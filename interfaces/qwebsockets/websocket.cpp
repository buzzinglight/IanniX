#include "websocket.h"
#include "handshakerequest.h"
#include "handshakeresponse.h"
#include <QUrl>
#include <QTcpSocket>
#include <QByteArray>
#include <QtEndian>
#include <QCryptographicHash>
#include <QRegExp>
#include <QStringList>
#include <QHostAddress>
#include <QNetworkProxy>

#include <QDebug>

#include <limits>

/*!
	\class WebSocket
	\brief The class WebSocket implements a TCP socket that talks the websocket protocol.

	WebSockets is a web technology providing full-duplex communications channels over a single TCP connection.
	The WebSocket protocol was standardized by the IETF as RFC 6455 in 2011 (see http://tools.ietf.org/html/rfc6455).
	It can both be used in a client application and server application.

	This class was modeled after QAbstractSocket.

	\ref echoclient

	\author Kurt Pattyn (pattyn.kurt@gmail.com)
*/
/*!
  \page echoclient WebSocket client example
  \brief A sample websocket client that sends a message and displays the message that it receives back.

  \section Description
  The EchoClient example implements a web socket client that sends a message to a websocket server and dumps the answer that it gets back.
  This example should ideally be used with the EchoServer example.
  \section Code
  We start by connecting to the `connected()` signal.
  \snippet echoclient.cpp constructor
  After the connection, we open the socket to the given \a url.

  \snippet echoclient.cpp onConnected
  When the client is connected successfully, we connect to the `onTextMessageReceived()` signal, and send out "Hello, world!".
  If connected with the EchoServer, we will receive the same message back.

  \snippet echoclient.cpp onTextMessageReceived
  Whenever a message is received, we write it out.
*/

/*!
  \fn void WebSocket::connected()
  \brief Emitted when a connection is successfully established.
  \sa open(), disconnected()
*/
/*!
  \fn void WebSocket::disconnected()
  \brief Emitted when the socket is disconnected.
  \sa close(), connected()
*/
/*!
	\fn void WebSocket::aboutToClose()

	This signal is emitted when the socket is about to close.
	Connect this signal if you have operations that need to be performed before the socket closes
	(e.g., if you have data in a separate buffer that needs to be written to the device).

	\sa close()
 */
/*!
\fn void WebSocket::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)

This signal can be emitted when a \a proxy that requires
authentication is used. The \a authenticator object can then be
filled in with the required details to allow authentication and
continue the connection.

\note It is not possible to use a QueuedConnection to connect to
this signal, as the connection will fail if the authenticator has
not been filled in with new information when the signal returns.

\sa QAuthenticator, QNetworkProxy
*/
/*!
	\fn void WebSocket::stateChanged(QAbstractSocket::SocketState state);

	This signal is emitted whenever WebSocket's state changes.
	The \a socketState parameter is the new state.

	QAbstractSocket::SocketState is not a registered metatype, so for queued
	connections, you will have to register it with Q_REGISTER_METATYPE() and
	qRegisterMetaType().

	\sa state()
*/
/*!
	\fn void WebSocket::readChannelFinished()

	This signal is emitted when the input (reading) stream is closed in this device. It is emitted as soon as the closing is detected.

	\sa close()
*/

/*!
	\fn void WebSocket::textFrameReceived(QString frame, bool isLastFrame);

	This signal is emitted whenever a text frame is received. The \a frame contains the data and
	\a isLastFrame indicates whether this is the last frame of the complete message.

	This signal can be used to process large messages frame by frame, instead of waiting for the complete
	message to arrive.

	\sa binaryFrameReceived(QByteArray, bool), textMessageReceived(QString)
*/
/*!
	\fn void WebSocket::binaryFrameReceived(QByteArray frame, bool isLastFrame);

	This signal is emitted whenever a binary frame is received. The \a frame contains the data and
	\a isLastFrame indicates whether this is the last frame of the complete message.

	This signal can be used to process large messages frame by frame, instead of waiting for the complete
	message to arrive.

	\sa textFrameReceived(QString, bool), binaryMessageReceived(QByteArray)
*/
/*!
	\fn void WebSocket::textMessageReceived(QString message);

	This signal is emitted whenever a text message is received. The \a message contains the received text.

	\sa textFrameReceived(QString, bool), binaryMessageReceived(QByteArray)
*/
/*!
	\fn void WebSocket::binaryMessageReceived(QByteArray message);

	This signal is emitted whenever a binary message is received. The \a message contains the received bytes.

	\sa binaryFrameReceived(QByteArray, bool), textMessageReceived(QString)
*/
/*!
	\fn void WebSocket::error(QAbstractSocket::SocketError error);

	This signal is emitted after an error occurred. The \a socketError
	parameter describes the type of error that occurred.

	QAbstractSocket::SocketError is not a registered metatype, so for queued
	connections, you will have to register it with Q_DECLARE_METATYPE() and
	qRegisterMetaType().

	\sa error(), errorString()
*/
/*!
  \fn void WebSocket::pong(quint64 elapsedTime)

  Emitted when a pong message is received in reply to a previous ping.

  \sa ping()
  */

