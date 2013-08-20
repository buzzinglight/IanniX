/**
 * @file websocket.h
 * @brief Defines the WebSocket class.
 *
 * \note Currently, only V13 (RFC6455) is supported.
 * \note Both text and binary websockets are supported.
 * \note The secure version (wss) is currently not implemented.
 * @author Kurt Pattyn (pattyn.kurt@gmail.com)
 */

#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QUrl>
#include <QAbstractSocket>
#include <QHostAddress>
#include "websocketprotocol.h"
#include "dataprocessor.h"
#include <QNetworkProxy>
#include <QTime>

class HandshakeRequest;
class HandshakeResponse;
class QTcpSocket;

class WebSocket:public QObject
{
	Q_OBJECT

public:
	explicit WebSocket(QString origin = QString(), WebSocketProtocol::Version version = WebSocketProtocol::V_LATEST, QObject *parent = 0);
	virtual ~WebSocket();

	void abort();
	QAbstractSocket::SocketError error() const;
	QString errorString() const;
	bool flush();
	bool isValid();
	QHostAddress localAddress() const;
	quint16 localPort() const;
	QHostAddress peerAddress() const;
	QString peerName() const;
	quint16 peerPort() const;
	QNetworkProxy proxy() const;
	qint64 readBufferSize() const;
	void setProxy(const QNetworkProxy &networkProxy);
	void setReadBufferSize(qint64 size);
	void setSocketOption(QAbstractSocket::SocketOption option, const QVariant &value);
	QVariant socketOption(QAbstractSocket::SocketOption option);
	QAbstractSocket::SocketState state() const;

	bool waitForConnected(int msecs = 30000);
	bool waitForDisconnected(int msecs = 30000);

	WebSocketProtocol::Version getVersion();
	QString getResourceName();
	QUrl getRequestUrl();
	QString getOrigin();
	QString getProtocol();
	QString getExtension();

	qint64 send(const char *message);
	qint64 send(const QString &message);	//send data as text
	qint64 send(const QByteArray &data);	//send data as binary

public Q_SLOTS:
	virtual void close(WebSocketProtocol::CloseCode closeCode = WebSocketProtocol::CC_NORMAL, QString reason = QString());
	virtual void open(const QUrl &url, bool mask = true);
	void ping();

Q_SIGNALS:
	void aboutToClose();
	void connected();
	void disconnected();
	void stateChanged(QAbstractSocket::SocketState state);
	void proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *pAuthenticator);
	void readChannelFinished();
	void textFrameReceived(QString frame, bool isLastFrame);
	void binaryFrameReceived(QByteArray frame, bool isLastFrame);
	void textMessageReceived(QString message);
	void binaryMessageReceived(QByteArray message);
	void error(QAbstractSocket::SocketError error);
	void pong(quint64 elapsedTime);

private Q_SLOTS:
	void processData();
	void processControlFrame(WebSocketProtocol::OpCode opCode, QByteArray frame);
	void processHandshake(QTcpSocket *pSocket);
	void processStateChanged(QAbstractSocket::SocketState socketState);

private:
	Q_DISABLE_COPY(WebSocket)

	WebSocket(QTcpSocket *pTcpSocket, WebSocketProtocol::Version version, QObject *parent = 0);
	void setVersion(WebSocketProtocol::Version version);
	void setResourceName(QString resourceName);
	void setRequestUrl(QUrl requestUrl);
	void setOrigin(QString origin);
	void setProtocol(QString protocol);
	void setExtension(QString extension);
	void enableMasking(bool enable);
	void setSocketState(QAbstractSocket::SocketState state);
	void setErrorString(QString errorString);

	qint64 doWriteData(const QByteArray &data, bool isBinary);
	qint64 doWriteFrames(const QByteArray &data, bool isBinary);

	void makeConnections(const QTcpSocket *pTcpSocket);
	void releaseConnections(const QTcpSocket *pTcpSocket);

	QByteArray getFrameHeader(WebSocketProtocol::OpCode opCode, quint64 payloadLength, quint32 maskingKey, bool lastFrame) const;
	QString calculateAcceptKey(const QString &key) const;
	QString createHandShakeRequest(QString resourceName,
								   QString host,
								   QString origin,
								   QString extensions,
								   QString protocols,
								   QByteArray key);

	quint32 generateMaskingKey() const;
	QByteArray generateKey() const;
	quint32 generateRandomNumber() const;
	qint64 writeFrames(const QList<QByteArray> &frames);
	qint64 writeFrame(const QByteArray &frame);

	static WebSocket *upgradeFrom(QTcpSocket *tcpSocket,
								  const HandshakeRequest &request,
								  const HandshakeResponse &response,
								  QObject *parent = 0);
	friend class WebSocketServer;

	QTcpSocket *m_pSocket;
	QString m_errorString;
	WebSocketProtocol::Version m_version;
	QUrl m_resource;
	QString m_resourceName;
	QUrl m_requestUrl;
	QString m_origin;
	QString m_protocol;
	QString m_extension;
	QAbstractSocket::SocketState m_socketState;

	QByteArray m_key;	//identification key used in handshake requests

	bool m_mustMask;	//a server must not mask the frames it sends

	bool m_isClosingHandshakeSent;
	bool m_isClosingHandshakeReceived;

	QTime m_pingTimer;

	DataProcessor m_dataProcessor;
};

#endif // WEBSOCKET_H
