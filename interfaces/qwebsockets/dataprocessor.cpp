#include "dataprocessor.h"
#include "websocketprotocol.h"
#include <QTcpSocket>
#include <QtEndian>
#include <limits.h>
#include <QTextCodec>
#include <QTextDecoder>

const quint64 MAX_FRAME_SIZE_IN_BYTES = INT_MAX - 1;
const quint64 MAX_MESSAGE_SIZE_IN_BYTES = INT_MAX - 1;

class Frame
{
public:
	Frame();
	Frame(const Frame &other);

	const Frame &operator =(const Frame &other);

	WebSocketProtocol::CloseCode getCloseCode() const;
	QString getCloseReason() const;
	bool isFinalFrame() const;
	bool isControlFrame() const;
	bool isDataFrame() const;
	bool isContinuationFrame() const;
	bool hasMask() const;
	quint32 getMask() const;    //returns 0 if no mask
	int getRsv1() const;
	int getRsv2() const;
	int getRsv3() const;
	WebSocketProtocol::OpCode getOpCode() const;
	QByteArray getPayload() const;

	void clear();       //resets all member variables, and invalidates the object

	bool isValid() const;

	static Frame readFrame(QTcpSocket *pSocket);

private:
	WebSocketProtocol::CloseCode m_closeCode;
	QString m_closeReason;
	bool m_isFinalFrame;
	quint32 m_mask;
	int m_rsv1; //reserved field 1
	int m_rsv2; //reserved field 2
	int m_rsv3; //reserved field 3
	WebSocketProtocol::OpCode m_opCode;

	quint8 m_length;        //length field as read from the header; this is 1 byte, which when 126 or 127, indicates a large payload
	QByteArray m_payload;

	bool m_isValid;

	enum ProcessingState
	{
		PS_READ_HEADER,
		PS_READ_PAYLOAD_LENGTH,
		PS_READ_BIG_PAYLOAD_LENGTH,
		PS_READ_MASK,
		PS_READ_PAYLOAD,
		PS_DISPATCH_RESULT,
		PS_WAIT_FOR_MORE_DATA
	};

	void setError(WebSocketProtocol::CloseCode code, QString closeReason);
	bool checkValidity();
};

Frame::Frame() :
	m_closeCode(WebSocketProtocol::CC_NORMAL),
	m_closeReason(),
	m_isFinalFrame(true),
	m_mask(0),
	m_rsv1(0),
	m_rsv2(0),
	m_rsv3(0),
	m_opCode(WebSocketProtocol::OC_RESERVED_V),
	m_length(0),
	m_payload(),
	m_isValid(false)
{
}

Frame::Frame(const Frame &other) :
	m_closeCode(other.m_closeCode),
	m_closeReason(other.m_closeReason),
	m_isFinalFrame(other.m_isFinalFrame),
	m_mask(other.m_mask),
	m_rsv1(other.m_rsv1),
	m_rsv2(other.m_rsv2),
	m_rsv3(other.m_rsv3),
	m_opCode(other.m_opCode),
	m_length(other.m_length),
	m_payload(other.m_payload),
	m_isValid(other.m_isValid)
{
}

const Frame &Frame::operator =(const Frame &other)
{
	m_closeCode = other.m_closeCode;
	m_closeReason = other.m_closeReason;
	m_isFinalFrame = other.m_isFinalFrame;
	m_mask = other.m_mask;
	m_rsv1 = other.m_rsv1;
	m_rsv2 = other.m_rsv2;
	m_rsv3 = other.m_rsv2;
	m_opCode = other.m_opCode;
	m_length = other.m_length;
	m_payload = other.m_payload;
	m_isValid = other.m_isValid;

	return *this;
}

WebSocketProtocol::CloseCode Frame::getCloseCode() const
{
	return m_closeCode;
}

QString Frame::getCloseReason() const
{
	return m_closeReason;
}

bool Frame::isFinalFrame() const
{
	return m_isFinalFrame;
}

bool Frame::isControlFrame() const
{
	return (m_opCode & 0x08) == 0x08;
}

bool Frame::isDataFrame() const
{
	return !isControlFrame();
}