const quint64 FRAME_SIZE_IN_BYTES = 512 * 512 * 2;	//maximum size of a frame when sending a message

/*!
 * \brief Creates a new WebSocket with the given \a origin, the \a version of the protocol to use and \a parent.
 *
 * The \a origin of the client is as specified in http://tools.ietf.org/html/rfc6454.
 * (The \a origin is not required for non-web browser clients (see RFC 6455)).
 * \note Currently only V13 (RFC 6455) is supported
 */
WebSocket::WebSocket(QString origin, WebSocketProtocol::Version version, QObject *parent) :
	QObject(parent),
	m_pSocket(new QTcpSocket(this)),
	m_errorString(),
	m_version(version),
	m_resourceName(),
	m_requestUrl(),
	m_origin(origin),
	m_protocol(""),
	m_extension(""),
	m_socketState(QAbstractSocket::UnconnectedState),
	m_key(),
	m_mustMask(true),
	m_isClosingHandshakeSent(false),
	m_isClosingHandshakeReceived(false),
	m_pingTimer(),
	m_dataProcessor()
{
	makeConnections(m_pSocket);
	qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));
}

//only called by upgradeFrom
/*!
	\internal
	Constructor used for the server implementation. Should never be called directly.

	pTcpSocket The tcp socket to use for this websocket
	version The version of the protocol to speak (currently only V13 is supported)
	parent The parent object of the WebSocket object
*/
WebSocket::WebSocket(QTcpSocket *pTcpSocket, WebSocketProtocol::Version version, QObject *parent) :
	QObject(parent),
	m_pSocket(pTcpSocket),
	m_errorString(pTcpSocket->errorString()),
	m_version(version),
	m_resourceName(),
	m_requestUrl(),
	m_origin(),
	m_protocol(),
	m_extension(),
	m_socketState(pTcpSocket->state()),
	m_key(),
	m_mustMask(true),
	m_isClosingHandshakeSent(false),
	m_isClosingHandshakeReceived(false),
	m_pingTimer(),
	m_dataProcessor()
{
	makeConnections(m_pSocket);
}

/*!
 * \brief Destroys the WebSocket. Closes the socket if it is still open, and releases any used resources.
 */
WebSocket::~WebSocket()
{
	if (state() == QAbstractSocket::ConnectedState)
	{
		close(WebSocketProtocol::CC_GOING_AWAY, "Connection closed");
	}
	releaseConnections(m_pSocket);
	m_pSocket->deleteLater();
	m_pSocket = 0;
}

/*!
 * \brief Aborts the current socket and resets the socket. Unlike close(), this function immediately closes the socket, discarding any pending data in the write buffer.
 */
void WebSocket::abort()
{
	m_pSocket->abort();
}

/*!
 * Returns the type of error that last occurred
 * \sa errorString()
 */
QAbstractSocket::SocketError WebSocket::error() const
{
	return m_pSocket->error();
}

/*!
 * Returns a human-readable description of the last error that occurred
 *
 * \sa error()
 */
QString WebSocket::errorString() const
{
	if (!m_errorString.isEmpty())
	{
		return m_errorString;
	}
	else
	{
		return m_pSocket->errorString();
	}
}

/*!
	This function writes as much as possible from the internal write buffer to the underlying network socket, without blocking.
	If any data was written, this function returns true; otherwise false is returned.
	Call this function if you need WebSocket to start sending buffered data immediately.
	The number of bytes successfully written depends on the operating system.
	In most cases, you do not need to call this function, because WebSocket will start sending data automatically once control goes back to the event loop.
	In the absence of an event loop, call waitForBytesWritten() instead.

	\sa send() and waitForBytesWritten().
*/
bool WebSocket::flush()
{
	return m_pSocket->flush();
}

/*!
 * Sends the given \a message over the socket as a text message and returns the number of bytes actually sent.
 * \param message Text message to be sent. Must be '\0' terminated.
 * \return The number of bytes actually sent.
 * \sa send(const QString &message)
 */
qint64 WebSocket::send(const char *message)
{
	return send(QString::fromUtf8(message));
}

/**
 * @brief Sends the given \a message over the socket as a text message and returns the number of bytes actually sent.
 * @param message The message to be sent
 * @return The number of bytes actually sent.
 */
qint64 WebSocket::send(const QString &message)
{
	return doWriteData(message.toUtf8(), false);
}

/**
 * @brief Sends the given \a data over the socket as a binary message and returns the number of bytes actually sent.
 * @param data The binary data to be sent.
 * @return The number of bytes actually sent.
 */
qint64 WebSocket::send(const QByteArray &data)
{
	return doWriteData(data, true);
}

/*!
  \internal
 */
WebSocket *WebSocket::upgradeFrom(QTcpSocket *pTcpSocket,
								  const HandshakeRequest &request,
								  const HandshakeResponse &response,
								  QObject *parent)
{
	WebSocket *pWebSocket = new WebSocket(pTcpSocket, response.getAcceptedVersion(), parent);
	pWebSocket->setExtension(response.getAcceptedExtension());
	pWebSocket->setOrigin(request.getOrigin());
	pWebSocket->setRequestUrl(request.getRequestUrl());
	pWebSocket->setProtocol(response.getAcceptedProtocol());
	pWebSocket->setResourceName(request.getRequestUrl().toString(QUrl::RemoveUserInfo));
	pWebSocket->enableMasking(false);	//a server should not send masked frames

	return pWebSocket;
}

