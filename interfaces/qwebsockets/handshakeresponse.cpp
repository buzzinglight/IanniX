#include "handshakeresponse.h"
#include "handshakerequest.h"
#include <QString>
#include <QTextStream>
#include <QByteArray>
#include <QStringList>
#include <QDateTime>
#include <QCryptographicHash>
#include <QSet>
#include <QList>

HandshakeResponse::HandshakeResponse(const HandshakeRequest &request,
									 const QList<WebSocketProtocol::Version> &supportedVersions,
									 const QList<QString> &supportedProtocols,
									 const QList<QString> &supportedExtensions) :
	m_isValid(false),
	m_canUpgrade(false),
	m_response(),
	m_acceptedProtocol(),
	m_acceptedExtension(),
	m_acceptedVersion(WebSocketProtocol::V_Unknow)
{
	m_response = getHandshakeResponse(request, supportedVersions, supportedProtocols, supportedExtensions);
	m_isValid = true;
}

HandshakeResponse::~HandshakeResponse()
{
}

bool HandshakeResponse::isValid() const
{
	return m_isValid;
}

bool HandshakeResponse::canUpgrade() const
{
	return m_isValid && m_canUpgrade;
}

QString HandshakeResponse::getAcceptedProtocol() const
{
	return m_acceptedProtocol;
}

QString HandshakeResponse::calculateAcceptKey(const QString &key) const
{
	QString tmpKey = key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";	//the UID comes from RFC6455
	QByteArray hash = QCryptographicHash::hash(tmpKey.toLatin1(), QCryptographicHash::Sha1);
	return QString(hash.toBase64());
}

QString HandshakeResponse::getHandshakeResponse(const HandshakeRequest &request,
												const QList<WebSocketProtocol::Version> &supportedVersions,
												const QList<QString> &supportedProtocols,
												const QList<QString> &supportedExtensions)
{
	QStringList response;
	m_canUpgrade = false;
	if (request.isValid())
	{
		QString acceptKey = calculateAcceptKey(request.getKey());
		QList<QString> matchingProtocols = supportedProtocols.toSet().intersect(request.getProtocols().toSet()).toList();
		QList<QString> matchingExtensions = supportedExtensions.toSet().intersect(request.getExtensions().toSet()).toList();
		QList<WebSocketProtocol::Version> matchingVersions = request.getVersions().toSet().intersect(supportedVersions.toSet()).toList();
		qStableSort(matchingVersions.begin(), matchingVersions.end(), qGreater<WebSocketProtocol::Version>());	//sort in descending order

		if (matchingVersions.isEmpty())
		{
			m_canUpgrade = false;
		}
		else
		{
			response << "HTTP/1.1 101 Switching Protocols" <<
						"Upgrade: websocket" <<
						"Connection: Upgrade" <<
						"Sec-WebSocket-Accept: " + acceptKey;
			if (!matchingProtocols.isEmpty())
			{
				m_acceptedProtocol = matchingProtocols.first();
				response << "Sec-WebSocket-Protocol: " + m_acceptedProtocol;
			}
			if (!matchingExtensions.isEmpty())
			{
				m_acceptedExtension = matchingExtensions.first();
				response << "Sec-WebSocket-Extensions: " + m_acceptedExtension;
			}
			QString origin = request.getOrigin().trimmed();
			if (origin.isEmpty())
			{
				origin = "*";
			}
			//TODO: header values should be configurable; i.e. Server, Allow-Credentials, Allow-Headers
			response << "Server: Imagine Delivery Server" <<
						"Access-Control-Allow-Credentials: true" <<
						"Access-Control-Allow-Headers: content-type" <<
						"Access-Control-Allow-Origin: " + origin <<
						"Date: " + QDateTime::currentDateTimeUtc().toString("ddd, dd MMM yyyy hh:mm:ss 'GMT'");

			m_acceptedVersion = WebSocketProtocol::getCurrentVersion();
			m_canUpgrade = true;
		}
	}
	else
	{
		m_canUpgrade = false;
	}
	if (!m_canUpgrade)
	{
		response << "HTTP/1.1 400 Bad Request";
		QStringList versions;
		Q_FOREACH(WebSocketProtocol::Version version, supportedVersions)
		{
			versions << QString::number(static_cast<int>(version));
		}
		response << "Sec-WebSocket-Version: " + versions.join(", ");
	}
	response << "\r\n";	//append empty line at end of header
	return response.join("\r\n");
}

QTextStream &HandshakeResponse::writeToStream(QTextStream &textStream) const
{
	if (!m_response.isEmpty())
	{
		textStream << m_response.toLatin1().constData();
	}
	else
	{
		textStream.setStatus(QTextStream::WriteFailed);
	}
	return textStream;
}

QTextStream &operator <<(QTextStream &stream, const HandshakeResponse &response)
{
	return response.writeToStream(stream);
}

WebSocketProtocol::Version HandshakeResponse::getAcceptedVersion() const
{
	return m_acceptedVersion;
}

QString HandshakeResponse::getAcceptedExtension() const
{
	return m_acceptedExtension;
}