bool Frame::isContinuationFrame() const
{
	return isDataFrame() && (m_opCode == WebSocketProtocol::OC_CONTINUE);
}

bool Frame::hasMask() const
{
	return m_mask != 0;
}

quint32 Frame::getMask() const
{
	return m_mask;
}

int Frame::getRsv1() const
{
	return m_rsv1;
}

int Frame::getRsv2() const
{
	return m_rsv2;
}

int Frame::getRsv3() const
{
	return m_rsv3;
}

WebSocketProtocol::OpCode Frame::getOpCode() const
{
	return m_opCode;
}

QByteArray Frame::getPayload() const
{
	return m_payload;
}

void Frame::clear()
{
	m_closeCode = WebSocketProtocol::CC_NORMAL;
	m_closeReason.clear();
	m_isFinalFrame = true;
	m_mask = 0;
	m_rsv1 = 0;
	m_rsv2 =0;
	m_rsv3 = 0;
	m_opCode = WebSocketProtocol::OC_RESERVED_V;
	m_length = 0;
	m_payload.clear();
	m_isValid = false;
}

bool Frame::isValid() const
{
	return m_isValid;
}

#define WAIT_FOR_MORE_DATA(dataSizeInBytes)  { returnState = processingState; processingState = PS_WAIT_FOR_MORE_DATA; dataWaitSize = dataSizeInBytes; }

Frame Frame::readFrame(QTcpSocket *pSocket)
{
	bool isDone = false;
	qint64 bytesRead = 0;
	Frame frame;
	quint64 dataWaitSize = 0;
	ProcessingState processingState = PS_READ_HEADER;
	ProcessingState returnState = PS_READ_HEADER;
	bool hasMask = false;
	quint64 payloadLength = 0;

	while (!isDone)
	{
		switch (processingState)
		{
			case PS_WAIT_FOR_MORE_DATA:
			{
				bool ok = pSocket->waitForReadyRead(5000);
				if (!ok)
				{
					frame.setError(WebSocketProtocol::CC_GOING_AWAY, "Timeout when reading data from socket.");
					isDone = true;
				}
				else
				{
					processingState = returnState;
				}
				break;
			}
			case PS_READ_HEADER:
			{
				if (pSocket->bytesAvailable() >= 2)
				{
					//FIN, RSV1-3, Opcode
					char header[2] = {0};
					bytesRead = pSocket->read(header, 2);
					frame.m_isFinalFrame = (header[0] & 0x80) != 0;
					frame.m_rsv1 = (header[0] & 0x40);
					frame.m_rsv2 = (header[0] & 0x20);
					frame.m_rsv3 = (header[0] & 0x10);
					frame.m_opCode = static_cast<WebSocketProtocol::OpCode>(header[0] & 0x0F);

					//Mask, PayloadLength
					hasMask = (header[1] & 0x80) != 0;
					frame.m_length = (header[1] & 0x7F);

					switch (frame.m_length)
					{
						case 126:
						{
							processingState = PS_READ_PAYLOAD_LENGTH;
							break;
						}
						case 127:
						{
							processingState = PS_READ_BIG_PAYLOAD_LENGTH;
							break;
						}
						default:
						{
							payloadLength = frame.m_length;
							processingState = hasMask ? PS_READ_MASK : PS_READ_PAYLOAD;
							break;
						}
					}
					if (!frame.checkValidity())
					{
						isDone = true;
					}
				}
				else
				{
					WAIT_FOR_MORE_DATA(2);
				}
				break;
			}

			case PS_READ_PAYLOAD_LENGTH:
			{
				if (pSocket->bytesAvailable() >= 2)
				{
					uchar length[2] = {0};
					 //TODO: Handle return value
					bytesRead = pSocket->read(reinterpret_cast<char *>(length), 2);
					payloadLength = qFromBigEndian<quint16>(reinterpret_cast<const uchar *>(length));
					processingState = hasMask ? PS_READ_MASK : PS_READ_PAYLOAD;
				}
				else
				{
					WAIT_FOR_MORE_DATA(2);
				}
				break;
			}

			case PS_READ_BIG_PAYLOAD_LENGTH:
			{
				if (pSocket->bytesAvailable() >= 8)
				{
					uchar length[8] = {0};
					//TODO: Handle return value
					bytesRead = pSocket->read(reinterpret_cast<char *>(length), 8);
					//Most significant bit must be set to 0 as per http://tools.ietf.org/html/rfc6455#section-5.2
					//TODO: Do we check for that?
					payloadLength = qFromBigEndian<quint64>(length) & ~(1ULL << 63);
					processingState = hasMask ? PS_READ_MASK : PS_READ_PAYLOAD;
				}
				else
				{
					WAIT_FOR_MORE_DATA(8);
				}

				break;
			}

			case PS_READ_MASK:
			{
				if (pSocket->bytesAvailable() >= 4)
				{
					//TODO: Handle return value
					bytesRead = pSocket->read(reinterpret_cast<char *>(&frame.m_mask), sizeof(frame.m_mask));
					processingState = PS_READ_PAYLOAD;
				}
				else
				{
					WAIT_FOR_MORE_DATA(4);
				}
				break;
			}

			case PS_READ_PAYLOAD:
			{
				if (!payloadLength)
				{
					processingState = PS_DISPATCH_RESULT;
				}
				else if (payloadLength > MAX_FRAME_SIZE_IN_BYTES)
				{
					frame.setError(WebSocketProtocol::CC_TOO_MUCH_DATA, "Maximum framesize exceeded.");
					processingState = PS_DISPATCH_RESULT;
				}
				else
				{
					quint64 bytesAvailable = static_cast<quint64>(pSocket->bytesAvailable());
					if (bytesAvailable >= payloadLength)
					{
						frame.m_payload = pSocket->read(payloadLength);
						if (hasMask)
						{
							WebSocketProtocol::mask(&frame.m_payload, frame.m_mask);
						}
						processingState = PS_DISPATCH_RESULT;
					}
					else
					{
						WAIT_FOR_MORE_DATA(payloadLength);
					}
				}
				break;
			}

			case PS_DISPATCH_RESULT:
			{
				processingState = PS_READ_HEADER;
				isDone = true;
				break;
			}

			default:
			{
				//should not come here
				qDebug() << "DataProcessor::process: Found invalid state. This should not happen!";
				frame.clear();
				isDone = true;
				break;
			}
		}	//end switch
	}

	return frame;
}