/*!
 * \brief Gracefully closes the socket with the given \a closeCode and \a reason. Any data in the write buffer is flushed before the socket is closed.
 * \param closeCode The WebSocketProtocol::CloseCode indicating the reason to close.
 * \param reason A string describing the error more in detail
 */
void WebSocket::close(WebSocketProtocol::CloseCode closeCode, QString reason)
{
	if (!m_isClosingHandshakeSent)
	{
		quint32 maskingKey = 0;
		if (m_mustMask)
		{
			maskingKey = generateMaskingKey();
		}
		quint16 code = qToBigEndian<quint16>(closeCode);
		QByteArray payload;
		payload.append(static_cast<const char *>(static_cast<const void *>(&code)), 2);
		if (!reason.isEmpty())
		{
			payload.append(reason.toUtf8());
		}
		if (m_mustMask)
		{
			WebSocketProtocol::mask(payload.data(), payload.size(), maskingKey);
		}
		QByteArray frame = getFrameHeader(WebSocketProtocol::OC_CLOSE, payload.size(), maskingKey, true);
		frame.append(payload);
		m_pSocket->write(frame);
		m_pSocket->flush();

		m_isClosingHandshakeSent = true;

		Q_EMIT aboutToClose();
	}
	m_pSocket->close();
}

/*!
 * \brief Opens a websocket connection using the given \a url.
 * If \a mask is true, all frames will be masked; this is only necessary for client side sockets; servers should never mask
 * \param url The url to connect to
 * \param mask When true, all frames are masked
 * \note A client socket must *always* mask its frames; servers may *never* mask its frames
 */
void WebSocket::open(const QUrl &url, bool mask)
{
	m_dataProcessor.clear();
	m_isClosingHandshakeReceived = false;
	m_isClosingHandshakeSent = false;

	setRequestUrl(url);
    QString resourceName = url.path() + url.toEncoded(); // NOTE 4.8
	if (resourceName.isEmpty())
	{
		resourceName = "/";
	}
	setResourceName(resourceName);
	enableMasking(mask);

	setSocketState(QAbstractSocket::ConnectingState);

	m_pSocket->connectToHost(url.host(), url.port(80));
}

/*!
 * \brief Pings the server to indicate that the connection is still alive.
 *
 * \sa pong()
 */
void WebSocket::ping()
{
	m_pingTimer.restart();
	QByteArray pingFrame = getFrameHeader(WebSocketProtocol::OC_PING, 0, 0, true);
	writeFrame(pingFrame);
}

/*!
  \internal
	Sets the version to use for the websocket protocol; this must be set before the socket is opened.
*/
void WebSocket::setVersion(WebSocketProtocol::Version version)
{
	m_version = version;
}

/*!
	\internal
	Sets the resource name of the connection; must be set before the socket is openend
*/
void WebSocket::setResourceName(QString resourceName)
{
	m_resourceName = resourceName;
}

/*!
  \internal
 */
void WebSocket::setRequestUrl(QUrl requestUrl)
{
	m_requestUrl = requestUrl;
}

/*!
  \internal
 */
void WebSocket::setOrigin(QString origin)
{
	m_origin = origin;
}

/*!
  \internal
 */
void WebSocket::setProtocol(QString protocol)
{
	m_protocol = protocol;
}

/*!
  \internal
 */
void WebSocket::setExtension(QString extension)
{
	m_extension = extension;
}

/*!
  \internal
 */
void WebSocket::enableMasking(bool enable)
{
	m_mustMask = enable;
}

/*!
 * \internal
 */
qint64 WebSocket::doWriteData(const QByteArray &data, bool isBinary)
{
	return doWriteFrames(data, isBinary);
}

/*!
 * \internal
 */
void WebSocket::makeConnections(const QTcpSocket *pTcpSocket)
{
	//pass through signals
	connect(pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(error(QAbstractSocket::SocketError)));
	connect(pTcpSocket, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)), this, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)));
	connect(pTcpSocket, SIGNAL(readChannelFinished()), this, SIGNAL(readChannelFinished()));
	//connect(pTcpSocket, SIGNAL(aboutToClose()), this, SIGNAL(aboutToClose()));
	//connect(pTcpSocket, SIGNAL(bytesWritten(qint64)), this, SIGNAL(bytesWritten(qint64)));

	//catch signals
	connect(pTcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(processStateChanged(QAbstractSocket::SocketState)));
	connect(pTcpSocket, SIGNAL(readyRead()), this, SLOT(processData()));

	connect(&m_dataProcessor, SIGNAL(controlFrameReceived(WebSocketProtocol::OpCode, QByteArray)), this, SLOT(processControlFrame(WebSocketProtocol::OpCode, QByteArray)));
	connect(&m_dataProcessor, SIGNAL(textFrameReceived(QString,bool)), this, SIGNAL(textFrameReceived(QString,bool)));
	connect(&m_dataProcessor, SIGNAL(binaryFrameReceived(QByteArray,bool)), this, SIGNAL(binaryFrameReceived(QByteArray,bool)));
	connect(&m_dataProcessor, SIGNAL(binaryMessageReceived(QByteArray)), this, SIGNAL(binaryMessageReceived(QByteArray)));
	connect(&m_dataProcessor, SIGNAL(textMessageReceived(QString)), this, SIGNAL(textMessageReceived(QString)));
	connect(&m_dataProcessor, SIGNAL(errorEncountered(WebSocketProtocol::CloseCode,QString)), this, SLOT(close(WebSocketProtocol::CloseCode,QString)));
}

