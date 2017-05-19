#ifndef HANDSHAKEREQUEST_H
#define HANDSHAKEREQUEST_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QUrl>
#include <QSet>

#include "websocketprotocol.h"

class QTextStream;

class HandshakeRequest
{
public:
	HandshakeRequest(int port, bool isSecure);
	virtual ~HandshakeRequest();

	void clear();

	int getPort() const;
	bool isSecure() const;
	bool isValid() const;
	QMap<QString, QString> getHeaders() const;
	QList<WebSocketProtocol::Version> getVersions() const;
	QString getKey() const;
	QString getOrigin() const;
	QList<QString> getProtocols() const;
	QList<QString> getExtensions() const;
	QUrl getRequestUrl() const;
	QString getResourceName() const;
	QString getHost() const;

private:
	Q_DISABLE_COPY(HandshakeRequest)
	QTextStream &readFromStream(QTextStream &textStream);
	friend QTextStream &operator >>(QTextStream &stream, HandshakeRequest &request);

	int m_port;
	bool m_isSecure;
	bool m_isValid;
	QMap<QString, QString> m_headers;
	QList<WebSocketProtocol::Version> m_versions;
	QString m_key;
	QString m_origin;
	QList<QString> m_protocols;
	QList<QString> m_extensions;
	QUrl m_requestUrl;
};

QTextStream &operator >>(QTextStream &stream, HandshakeRequest &request);

#endif // HANDSHAKEREQUEST_H
