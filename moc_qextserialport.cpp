/****************************************************************************
** Meta object code from reading C++ file 'qextserialport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "interfaces/qextserialport/qextserialport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qextserialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QextSerialPort_t {
    QByteArrayData data[28];
    char stringdata0[278];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QextSerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QextSerialPort_t qt_meta_stringdata_QextSerialPort = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QextSerialPort"
QT_MOC_LITERAL(1, 15, 10), // "dsrChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 6), // "status"
QT_MOC_LITERAL(4, 34, 11), // "setPortName"
QT_MOC_LITERAL(5, 46, 4), // "name"
QT_MOC_LITERAL(6, 51, 12), // "setQueryMode"
QT_MOC_LITERAL(7, 64, 9), // "QueryMode"
QT_MOC_LITERAL(8, 74, 4), // "mode"
QT_MOC_LITERAL(9, 79, 11), // "setBaudRate"
QT_MOC_LITERAL(10, 91, 12), // "BaudRateType"
QT_MOC_LITERAL(11, 104, 11), // "setDataBits"
QT_MOC_LITERAL(12, 116, 12), // "DataBitsType"
QT_MOC_LITERAL(13, 129, 9), // "setParity"
QT_MOC_LITERAL(14, 139, 10), // "ParityType"
QT_MOC_LITERAL(15, 150, 11), // "setStopBits"
QT_MOC_LITERAL(16, 162, 12), // "StopBitsType"
QT_MOC_LITERAL(17, 175, 14), // "setFlowControl"
QT_MOC_LITERAL(18, 190, 8), // "FlowType"
QT_MOC_LITERAL(19, 199, 10), // "setTimeout"
QT_MOC_LITERAL(20, 210, 6), // "setDtr"
QT_MOC_LITERAL(21, 217, 3), // "set"
QT_MOC_LITERAL(22, 221, 6), // "setRts"
QT_MOC_LITERAL(23, 228, 10), // "_q_canRead"
QT_MOC_LITERAL(24, 239, 8), // "portName"
QT_MOC_LITERAL(25, 248, 9), // "queryMode"
QT_MOC_LITERAL(26, 258, 7), // "Polling"
QT_MOC_LITERAL(27, 266, 11) // "EventDriven"

    },
    "QextSerialPort\0dsrChanged\0\0status\0"
    "setPortName\0name\0setQueryMode\0QueryMode\0"
    "mode\0setBaudRate\0BaudRateType\0setDataBits\0"
    "DataBitsType\0setParity\0ParityType\0"
    "setStopBits\0StopBitsType\0setFlowControl\0"
    "FlowType\0setTimeout\0setDtr\0set\0setRts\0"
    "_q_canRead\0portName\0queryMode\0Polling\0"
    "EventDriven"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QextSerialPort[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       2,  120, // properties
       1,  126, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   87,    2, 0x0a /* Public */,
       6,    1,   90,    2, 0x0a /* Public */,
       9,    1,   93,    2, 0x0a /* Public */,
      11,    1,   96,    2, 0x0a /* Public */,
      13,    1,   99,    2, 0x0a /* Public */,
      15,    1,  102,    2, 0x0a /* Public */,
      17,    1,  105,    2, 0x0a /* Public */,
      19,    1,  108,    2, 0x0a /* Public */,
      20,    1,  111,    2, 0x0a /* Public */,
      20,    0,  114,    2, 0x2a /* Public | MethodCloned */,
      22,    1,  115,    2, 0x0a /* Public */,
      22,    0,  118,    2, 0x2a /* Public | MethodCloned */,
      23,    0,  119,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 18,    2,
    QMetaType::Void, QMetaType::Long,    2,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      24, QMetaType::QString, 0x00095103,
      25, 0x80000000 | 7, 0x0009510b,

 // enums: name, alias, flags, count, data
       7,    7, 0x0,    2,  131,

 // enum data: key, value
      26, uint(QextSerialPort::Polling),
      27, uint(QextSerialPort::EventDriven),

       0        // eod
};

void QextSerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QextSerialPort *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dsrChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setPortName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setQueryMode((*reinterpret_cast< QueryMode(*)>(_a[1]))); break;
        case 3: _t->setBaudRate((*reinterpret_cast< BaudRateType(*)>(_a[1]))); break;
        case 4: _t->setDataBits((*reinterpret_cast< DataBitsType(*)>(_a[1]))); break;
        case 5: _t->setParity((*reinterpret_cast< ParityType(*)>(_a[1]))); break;
        case 6: _t->setStopBits((*reinterpret_cast< StopBitsType(*)>(_a[1]))); break;
        case 7: _t->setFlowControl((*reinterpret_cast< FlowType(*)>(_a[1]))); break;
        case 8: _t->setTimeout((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 9: _t->setDtr((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setDtr(); break;
        case 11: _t->setRts((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->setRts(); break;
        case 13: _t->d_func()->_q_canRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QextSerialPort::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QextSerialPort::dsrChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QextSerialPort *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->portName(); break;
        case 1: *reinterpret_cast< QueryMode*>(_v) = _t->queryMode(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QextSerialPort *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPortName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setQueryMode(*reinterpret_cast< QueryMode*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject QextSerialPort::staticMetaObject = { {
    QMetaObject::SuperData::link<QIODevice::staticMetaObject>(),
    qt_meta_stringdata_QextSerialPort.data,
    qt_meta_data_QextSerialPort,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QextSerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QextSerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QextSerialPort.stringdata0))
        return static_cast<void*>(this);
    return QIODevice::qt_metacast(_clname);
}

int QextSerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QIODevice::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QextSerialPort::dsrChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