/*!
 * \internal
 */
void WebSocket::releaseConnections(const QTcpSocket *pTcpSocket)
{
	if (pTcpSocket)
	{
		//pass through signals
		disconnect(pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(error(QAbstractSocket::SocketError)));
		disconnect(pTcpSocket, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)), this, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)));
		disconnect(pTcpSocket, SIGNAL(readChannelFinished()), this, SIGNAL(readChannelFinished()));
		//disconnect(pTcpSocket, SIGNAL(aboutToClose()), this, SIGNAL(aboutToClose()));
		//disconnect(pTcpSocket, SIGNAL(bytesWritten(qint64)), this, SIGNAL(bytesWritten(qint64)));

		//catched signals
		disconnect(pTcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(processStateChanged(QAbstractSocket::SocketState)));
		disconnect(pTcpSocket, SIGNAL(readyRead()), this, SLOT(processData()));
	}
	disconnect(&m_dataProcessor, SIGNAL(controlFrameReceived(WebSocketProtocol::OpCode,QByteArray)), this, SLOT(processControlFrame(WebSocketProtocol::OpCode,QByteArray)));
	disconnect(&m_dataProcessor, SIGNAL(textFrameReceived(QString,bool)), this, SIGNAL(textFrameReceived(QString,bool)));
	disconnect(&m_dataProcessor, SIGNAL(binaryFrameReceived(QByteArray,bool)), this, SIGNAL(binaryFrameReceived(QByteArray,bool)));
	disconnect(&m_dataProcessor, SIGNAL(binaryMessageReceived(QByteArray)), this, SIGNAL(binaryMessageReceived(QByteArray)));
	disconnect(&m_dataProcessor, SIGNAL(textMessageReceived(QString)), this, SIGNAL(textMessageReceived(QString)));
	disconnect(&m_dataProcessor, SIGNAL(errorEncountered(WebSocketProtocol::CloseCode,QString)), this, SLOT(close(WebSocketProtocol::CloseCode,QString)));
}

/*!
 * \brief Returns the version the socket is currently using
 */
WebSocketProtocol::Version WebSocket::getVersion()
{
	return m_version;
}

/**
 * @brief Returns the name of the resource currently accessed.
 */
QString WebSocket::getResourceName()
{
	return m_resourceName;
}

/*!
 * \brief Returns the url the socket is connected to or will connect to.
 */
QUrl WebSocket::getRequestUrl()
{
	return m_requestUrl;
}

/*!
  Returns the current origin
 */
QString WebSocket::getOrigin()
{
	return m_origin;
}

/*!
  Returns the currently used protocol.
 */
QString WebSocket::getProtocol()
{
	return m_protocol;
}

/*!
  Returns the currently used extension.
 */
QString WebSocket::getExtension()
{
	return m_extension;
}

/*!
 * \internal
 */
QByteArray WebSocket::getFrameHeader(WebSocketProtocol::OpCode opCode, quint64 payloadLength, quint32 maskingKey, bool lastFrame) const
{
	QByteArray header;
	quint8 byte = 0x00;
	bool ok = payloadLength <= 0x7FFFFFFFFFFFFFFFULL;

	if (ok)
	{
		//FIN, RSV1-3, opcode
		byte = static_cast<quint8>((opCode & 0x0F) | (lastFrame ? 0x80 : 0x00));	//FIN, opcode
		//RSV-1, RSV-2 and RSV-3 are zero
		header.append(static_cast<char>(byte));

		//Now write the masking bit and the payload length byte
		byte = 0x00;
		if (maskingKey != 0)
		{
			byte |= 0x80;
		}
		if (payloadLength <= 125)
		{
			byte |= static_cast<quint8>(payloadLength);
			header.append(static_cast<char>(byte));
		}
		else if (payloadLength <= 0xFFFFU)
		{
			byte |= 126;
			header.append(static_cast<char>(byte));
			quint16 swapped = qToBigEndian<quint16>(static_cast<quint16>(payloadLength));
			header.append(static_cast<const char *>(static_cast<const void *>(&swapped)), 2);
		}
		else if (payloadLength <= 0x7FFFFFFFFFFFFFFFULL)
		{
			byte |= 127;
			header.append(static_cast<char>(byte));
			quint64 swapped = qToBigEndian<quint64>(payloadLength);
			header.append(static_cast<const char *>(static_cast<const void *>(&swapped)), 8);
		}

		//Write mask
		if (maskingKey != 0)
		{
			header.append(static_cast<const char *>(static_cast<const void *>(&maskingKey)), sizeof(quint32));
		}
	}
	else
	{
		//setErrorString("WebSocket::getHeader: payload too big!");
		//Q_EMIT error(QAbstractSocket::DatagramTooLargeError);
		qDebug() << "WebSocket::getHeader: payload too big!";
	}

	return header;
}

