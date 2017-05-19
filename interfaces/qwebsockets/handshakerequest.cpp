#include "handshakerequest.h"
#include <QString>
#include <QMap>
#include <QTextStream>
#include <QUrl>
#include <QList>
#include <QStringList>
#include "websocketprotocol.h"

HandshakeRequest::HandshakeRequest(int port, bool isSecure) :
	m_port(port),
	m_isSecure(isSecure),
	m_isValid(false),
	m_headers(),
	m_versions(),
	m_key(),
	m_origin(),
	m_protocols(),
	m_extensions(),
	m_requestUrl()
{
}

HandshakeRequest::~HandshakeRequest()
{
}

void HandshakeRequest::clear()
{
	m_port = -1;
	m_isSecure = false;
	m_isValid = false;
	m_headers.clear();
	m_versions.clear();
	m_key.clear();
	m_origin.clear();
	m_protocols.clear();
	m_extensions.clear();
	m_requestUrl.clear();
}

int HandshakeRequest::getPort() const
{
	return m_requestUrl.port(m_port);
}

bool HandshakeRequest::isSecure() const
{
	return m_isSecure;
}

bool HandshakeRequest::isValid() const
{
	return m_isValid;
}

QMap<QString, QString> HandshakeRequest::getHeaders() const
{
	return m_headers;
}

QList<WebSocketProtocol::Version> HandshakeRequest::getVersions() const
{
	return m_versions;
}

QString HandshakeRequest::getResourceName() const
{
	return m_requestUrl.path();
}

QString HandshakeRequest::getKey() const
{
	return m_key;
}

QString HandshakeRequest::getHost() const
{
	return m_requestUrl.host();
}

QString HandshakeRequest::getOrigin() const
{
	return m_origin;
}

QList<QString> HandshakeRequest::getProtocols() const
{
	return m_protocols;
}

QList<QString> HandshakeRequest::getExtensions() const
{
	return m_extensions;
}

QUrl HandshakeRequest::getRequestUrl() const
{
	return m_requestUrl;
}

QTextStream &HandshakeRequest::readFromStream(QTextStream &textStream)
{
	m_isValid = false;
	clear();
	if (textStream.status() == QTextStream::Ok)
	{
		QString requestLine = textStream.readLine();
		QStringList tokens = requestLine.split(' ', QString::SkipEmptyParts);
		QString verb = tokens[0];
		QString resourceName = tokens[1];
		QString httpProtocol = tokens[2];

		QString headerLine = textStream.readLine();
		m_headers.clear();
		while (!headerLine.isEmpty())
		{
			QStringList headerField = headerLine.split(QString(": "), QString::SkipEmptyParts);
			m_headers.insertMulti(headerField[0], headerField[1]);
			headerLine = textStream.readLine();
		}

		QString host = m_headers.value("Host", "");
		m_requestUrl = QUrl::fromEncoded(resourceName.toLatin1());
		if (m_requestUrl.isRelative())
		{
			m_requestUrl.setHost(host);
		}
		if (m_requestUrl.scheme().isEmpty())
		{
			QString scheme =  isSecure() ? "wss://" : "ws://";
			m_requestUrl.setScheme(scheme);
		}

		QStringList versionLines = m_headers.values("Sec-WebSocket-Version");
		Q_FOREACH(QString versionLine, versionLines)
		{
			QStringList versions = versionLine.split(",", QString::SkipEmptyParts);
			Q_FOREACH(QString version, versions)
			{
				WebSocketProtocol::Version ver = WebSocketProtocol::versionFromString(version.trimmed());
				m_versions << ver;
			}
		}
		qStableSort(m_versions.begin(), m_versions.end(), qGreater<WebSocketProtocol::Version>());	//sort in descending order
		m_key = m_headers.value("Sec-WebSocket-Key", "");
		QString upgrade = m_headers.value("Upgrade", ""); //must be equal to "websocket", case-insensitive
		QString connection = m_headers.value("Connection", "");	//must contain "Upgrade", case-insensitive
		QStringList connectionLine = connection.split(",", QString::SkipEmptyParts);
		QStringList connectionValues;
		Q_FOREACH(QString connection, connectionLine)
		{
			connectionValues << connection.trimmed();
		}

		//optional headers
		m_origin = m_headers.value("Sec-WebSocket-Origin", "");
		QStringList protocolLines = m_headers.values("Sec-WebSocket-Protocol");
		Q_FOREACH(QString protocolLine, protocolLines)
		{
			QStringList protocols = protocolLine.split(",", QString::SkipEmptyParts);
			Q_FOREACH(QString protocol, protocols)
			{
				m_protocols << protocol.trimmed();
			}
		}
		QStringList extensionLines = m_headers.values("Sec-WebSocket-Extensions");
		Q_FOREACH(QString extensionLine, extensionLines)
		{
			QStringList extensions = extensionLine.split(",", QString::SkipEmptyParts);
			Q_FOREACH(QString extension, extensions)
			{
				m_extensions << extension.trimmed();
			}
		}
		//TODO: authentication field

		m_isValid = !(host.isEmpty() ||
					  resourceName.isEmpty() ||
					  m_versions.isEmpty() ||
					  m_key.isEmpty() ||
					  (verb != "GET") ||
					  (httpProtocol != "HTTP/1.1") ||
					  (upgrade.toLower() != "websocket") ||
					  (!connectionValues.contains("upgrade", Qt::CaseInsensitive)));
					  //(connection.toLower() != "upgrade"));
	}
	return textStream;
}

QTextStream &operator >>(QTextStream &stream, HandshakeRequest &request)
{
	return request.readFromStream(stream);
}