void Frame::setError(WebSocketProtocol::CloseCode code, QString closeReason)
{
	clear();
	m_closeCode = code;
	m_closeReason = closeReason;
	m_isValid = false;
}

bool Frame::checkValidity()
{
	if (!isValid())
	{
		if (m_rsv1 || m_rsv2 || m_rsv3)
		{
			setError(WebSocketProtocol::CC_PROTOCOL_ERROR, "Rsv field is non-zero");
		}
		else if (WebSocketProtocol::isOpCodeReserved(m_opCode))
		{
			setError(WebSocketProtocol::CC_PROTOCOL_ERROR, "Used reserved opcode");
		}
		else if (isControlFrame())
		{
			if (m_length > 125)
			{
				setError(WebSocketProtocol::CC_PROTOCOL_ERROR, "Controle frame is larger than 125 bytes");
			}
			else if (!m_isFinalFrame)
			{
				setError(WebSocketProtocol::CC_PROTOCOL_ERROR, "Controle frames cannot be fragmented");
			}
			else
			{
				m_isValid = true;
			}
		}
		else
		{
			m_isValid = true;
		}
	}
	return m_isValid;
}

DataProcessor::DataProcessor(QObject *parent) :
	QObject(parent),
	m_processingState(PS_READ_HEADER),
	m_isFinalFrame(false),
	m_isFragmented(false),
	m_opCode(WebSocketProtocol::OC_CLOSE),
	m_isControlFrame(false),
	m_hasMask(false),
	m_mask(0),
	m_binaryMessage(),
	m_textMessage(),
	m_payloadLength(0),
	m_pConverterState(0),
	m_pTextCodec(QTextCodec::codecForName("UTF-8"))
{
	clear();
}