/*!
 * \internal
 */
qint64 WebSocket::doWriteFrames(const QByteArray &data, bool isBinary)
{
	const WebSocketProtocol::OpCode firstOpCode = isBinary ? WebSocketProtocol::OC_BINARY : WebSocketProtocol::OC_TEXT;

	int numFrames = data.size() / FRAME_SIZE_IN_BYTES;
	QByteArray tmpData(data);
	tmpData.detach();
	char *payload = tmpData.data();
	quint64 sizeLeft = static_cast<quint64>(data.size()) % FRAME_SIZE_IN_BYTES;
	if (sizeLeft)
	{
		++numFrames;
	}
	if (numFrames == 0)     //catch the case where the payload is zero bytes; in that case, we still need to send a frame
	{
		numFrames = 1;
	}
	quint64 currentPosition = 0;
	qint64 bytesWritten = 0;
	qint64 payloadWritten = 0;
	quint64 bytesLeft = data.size();

	for (int i = 0; i < numFrames; ++i)
	{
		quint32 maskingKey = 0;
		if (m_mustMask)
		{
			maskingKey = generateMaskingKey();
		}

		bool isLastFrame = (i == (numFrames - 1));
		bool isFirstFrame = (i == 0);

		quint64 size = qMin(bytesLeft, FRAME_SIZE_IN_BYTES);
		WebSocketProtocol::OpCode opcode = isFirstFrame ? firstOpCode : WebSocketProtocol::OC_CONTINUE;

		//write header
		bytesWritten += m_pSocket->write(getFrameHeader(opcode, size, maskingKey, isLastFrame));

		//write payload
		if (size > 0)
		{
			char *currentData = payload + currentPosition;
			if (m_mustMask)
			{
				WebSocketProtocol::mask(currentData, size, maskingKey);
			}
			qint64 written = m_pSocket->write(currentData, static_cast<qint64>(size));
			if (written > 0)
			{
				bytesWritten += written;
				payloadWritten += written;
			}
			else
			{
				setErrorString("WebSocket::doWriteFrames: Error writing bytes to socket: " + m_pSocket->errorString());
				qDebug() << errorString();
				m_pSocket->flush();
				Q_EMIT error(QAbstractSocket::NetworkError);
				break;
			}
		}
		currentPosition += size;
		bytesLeft -= size;
	}
	if (payloadWritten != data.size())
	{
		setErrorString("Bytes written " + QString::number(payloadWritten) + " != " + QString::number(data.size()));
		qDebug() << errorString();
		Q_EMIT error(QAbstractSocket::NetworkError);
	}
	return payloadWritten;
}

/*!
 * \internal
 */
quint32 WebSocket::generateRandomNumber() const
{
	return static_cast<quint32>((static_cast<double>(qrand()) / RAND_MAX) * std::numeric_limits<quint32>::max());
}

/*!
	\internal
 */
quint32 WebSocket::generateMaskingKey() const
{
	return generateRandomNumber();
}

/*!
	\internal
 */
QByteArray WebSocket::generateKey() const
{
	QByteArray key;

	for (int i = 0; i < 4; ++i)
	{
		quint32 tmp = generateRandomNumber();
		key.append(static_cast<const char *>(static_cast<const void *>(&tmp)), sizeof(quint32));
	}

	return key.toBase64();
}


/*!
	\internal
 */
QString WebSocket::calculateAcceptKey(const QString &key) const
{
	QString tmpKey = key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
	QByteArray hash = QCryptographicHash::hash(tmpKey.toLatin1(), QCryptographicHash::Sha1);
	return QString(hash.toBase64());
}

/*!
	\internal
 */
qint64 WebSocket::writeFrames(const QList<QByteArray> &frames)
{
	qint64 written = 0;
	for (int i = 0; i < frames.size(); ++i)
	{
		written += writeFrame(frames[i]);
	}
	return written;
}

/*!
	\internal
 */
qint64 WebSocket::writeFrame(const QByteArray &frame)
{
	return m_pSocket->write(frame);
}

/*!
	\internal
 */
QString readLine(QTcpSocket *pSocket)
{
	QString line;
	char c;
	while (pSocket->getChar(&c))
	{
		if (c == '\r')
		{
			pSocket->getChar(&c);
			break;
		}
		else
		{
			line.append(QChar(c));
		}
	}
	return line;
}

//called for a server handshake response
/*!
	\internal
 */
