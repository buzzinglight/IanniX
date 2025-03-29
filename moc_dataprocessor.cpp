/****************************************************************************
** Meta object code from reading C++ file 'dataprocessor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "interfaces/qwebsockets/dataprocessor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataprocessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataProcessor_t {
    QByteArrayData data[20];
    char stringdata0[270];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataProcessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataProcessor_t qt_meta_stringdata_DataProcessor = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DataProcessor"
QT_MOC_LITERAL(1, 14, 20), // "controlFrameReceived"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 25), // "WebSocketProtocol::OpCode"
QT_MOC_LITERAL(4, 62, 6), // "opCode"
QT_MOC_LITERAL(5, 69, 5), // "frame"
QT_MOC_LITERAL(6, 75, 17), // "textFrameReceived"
QT_MOC_LITERAL(7, 93, 9), // "lastFrame"
QT_MOC_LITERAL(8, 103, 19), // "binaryFrameReceived"
QT_MOC_LITERAL(9, 123, 19), // "textMessageReceived"
QT_MOC_LITERAL(10, 143, 7), // "message"
QT_MOC_LITERAL(11, 151, 21), // "binaryMessageReceived"
QT_MOC_LITERAL(12, 173, 16), // "errorEncountered"
QT_MOC_LITERAL(13, 190, 28), // "WebSocketProtocol::CloseCode"
QT_MOC_LITERAL(14, 219, 4), // "code"
QT_MOC_LITERAL(15, 224, 11), // "description"
QT_MOC_LITERAL(16, 236, 7), // "process"
QT_MOC_LITERAL(17, 244, 11), // "QTcpSocket*"
QT_MOC_LITERAL(18, 256, 7), // "pSocket"
QT_MOC_LITERAL(19, 264, 5) // "clear"

    },
    "DataProcessor\0controlFrameReceived\0\0"
    "WebSocketProtocol::OpCode\0opCode\0frame\0"
    "textFrameReceived\0lastFrame\0"
    "binaryFrameReceived\0textMessageReceived\0"
    "message\0binaryMessageReceived\0"
    "errorEncountered\0WebSocketProtocol::CloseCode\0"
    "code\0description\0process\0QTcpSocket*\0"
    "pSocket\0clear"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataProcessor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       6,    2,   59,    2, 0x06 /* Public */,
       8,    2,   64,    2, 0x06 /* Public */,
       9,    1,   69,    2, 0x06 /* Public */,
      11,    1,   72,    2, 0x06 /* Public */,
      12,    2,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,   80,    2, 0x0a /* Public */,
      19,    0,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QByteArray,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    5,    7,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Bool,    5,    7,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void, 0x80000000 | 13, QMetaType::QString,   14,   15,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,

       0        // eod
};

void DataProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataProcessor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->controlFrameReceived((*reinterpret_cast< WebSocketProtocol::OpCode(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: _t->textFrameReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->binaryFrameReceived((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->textMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->binaryMessageReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->errorEncountered((*reinterpret_cast< WebSocketProtocol::CloseCode(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->process((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 7: _t->clear(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataProcessor::*)(WebSocketProtocol::OpCode , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::controlFrameReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DataProcessor::*)(QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::textFrameReceived)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DataProcessor::*)(QByteArray , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::binaryFrameReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DataProcessor::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::textMessageReceived)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DataProcessor::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::binaryMessageReceived)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DataProcessor::*)(WebSocketProtocol::CloseCode , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataProcessor::errorEncountered)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataProcessor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DataProcessor.data,
    qt_meta_data_DataProcessor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataProcessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void DataProcessor::controlFrameReceived(WebSocketProtocol::OpCode _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataProcessor::textFrameReceived(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DataProcessor::binaryFrameReceived(QByteArray _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DataProcessor::textMessageReceived(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DataProcessor::binaryMessageReceived(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DataProcessor::errorEncountered(WebSocketProtocol::CloseCode _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
