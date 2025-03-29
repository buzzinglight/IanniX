/****************************************************************************
** Meta object code from reading C++ file 'transport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "transport/transport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TransportCpu_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TransportCpu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TransportCpu_t qt_meta_stringdata_TransportCpu = {
    {
QT_MOC_LITERAL(0, 0, 12) // "TransportCpu"

    },
    "TransportCpu"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TransportCpu[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void TransportCpu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject TransportCpu::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_TransportCpu.data,
    qt_meta_data_TransportCpu,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TransportCpu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransportCpu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TransportCpu.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int TransportCpu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_Transport_t {
    QByteArrayData data[9];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Transport_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Transport_t qt_meta_stringdata_Transport = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Transport"
QT_MOC_LITERAL(1, 10, 16), // "forceOpenGLtimer"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 19), // "forceSchedulerTimer"
QT_MOC_LITERAL(4, 48, 6), // "action"
QT_MOC_LITERAL(5, 55, 4), // "zoom"
QT_MOC_LITERAL(6, 60, 5), // "speed"
QT_MOC_LITERAL(7, 66, 6), // "center"
QT_MOC_LITERAL(8, 73, 6) // "rotate"

    },
    "Transport\0forceOpenGLtimer\0\0"
    "forceSchedulerTimer\0action\0zoom\0speed\0"
    "center\0rotate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Transport[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       4,   36, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       3,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, QMetaType::QReal,    2,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags
       5, QMetaType::QReal, 0x00095103,
       6, QMetaType::QReal, 0x00095103,
       7, QMetaType::QString, 0x00095003,
       8, QMetaType::QString, 0x00095003,

       0        // eod
};

void Transport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Transport *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->forceOpenGLtimer((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->forceSchedulerTimer((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 2: _t->action(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Transport::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Transport::forceOpenGLtimer)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Transport::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Transport::forceSchedulerTimer)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Transport *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->getZoom(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->getSpeed(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getCenterStr(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->getRotateStr(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Transport *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setZoom(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setSpeed(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setCenterStr(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setRotateStr(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Transport::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Transport.data,
    qt_meta_data_Transport,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Transport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Transport::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Transport.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NxObjectDispatchProperty"))
        return static_cast< NxObjectDispatchProperty*>(this);
    return QWidget::qt_metacast(_clname);
}

int Transport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Transport::forceOpenGLtimer(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Transport::forceSchedulerTimer(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