void WebSocket::processHandshake(QTcpSocket *pSocket)
{
	if (pSocket == 0)
	{
		return;
	}

	bool ok = false;
	QString errorDescription;

	const QString regExpStatusLine("^(HTTP/1.1)\\s([0-9]+)\\s(.*)");
	const QRegExp regExp(regExpStatusLine);
	QString statusLine = readLine(pSocket);
	QString httpProtocol;
	int httpStatusCode;
	QString httpStatusMessage;
	if (regExp.indexIn(statusLine) != -1)
	{
		QStringList tokens = regExp.capturedTexts();
		tokens.removeFirst();	//remove the search string
		if (tokens.length() == 3)
		{
			httpProtocol = tokens[0];
			httpStatusCode = tokens[1].toInt();
			httpStatusMessage = tokens[2].trimmed();
			ok = true;
		}
	}
	if (!ok)
	{
		errorDescription = "WebSocket::processHandshake: Invalid statusline in response: " + statusLine;
	}
	else
	{
		QString headerLine = readLine(pSocket);
		QMap<QString, QString> headers;
		while (!headerLine.isEmpty())
		{
			QStringList headerField = headerLine.split(QString(": "), QString::SkipEmptyParts);
			headers.insertMulti(headerField[0], headerField[1]);
			headerLine = readLine(pSocket);
		}

		QString acceptKey = headers.value("Sec-WebSocket-Accept", "");
		QString upgrade = headers.value("Upgrade", "");
		QString connection = headers.value("Connection", "");
		QString extensions = headers.value("Sec-WebSocket-Extensions", "");
		QString protocol = headers.value("Sec-WebSocket-Protocol", "");
		QString version = headers.value("Sec-WebSocket-Version", "");

		if (httpStatusCode == 101)	//HTTP/1.1 101 Switching Protocols
		{
			//TODO: do not check the httpStatusText right now
			ok = !(acceptKey.isEmpty() ||
				   (httpProtocol.toLower() != "http/1.1") ||
				   (upgrade.toLower() != "websocket") ||
				   (connection.toLower() != "upgrade"));
			if (ok)
			{
				QString accept = calculateAcceptKey(m_key);
				ok = (accept == acceptKey);
				if (!ok)
				{
					errorDescription = "WebSocket::processHandshake: Accept-Key received from server " + acceptKey + " does not match the client key " + accept;
				}
			}
			else
			{
				errorDescription = "WebSocket::processHandshake: Invalid statusline in response: " + statusLine;
			}
		}
		else if (httpStatusCode == 400)	//HTTP/1.1 400 Bad Request
		{
			if (!version.isEmpty())
			{
				QStringList versions = version.split(", ", QString::SkipEmptyParts);
				if (!versions.contains("13"))
				{
					//if needed to switch protocol version, then we are finished here
					//because we cannot handle other protocols than the RFC one (v13)
					errorDescription = "WebSocket::processHandshake: Server requests a version that we don't support: " + versions.join(", ");
					ok = false;
				}
				else
				{
					//we tried v13, but something different went wrong
					errorDescription = "WebSocket::processHandshake: Unknown error condition encountered. Aborting connection.";
					ok = false;
				}
			}
		}
		else
		{
			errorDescription = "WebSocket::processHandshake: Unhandled http status code " + QString::number(httpStatusCode);
			ok = false;
		}

		if (!ok)
		{
			qDebug() << errorDescription;
			setErrorString(errorDescription);
			Q_EMIT error(QAbstractSocket::ConnectionRefusedError);
		}
		else
		{
			//handshake succeeded
			setSocketState(QAbstractSocket::ConnectedState);
			Q_EMIT connected();
		}
	}
}

/*!
	\internal
 */
void WebSocket::processStateChanged(QAbstractSocket::SocketState socketState)
{
	QAbstractSocket::SocketState webSocketState = this->state();
	switch (socketState)
	{
		case QAbstractSocket::ConnectedState:
		{
			if (webSocketState == QAbstractSocket::ConnectingState)
			{
				m_key = generateKey();
				QString handshake = createHandShakeRequest(m_resourceName, m_requestUrl.host() + ":" + QString::number(m_requestUrl.port(80)), getOrigin(), "", "", m_key);
				m_pSocket->write(handshake.toLatin1());
			}
			break;
		}
		case QAbstractSocket::ClosingState:
		{
			if (webSocketState == QAbstractSocket::ConnectedState)
			{
				setSocketState(QAbstractSocket::ClosingState);
			}
			break;
		}
		case QAbstractSocket::UnconnectedState:
		{
			if (webSocketState != QAbstractSocket::UnconnectedState)
			{
				setSocketState(QAbstractSocket::UnconnectedState);
				Q_EMIT disconnected();
			}
			break;
		}
		case QAbstractSocket::HostLookupState:
		case QAbstractSocket::ConnectingState:
		case QAbstractSocket::BoundState:
		case QAbstractSocket::ListeningState:
		{
			//do nothing
			//to make C++ compiler happy;
			break;
		}
		default:
		{
			break;
		}
	}
}