DataProcessor::~DataProcessor()
{
	clear();
	if (m_pConverterState)
	{
		delete m_pConverterState;
		m_pConverterState = 0;
	}
}

void DataProcessor::process(QTcpSocket *pSocket)
{
	bool isDone = false;

	while (!isDone)
	{
		Frame frame = Frame::readFrame(pSocket);
		if (frame.isValid())
		{
			if (frame.isControlFrame())
			{
				Q_EMIT controlFrameReceived(frame.getOpCode(), frame.getPayload());
				isDone = true;  //exit the loop after a control frame, so we can get a chance to close the socket if necessary
			}
			else    //we have a dataframe; opcode can be OC_CONTINUE, OC_TEXT or OC_BINARY
			{
				if (!m_isFragmented && frame.isContinuationFrame())
				{
					clear();
					Q_EMIT errorEncountered(WebSocketProtocol::CC_PROTOCOL_ERROR, "Received Continuation frame /*with FIN=true*/, while there is nothing to continue.");
					return;
				}
				if (m_isFragmented && frame.isDataFrame() && !frame.isContinuationFrame())
				{
					clear();
					Q_EMIT errorEncountered(WebSocketProtocol::CC_PROTOCOL_ERROR, "All data frames after the initial data frame must have opcode 0 (continuation).");
					return;
				}
				if (!frame.isContinuationFrame())
				{
					m_opCode = frame.getOpCode();
					m_isFragmented = !frame.isFinalFrame();
				}
				quint64 messageLength = (quint64)(m_opCode == WebSocketProtocol::OC_TEXT) ? m_textMessage.length() : m_binaryMessage.length();
				if ((messageLength + quint64(frame.getPayload().length())) > MAX_MESSAGE_SIZE_IN_BYTES)
				{
					clear();
					Q_EMIT errorEncountered(WebSocketProtocol::CC_TOO_MUCH_DATA, "Received message is too big.");
					return;
				}

				if (m_opCode == WebSocketProtocol::OC_TEXT)
				{
					QString frameTxt = m_pTextCodec->toUnicode(frame.getPayload().constData(), frame.getPayload().size(), m_pConverterState);
					bool failed = (m_pConverterState->invalidChars != 0) || (frame.isFinalFrame() && (m_pConverterState->remainingChars != 0));
					if (failed)
					{
						clear();
						Q_EMIT errorEncountered(WebSocketProtocol::CC_WRONG_DATATYPE, "Invalid UTF-8 code encountered.");
						return;
					}
					else
					{
						m_textMessage.append(frameTxt);
						Q_EMIT textFrameReceived(frameTxt, frame.isFinalFrame());
					}
				}
				else
				{
					m_binaryMessage.append(frame.getPayload());
					Q_EMIT binaryFrameReceived(frame.getPayload(), frame.isFinalFrame());
				}

				if (frame.isFinalFrame())
				{
					if (m_opCode == WebSocketProtocol::OC_TEXT)
					{
						Q_EMIT textMessageReceived(m_textMessage);
					}
					else
					{
						Q_EMIT binaryMessageReceived(m_binaryMessage);
					}
					clear();
					isDone = true;
				}
			}
		}
		else
		{
			Q_EMIT errorEncountered(frame.getCloseCode(), frame.getCloseReason());
			clear();
			isDone = true;
		}
	}
}

void DataProcessor::clear()
{
	m_processingState = PS_READ_HEADER;
	m_isFinalFrame = false;
	m_isFragmented = false;
	m_opCode = WebSocketProtocol::OC_CLOSE;
	m_hasMask = false;
	m_mask = 0;
	m_binaryMessage.clear();
	m_textMessage.clear();
	m_payloadLength = 0;
	if (m_pConverterState)
	{
		if ((m_pConverterState->remainingChars != 0) || (m_pConverterState->invalidChars != 0))
		{
			delete m_pConverterState;
			m_pConverterState = 0;
		}
	}
	if (!m_pConverterState)
	{
		m_pConverterState = new QTextCodec::ConverterState(QTextCodec::ConvertInvalidToNull | QTextCodec::IgnoreHeader);
	}
}
