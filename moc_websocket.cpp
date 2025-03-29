/****************************************************************************
** Meta object code from reading C++ file 'websocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "interfaces/qwebsockets/websocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'websocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WebSocket_t {
    QByteArrayData data[42];
    char stringdata0[557];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WebSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WebSocket_t qt_meta_stringdata_WebSocket = {
    {
QT_MOC_LITERAL(0, 0, 9), // "WebSocket"
QT_MOC_LITERAL(1, 10, 12), // "aboutToClose"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "connected"
QT_MOC_LITERAL(4, 34, 12), // "disconnected"
QT_MOC_LITERAL(5, 47, 12), // "stateChanged"
QT_MOC_LITERAL(6, 60, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(7, 89, 5), // "state"
QT_MOC_LITERAL(8, 95, 27), // "proxyAuthenticationRequired"
QT_MOC_LITERAL(9, 123, 13), // "QNetworkProxy"
QT_MOC_LITERAL(10, 137, 5), // "proxy"
QT_MOC_LITERAL(11, 143, 15), // "QAuthenticator*"
QT_MOC_LITERAL(12, 159, 14), // "pAuthenticator"
QT_MOC_LITERAL(13, 174, 19), // "readChannelFinished"
QT_MOC_LITERAL(14, 194, 17), // "textFrameReceived"
QT_MOC_LITERAL(15, 212, 5), // "frame"
QT_MOC_LITERAL(16, 218, 11), // "isLastFrame"
QT_MOC_LITERAL(17, 230, 19), // "binaryFrameReceived"
QT_MOC_LITERAL(18, 250, 19), // "textMessageReceived"
QT_MOC_LITERAL(19, 270, 7), // "message"
QT_MOC_LITERAL(20, 278, 21), // "binaryMessageReceived"
QT_MOC_LITERAL(21, 300, 5), // "error"
QT_MOC_LITERAL(22, 306, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(23, 335, 4), // "pong"
QT_MOC_LITERAL(24, 340, 11), // "elapsedTime"
QT_MOC_LITERAL(25, 352, 5), // "close"
QT_MOC_LITERAL(26, 358, 28), // "WebSocketProtocol::CloseCode"
QT_MOC_LITERAL(27, 387, 9), // "closeCode"
QT_MOC_LITERAL(28, 397, 6), // "reason"
QT_MOC_LITERAL(29, 404, 4), // "open"
QT_MOC_LITERAL(30, 409, 3), // "url"
QT_MOC_LITERAL(31, 413, 4), // "mask"
QT_MOC_LITERAL(32, 418, 4), // "ping"
QT_MOC_LITERAL(33, 423, 11), // "processData"
QT_MOC_LITERAL(34, 435, 19), // "processControlFrame"
QT_MOC_LITERAL(35, 455, 25), // "WebSocketProtocol::OpCode"
QT_MOC_LITERAL(36, 481, 6), // "opCode"
QT_MOC_LITERAL(37, 488, 16), // "processHandshake"
QT_MOC_LITERAL(38, 505, 11), // "QTcpSocket*"
QT_MOC_LITERAL(39, 517, 7), // "pSocket"
QT_MOC_LITERAL(40, 525, 19), // "processStateChanged"
QT_MOC_LITERAL(41, 545, 11) // "socketState"

    },
    "WebSocket\0aboutToClose\0\0connected\0"
    "disconnected\0stateChanged\0"
    "QAbstractSocket::SocketState\0state\0"
    "proxyAuthenticationRequired\0QNetworkProxy\0"
    "proxy\0QAuthenticator*\0pAuthenticator\0"
    "readChannelFinished\0textFrameReceived\0"
    "frame\0isLastFrame\0binaryFrameReceived\0"
    "textMessageReceived\0message\0"
    "binaryMessageReceived\0error\0"
    "QAbstractSocket::SocketError\0pong\0"
    "elapsedTime\0close\0WebSocketProtocol::CloseCode\0"
    "closeCode\0reason\0open\0url\0mask\0ping\0"
    "processData\0processControlFrame\0"
    "WebSocketProtocol::OpCode\0opCode\0"
    "processHandshake\0QTcpSocket*\0pSocket\0"
    "processStateChanged\0socketState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebSocket[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  124,    2, 0x06 /* Public */,
       3,    0,  125,    2, 0x06 /* Public */,
       4,    0,  126,    2, 0x06 /* Public */,
       5,    1,  127,    2, 0x06 /* Public */,
       8,    2,  130,    2, 0x06 /* Public */,
      13,    0,  135,    2, 0x06 /* Public */,
      14,    2,  136,    2, 0x06 /* Public */,
      17,    2,  141,    2, 0x06 /* Public */,
      18,    1,  146,    2, 0x06 /* Public */,
      20,    1,  149,    2, 0x06 /* Public */,
      21,    1,  152,    2, 0x06 /* Public */,
      23,    1,  155,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      25,    2,  158,    2, 0x0a /* Public */,
      25,    1,  163,    2, 0x2a /* Public | MethodCloned */,
      25,    0,  166,    2, 0x2a /* Public | MethodCloned */,
      29,    2,  167,    2, 0x0a /* Public */,
      29,    1,  172,    2, 0x2a /* Public | MethodCloned */,
      32,    0,  175,    2, 0x0a /* Public */,
      33,    0,  176,    2, 0x08 /* Private */,
      34,    2,  177,    2, 0x08 /* Private */,
      37,    1,  182,    2, 0x08 /* Private */,
      40,    1,  185,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11,   10,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   15,   16,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Bool,   15,   16,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::QByteArray,   19,
    QMetaType::Void, 0x80000000 | 22,   21,
    QMetaType::Void, QMetaType::ULongLong,   24,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 26, QMetaType::QString,   27,   28,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QUrl, QMetaType::Bool,   30,   31,
    QMetaType::Void, QMetaType::QUrl,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 35, QMetaType::QByteArray,   36,   15,
    QMetaType::Void, 0x80000000 | 38,   39,
    QMetaType::Void, 0x80000000 | 6,   41,

       0        // eod
};

void WebSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WebSocket *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->aboutToClose(); break;
        case 1: _t->connected(); break;
        case 2: _t->disconnected(); break;
        case 3: _t->stateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 4: _t->proxyAuthenticationRequired((*reinterpret_cast< const QNetworkProxy(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 5: _t->readChannelFinished(); break;
        case 6: _t->textFrameReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->binaryFrameReceived((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->textMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->binaryMessageReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 10: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 11: _t->pong((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        case 12: _t->close((*reinterpret_cast< WebSocketProtocol::CloseCode(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: _t->close((*reinterpret_cast< WebSocketProtocol::CloseCode(*)>(_a[1]))); break;
        case 14: _t->close(); break;
        case 15: _t->open((*reinterpret_cast< const QUrl(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 16: _t->open((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 17: _t->ping(); break;
        case 18: _t->processData(); break;
        case 19: _t->processControlFrame((*reinterpret_cast< WebSocketProtocol::OpCode(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 20: _t->processHandshake((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 21: _t->processStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkProxy >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WebSocket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocket::aboutToClose)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WebSocket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocket::connected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WebSocket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocket::disconnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WebSocket::*)(QAbstractSocket::SocketState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocket::stateChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WebSocket::*)(const QNetworkProxy & , QAuthenticator * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocket::proxyAuthenticationRequired)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WebSocket::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocket::readChannelFinished)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (WebSocket::*)(QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocket::textFrameReceived)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (WebSocket::*)(QByteArray , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocket::binaryFrameReceived)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (WebSocket::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocket::textMessageReceived)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (WebSocket::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocket::binaryMessageReceived)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (WebSocket::*)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocket::error)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (WebSocket::*)(quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebSocket::pong)) {
                *result = 11;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WebSocket::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_WebSocket.data,
    qt_meta_data_WebSocket,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WebSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WebSocket.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WebSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void WebSocket::aboutToClose()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WebSocket::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WebSocket::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WebSocket::stateChanged(QAbstractSocket::SocketState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WebSocket::proxyAuthenticationRequired(const QNetworkProxy & _t1, QAuthenticator * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WebSocket::readChannelFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void WebSocket::textFrameReceived(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void WebSocket::binaryFrameReceived(QByteArray _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void WebSocket::textMessageReceived(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void WebSocket::binaryMessageReceived(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void WebSocket::error(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void WebSocket::pong(quint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