//order of events:
//connectToHost is called
//our socket state is set to "connecting", and tcpSocket->connectToHost is called
//the tcpsocket is opened, a handshake message is sent; a readyRead signal is thrown
//this signal is catched by processData
//when OUR socket state is in the "connecting state", this means that
//we have received data from the server (response to handshake), and that we
//should "upgrade" our socket to a websocket (connected state)
//if our socket was already upgraded, then we need to process websocket data
/*!
 \internal
 */
void WebSocket::processData()
{
	while (m_pSocket->bytesAvailable())
	{
		if (state() == QAbstractSocket::ConnectingState)
		{
			processHandshake(m_pSocket);
		}
		else
		{
			m_dataProcessor.process(m_pSocket);
		}
	}
}

/*!
	\internal
 */
void WebSocket::processControlFrame(WebSocketProtocol::OpCode opCode, QByteArray frame)
{
	switch (opCode)
	{
		case WebSocketProtocol::OC_PING:
		{
			quint32 maskingKey = 0;
			if (m_mustMask)
			{
				maskingKey = generateMaskingKey();
			}
			m_pSocket->write(getFrameHeader(WebSocketProtocol::OC_PONG, frame.size(), maskingKey, true));
			if (frame.size() > 0)
			{
				if (m_mustMask)
				{
					WebSocketProtocol::mask(&frame, maskingKey);
				}
				m_pSocket->write(frame);
			}
			break;
		}
		case WebSocketProtocol::OC_PONG:
		{
			Q_EMIT pong(static_cast<quint64>(m_pingTimer.elapsed()));
			break;
		}
		case WebSocketProtocol::OC_CLOSE:
		{
			quint16 closeCode = WebSocketProtocol::CC_NORMAL;
			QString closeReason;
			if (frame.size() > 0)   //close frame can have a close code and reason
			{
				closeCode = qFromBigEndian<quint16>(reinterpret_cast<const uchar *>(frame.constData()));
				if (!WebSocketProtocol::isCloseCodeValid(closeCode))
				{
					closeCode = WebSocketProtocol::CC_PROTOCOL_ERROR;
					closeReason = QString("Invalid close code %1 detected").arg(closeCode);
				}
				else
				{
					if (frame.size() > 2)
					{
						QTextCodec *tc = QTextCodec::codecForName("UTF-8");
						QTextCodec::ConverterState state(QTextCodec::ConvertInvalidToNull);
						closeReason = tc->toUnicode(frame.constData() + 2, frame.size() - 2, &state);
						bool failed = (state.invalidChars != 0) || (state.remainingChars != 0);
						if (failed)
						{
							closeCode = WebSocketProtocol::CC_WRONG_DATATYPE;
							closeReason = "Invalid UTF-8 code encountered.";
						}
					}
				}
			}
			m_isClosingHandshakeReceived = true;
			close(static_cast<WebSocketProtocol::CloseCode>(closeCode), closeReason);
			break;
		}
		case WebSocketProtocol::OC_CONTINUE:
		case WebSocketProtocol::OC_BINARY:
		case WebSocketProtocol::OC_TEXT:
		case WebSocketProtocol::OC_RESERVED_3:
		case WebSocketProtocol::OC_RESERVED_4:
		case WebSocketProtocol::OC_RESERVED_5:
		case WebSocketProtocol::OC_RESERVED_6:
		case WebSocketProtocol::OC_RESERVED_7:
		case WebSocketProtocol::OC_RESERVED_B:
		case WebSocketProtocol::OC_RESERVED_D:
		case WebSocketProtocol::OC_RESERVED_E:
		case WebSocketProtocol::OC_RESERVED_F:
		case WebSocketProtocol::OC_RESERVED_V:
		{
			//do nothing
			//case added to make C++ compiler happy
			break;
		}
		default:
		{
			qDebug() << "WebSocket::processData: Invalid opcode detected:" << static_cast<int>(opCode);
			//Do nothing
			break;
		}
	}
}

/*!
	\internal
 */
QString WebSocket::createHandShakeRequest(QString resourceName,
										  QString host,
										  QString origin,
										  QString extensions,
										  QString protocols,
										  QByteArray key)
{
	QStringList handshakeRequest;

	handshakeRequest << "GET " + resourceName + " HTTP/1.1" <<
						"Host: " + host <<
						"Upgrade: websocket" <<
						"Connection: Upgrade" <<
						"Sec-WebSocket-Key: " + QString(key);
	if (!origin.isEmpty())
	{
		handshakeRequest << "Origin: " + origin;
	}
	handshakeRequest << "Sec-WebSocket-Version: " + QString::number(WebSocketProtocol::getCurrentVersion());
	if (extensions.length() > 0)
	{
		handshakeRequest << "Sec-WebSocket-Extensions: " + extensions;
	}
	if (protocols.length() > 0)
	{
		handshakeRequest << "Sec-WebSocket-Protocol: " + protocols;
	}
	handshakeRequest << "\r\n";

	return handshakeRequest.join("\r\n");
}

/*!
  Returns the current state of the socket
 */
QAbstractSocket::SocketState WebSocket::state() const
{
	return m_socketState;
}

