/****************************************************************************
** Meta object code from reading C++ file 'interfacehttp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "interfaces/interfacehttp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interfacehttp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_InterfaceHttpServer_t {
    QByteArrayData data[9];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InterfaceHttpServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InterfaceHttpServer_t qt_meta_stringdata_InterfaceHttpServer = {
    {
QT_MOC_LITERAL(0, 0, 19), // "InterfaceHttpServer"
QT_MOC_LITERAL(1, 20, 12), // "parseRequest"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 14), // "QNetworkReply*"
QT_MOC_LITERAL(4, 49, 11), // "parseSocket"
QT_MOC_LITERAL(5, 61, 11), // "QTcpSocket*"
QT_MOC_LITERAL(6, 73, 10), // "readClient"
QT_MOC_LITERAL(7, 84, 13), // "discardClient"
QT_MOC_LITERAL(8, 98, 5) // "parse"

    },
    "InterfaceHttpServer\0parseRequest\0\0"
    "QNetworkReply*\0parseSocket\0QTcpSocket*\0"
    "readClient\0discardClient\0parse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InterfaceHttpServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   45,    2, 0x08 /* Private */,
       7,    0,   46,    2, 0x08 /* Private */,
       8,    1,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void InterfaceHttpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InterfaceHttpServer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->parseRequest((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: _t->parseSocket((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 2: _t->readClient(); break;
        case 3: _t->discardClient(); break;
        case 4: _t->parse((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (InterfaceHttpServer::*)(QNetworkReply * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InterfaceHttpServer::parseRequest)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (InterfaceHttpServer::*)(QTcpSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InterfaceHttpServer::parseSocket)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject InterfaceHttpServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QTcpServer::staticMetaObject>(),
    qt_meta_stringdata_InterfaceHttpServer.data,
    qt_meta_data_InterfaceHttpServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *InterfaceHttpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InterfaceHttpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InterfaceHttpServer.stringdata0))
        return static_cast<void*>(this);
    return QTcpServer::qt_metacast(_clname);
}

int InterfaceHttpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void InterfaceHttpServer::parseRequest(QNetworkReply * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void InterfaceHttpServer::parseSocket(QTcpSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_InterfaceHttp_t {
    QByteArrayData data[15];
    char stringdata0[264];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InterfaceHttp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InterfaceHttp_t qt_meta_stringdata_InterfaceHttp = {
    {
QT_MOC_LITERAL(0, 0, 13), // "InterfaceHttp"
QT_MOC_LITERAL(1, 14, 11), // "portChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "parseRequest"
QT_MOC_LITERAL(4, 40, 14), // "QNetworkReply*"
QT_MOC_LITERAL(5, 55, 11), // "parseSocket"
QT_MOC_LITERAL(6, 67, 11), // "QTcpSocket*"
QT_MOC_LITERAL(7, 79, 21), // "portWebSocketsChanged"
QT_MOC_LITERAL(8, 101, 23), // "webSocketsNewConnection"
QT_MOC_LITERAL(9, 125, 24), // "webSocketsProcessMessage"
QT_MOC_LITERAL(10, 150, 7), // "message"
QT_MOC_LITERAL(11, 158, 30), // "webSocketsProcessBinaryMessage"
QT_MOC_LITERAL(12, 189, 28), // "webSocketsSocketDisconnected"
QT_MOC_LITERAL(13, 218, 32), // "webSocketsUpdateConnectedClients"
QT_MOC_LITERAL(14, 251, 12) // "openExamples"

    },
    "InterfaceHttp\0portChanged\0\0parseRequest\0"
    "QNetworkReply*\0parseSocket\0QTcpSocket*\0"
    "portWebSocketsChanged\0webSocketsNewConnection\0"
    "webSocketsProcessMessage\0message\0"
    "webSocketsProcessBinaryMessage\0"
    "webSocketsSocketDisconnected\0"
    "webSocketsUpdateConnectedClients\0"
    "openExamples"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InterfaceHttp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    1,   65,    2, 0x08 /* Private */,
       5,    1,   68,    2, 0x08 /* Private */,
       7,    0,   71,    2, 0x08 /* Private */,
       8,    0,   72,    2, 0x08 /* Private */,
       9,    1,   73,    2, 0x08 /* Private */,
      11,    1,   76,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,
      13,    0,   80,    2, 0x08 /* Private */,
      14,    0,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void InterfaceHttp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InterfaceHttp *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->portChanged(); break;
        case 1: _t->parseRequest((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->parseSocket((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 3: _t->portWebSocketsChanged(); break;
        case 4: _t->webSocketsNewConnection(); break;
        case 5: _t->webSocketsProcessMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->webSocketsProcessBinaryMessage((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 7: _t->webSocketsSocketDisconnected(); break;
        case 8: _t->webSocketsUpdateConnectedClients(); break;
        case 9: _t->openExamples(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject InterfaceHttp::staticMetaObject = { {
    QMetaObject::SuperData::link<NetworkInterface::staticMetaObject>(),
    qt_meta_stringdata_InterfaceHttp.data,
    qt_meta_data_InterfaceHttp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *InterfaceHttp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InterfaceHttp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InterfaceHttp.stringdata0))
        return static_cast<void*>(this);
    return NetworkInterface::qt_metacast(_clname);
}

int InterfaceHttp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NetworkInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
