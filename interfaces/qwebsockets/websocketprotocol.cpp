#include "websocketprotocol.h"
#include <QString>
#include <QSet>
#include <QtEndian>

/*!
	\enum WebSocketProtocol::CloseCode

	The close codes supported by WebSockets V13
	\sa WebSocket::close()
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_NORMAL
	Normal closure
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_GOING_AWAY
	Going away
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_PROTOCOL_ERROR
	Protocol error
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_DATATYPE_NOT_SUPPORTED
	Unsupported data
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_RESERVED_1004
	Reserved
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_MISSING_STATUS_CODE
	No status received
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_ABNORMAL_DISCONNECTION
	Abnormal closure
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_WRONG_DATATYPE
	Invalid frame payload data
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_POLICY_VIOLATED
	Policy violation
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_TOO_MUCH_DATA
	Message too big
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_MISSING_EXTENSION
	Mandatory extension missing
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_BAD_OPERATION
	Internal server error
*/
/*!
	\var WebSocketProtocol::CloseCode::CC_TLS_HANDSHAKE_FAILED
	TLS handshake failed
*/
/*!
	\enum WebSocketProtocol::Version

	\brief The different defined versions of the Websocket protocol.

	For an overview of the differences between the different protocols, see
	<http://code.google.com/p/pywebsocket/wiki/WebSocketProtocolSpec>
*/
/*!
	\var WebSocketProtocol::Version::V_Unknow
*/
/*!
	\var WebSocketProtocol::Version::V_0
	hixie76: http://tools.ietf.org/html/draft-hixie-thewebsocketprotocol-76 & hybi-00: http://tools.ietf.org/html/draft-ietf-hybi-thewebsocketprotocol-00.
	Works with key1, key2 and a key in the payload.\n
	Attribute: Sec-WebSocket-Draft value 0.
*/
/*!
	\var WebSocketProtocol::Version::V_4
	hybi-04: http://tools.ietf.org/id/draft-ietf-hybi-thewebsocketprotocol-04.txt.
	Changed handshake: key1, key2, key3 ==> Sec-WebSocket-Key, Sec-WebSocket-Nonce, Sec-WebSocket-Accept\n
	Sec-WebSocket-Draft renamed to Sec-WebSocket-Version\n
	Sec-WebSocket-Version = 4
*/
/*!
	\var WebSocketProtocol::Version::V_5
	hybi-05: http://tools.ietf.org/id/draft-ietf-hybi-thewebsocketprotocol-05.txt.
	Sec-WebSocket-Version = 5\n
	Removed Sec-WebSocket-Nonce\n
	Added Sec-WebSocket-Accept\n
*/
/*!
	\var WebSocketProtocol::Version::V_6
	Sec-WebSocket-Version = 6.
*/
/*!
	\var WebSocketProtocol::Version::V_7
	hybi-07: http://tools.ietf.org/html/draft-ietf-hybi-thewebsocketprotocol-07.
	Sec-WebSocket-Version = 7
*/
/*!
	\var WebSocketProtocol::Version::V_8
	hybi-8, hybi-9, hybi-10, hybi-11 and hybi-12.
	Status codes 1005 and 1006 are added and all codes are now unsigned\n
	Internal error results in 1006
*/
/*!
	\var WebSocketProtocol::Version::V_13
	hybi-13, hybi14, hybi-15, hybi-16, hybi-17 and RFC 6455.
	Sec-WebSocket-Version = 13\n
	Status code 1004 is now reserved\n
	Added 1008, 1009 and 1010\n
	Must support TLS\n
	Clarify multiple version support
*/
/*!
	\var WebSocketProtocol::Version::V_LATEST
	Refers to the latest know version to QWebSockets.
*/

/*!
  \fn WebSocketProtocol::isOpCodeReserved(OpCode code)
  Checks if \a code is a valid OpCode
  \internal
*/

/*!
  \fn WebSocketProtocol::isCloseCodeValid(int closeCode)
  Checks if \a closeCode is a valid web socket close code
  \internal
*/

/*!
  \fn WebSocketProtocol::getCurrentVersion()
  Returns the latest version that WebSocket is supporting
  \internal
*/

/**
 * @brief Contains constants related to the WebSocket standard.
 */
namespace WebSocketProtocol
{
	/*!
		Parses the \a versionString and converts it to a Version value
		\internal
	*/
	Version versionFromString(const QString &versionString)
	{
		bool ok = false;
		Version version = V_Unknow;
		int ver = versionString.toInt(&ok);
		QSet<Version> supportedVersions;
		supportedVersions << V_0 << V_4 << V_5 << V_6 << V_7 << V_8 << V_13;
		if (ok)
		{
			if (supportedVersions.contains(static_cast<Version>(ver)))
			{
				version = static_cast<Version>(ver);
			}
		}
		return version;
	}

	/*!
	  Mask the \a payload with the given \a maskingKey and stores the result back in \a payload.
	  \internal
	*/
	void mask(QByteArray *payload, quint32 maskingKey)
	{
		quint32 *payloadData = reinterpret_cast<quint32 *>(payload->data());
		quint32 numIterations = static_cast<quint32>(payload->size()) / sizeof(quint32);
		quint32 remainder = static_cast<quint32>(payload->size()) % sizeof(quint32);
		quint32 i;
		for (i = 0; i < numIterations; ++i)
		{
			*(payloadData + i) ^= maskingKey;
		}
		if (remainder)
		{
			const quint32 offset = i * static_cast<quint32>(sizeof(quint32));
			char *payloadBytes = payload->data();
			uchar *mask = reinterpret_cast<uchar *>(&maskingKey);
			for (quint32 i = 0; i < remainder; ++i)
			{
				*(payloadBytes + offset + i) ^= static_cast<char>(mask[(i + offset) % 4]);
			}
		}
	}

	/*!
	  Masks the \a payload of length \a size with the given \a maskingKey and stores the result back in \a payload.
	  \internal
	*/
	void mask(char *payload, quint64 size, quint32 maskingKey)
	{
		quint32 *payloadData = reinterpret_cast<quint32 *>(payload);
		quint32 numIterations = static_cast<quint32>(size / sizeof(quint32));
		quint32 remainder = size % sizeof(quint32);
		quint32 i;
		for (i = 0; i < numIterations; ++i)
		{
			*(payloadData + i) ^= maskingKey;
		}
		if (remainder)
		{
			const quint32 offset = i * static_cast<quint32>(sizeof(quint32));
			uchar *mask = reinterpret_cast<uchar *>(&maskingKey);
			for (quint32 i = 0; i < remainder; ++i)
			{
				*(payload + offset + i) ^= static_cast<char>(mask[(i + offset) % 4]);
			}
		}
	}
}	//end namespace WebSocketProtocol