/**
	@brief Waits until the socket is connected, up to \a msecs milliseconds. If the connection has been established, this function returns true; otherwise it returns false. In the case where it returns false, you can call error() to determine the cause of the error.
	The following example waits up to one second for a connection to be established:

	~~~{.cpp}
	socket->open("ws://localhost:1234", false);
	if (socket->waitForConnected(1000))
	{
		qDebug("Connected!");
	}
	~~~

	If \a msecs is -1, this function will not time out.
	@note This function may wait slightly longer than msecs, depending on the time it takes to complete the host lookup.
	@note Multiple calls to this functions do not accumulate the time. If the function times out, the connecting process will be aborted.

	\param msecs The number of milliseconds to wait before a time out occurs; when -1, this function will block until the socket is connected.

	\sa connected(), open(), state()
 */
bool WebSocket::waitForConnected(int msecs)
{
	bool retVal = false;
	if (m_pSocket)
	{
		retVal = m_pSocket->waitForConnected(msecs);
	}
	return retVal;
}

/*!
  Waits \a msecs for the socket to be disconnected.
  If the socket was successfully disconnected within time, this method returns true.
  Otherwise false is returned.

  \param msecs The number of milliseconds to wait before a time out occurs; when -1, this function will block until the socket is disconnected.

  \sa close(), state()
*/
bool WebSocket::waitForDisconnected(int msecs)
{
	bool retVal = true;
	if (m_pSocket)
	{
		retVal = m_pSocket->waitForDisconnected(msecs);
	}
	return retVal;
}

/*!
 \internal
 Sets the internal socket state
*/
void WebSocket::setSocketState(QAbstractSocket::SocketState state)
{
	if (m_socketState != state)
	{
		m_socketState = state;
		Q_EMIT stateChanged(m_socketState);
	}
}

/*!
  \internal
  Sets the error string.
  Only used internally.
*/
void WebSocket::setErrorString(QString errorString)
{
	m_errorString = errorString;
}

/*!
  Returns the local address
 */
QHostAddress WebSocket::localAddress() const
{
	QHostAddress address;
	if (m_pSocket)
	{
		address = m_pSocket->localAddress();
	}
	return address;
}

/*!
  Returns the local port
 */
quint16 WebSocket::localPort() const
{
	quint16 port = 0;
	if (m_pSocket)
	{
		port = m_pSocket->localPort();
	}
	return port;
}

/*!
  Returns the peer address
 */
QHostAddress WebSocket::peerAddress() const
{
	QHostAddress peer;
	if (m_pSocket)
	{
		peer = m_pSocket->peerAddress();
	}
	return peer;
}

/*!
  Returns the peerName
 */
QString WebSocket::peerName() const
{
	QString name;
	if (m_pSocket)
	{
		name = m_pSocket->peerName();
	}
	return name;
}

/*!
  Returns the peerport
 */
quint16 WebSocket::peerPort() const
{
	quint16 port = 0;
	if (m_pSocket)
	{
		port = m_pSocket->peerPort();
	}
	return port;
}

/*!
  * Returns the currently configured proxy
 */
QNetworkProxy WebSocket::proxy() const
{
	QNetworkProxy proxy;
	if (m_pSocket)
	{
		proxy = m_pSocket->proxy();
	}
	return proxy;
}

/*!
 * Returns the size in bytes of the readbuffer that is used by the socket.
 */
qint64 WebSocket::readBufferSize() const
{
	qint64 readBuffer = 0;
	if (m_pSocket)
	{
		readBuffer = m_pSocket->readBufferSize();
	}
	return readBuffer;
}

/*!
  Sets the proxy to \a networkProxy
 */
void WebSocket::setProxy(const QNetworkProxy &networkProxy)
{
	if (m_pSocket)
	{
		m_pSocket->setProxy(networkProxy);
	}
}

/**
	Sets the size of WebSocket's internal read buffer to be size bytes.
	If the buffer size is limited to a certain size, WebSocket won't buffer more than this size of data.
	Exceptionally, a buffer size of 0 means that the read buffer is unlimited and all incoming data is buffered. This is the default.
	This option is useful if you only read the data at certain points in time (e.g., in a real-time streaming application) or if you want to protect your socket against receiving too much data, which may eventually cause your application to run out of memory.
	\sa readBufferSize() and read().
*/
void WebSocket::setReadBufferSize(qint64 size)
{
	if (m_pSocket)
	{
		m_pSocket->setReadBufferSize(size);
	}
}

/*!
	Sets the given \a option to the value described by \a value.
	\sa socketOption().
*/
void WebSocket::setSocketOption(QAbstractSocket::SocketOption option, const QVariant &value)
{
	if (m_pSocket)
	{
		m_pSocket->setSocketOption(option, value);
	}
}

/*!
	Returns the value of the option \a option.
	\sa setSocketOption().
*/
QVariant WebSocket::socketOption(QAbstractSocket::SocketOption option)
{
	QVariant result;
	if (m_pSocket)
	{
		result = m_pSocket->socketOption(option);
	}
	return result;
}

/*!
  Returns true if the WebSocket is valid.
 */
bool WebSocket::isValid()
{
	bool valid = false;
	if (m_pSocket)
	{
		valid = m_pSocket->isValid();
	}
	return valid;
}
