/**
 * @file websocketserver.h
 * @author Kurt Pattyn (pattyn.kurt@gmail.com)
 * @brief Defines the WebSocketServer class.
 */

#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QQueue>
#include <QString>
#include <QHostAddress>
#include "websocket.h"

class QTcpServer;

class WebSocketServerImp;

class WebSocketServer : public QObject
{
	Q_OBJECT

public:
	explicit WebSocketServer(QObject *parent = 0);
	virtual ~WebSocketServer();

	void close();
	QString errorString() const;
	bool hasPendingConnections() const;
	bool isListening() const;
	bool listen(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
	int maxPendingConnections() const;
	virtual WebSocket *nextPendingConnection();
	QNetworkProxy proxy() const;
	QHostAddress serverAddress() const;
	QAbstractSocket::SocketError serverError() const;
	quint16 serverPort() const;
	void setMaxPendingConnections(int numConnections);
	void setProxy(const QNetworkProxy &networkProxy);
	bool setSocketDescriptor(int socketDescriptor);
	int socketDescriptor() const;
	bool waitForNewConnection(int msec = 0, bool *timedOut = 0);

	QList<WebSocketProtocol::Version> getSupportedVersions() const;
	QList<QString> getSupportedProtocols() const;
	QList<QString> getSupportedExtensions() const;

Q_SIGNALS:
	void newConnection();

private Q_SLOTS:
	void onNewConnection();
	void onCloseConnection();
	void handshakeReceived();

private:
	Q_DISABLE_COPY(WebSocketServer)

	QTcpServer *m_pTcpServer;
	QQueue<WebSocket *> m_pendingConnections;

	void addPendingConnection(WebSocket *pWebSocket);
};

#endif // WEBSOCKETSERVER_H
