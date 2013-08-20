#ifndef HANDSHAKERESPONSE_H
#define HANDSHAKERESPONSE_H

#include <QObject>
#include "websocketprotocol.h"

class HandshakeRequest;
class QString;
class QTextStream;

class HandshakeResponse:public QObject
{
	Q_OBJECT
public:
	HandshakeResponse(const HandshakeRequest &request,
					  const QList<WebSocketProtocol::Version> &supportedVersions,
					  const QList<QString> &supportedProtocols,
					  const QList<QString> &supportedExtensions);

	virtual ~HandshakeResponse();

	bool isValid() const;
	bool canUpgrade() const;
	QString getAcceptedProtocol() const;
	QString getAcceptedExtension() const;
	WebSocketProtocol::Version getAcceptedVersion() const;

public Q_SLOTS:

Q_SIGNALS:

private:
	Q_DISABLE_COPY(HandshakeResponse)
	bool m_isValid;
	bool m_canUpgrade;
	QString m_response;
	QString m_acceptedProtocol;
	QString m_acceptedExtension;
	WebSocketProtocol::Version m_acceptedVersion;

	QString calculateAcceptKey(const QString &key) const;
	QString getHandshakeResponse(const HandshakeRequest &request,
								 const QList<WebSocketProtocol::Version> &supportedVersions,
								 const QList<QString> &supportedProtocols,
								 const QList<QString> &supportedExtensions);

	QTextStream &writeToStream(QTextStream &textStream) const;
	friend QTextStream &operator <<(QTextStream &stream, const HandshakeResponse &response);
};

#endif // HANDSHAKERESPONSE_H
