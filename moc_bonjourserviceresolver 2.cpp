/****************************************************************************
** Meta object code from reading C++ file 'bonjourserviceresolver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "interfaces/zeroconf/bonjourserviceresolver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bonjourserviceresolver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BonjourServiceResolver_t {
    QByteArrayData data[11];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BonjourServiceResolver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BonjourServiceResolver_t qt_meta_stringdata_BonjourServiceResolver = {
    {
QT_MOC_LITERAL(0, 0, 22), // "BonjourServiceResolver"
QT_MOC_LITERAL(1, 23, 21), // "bonjourRecordResolved"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 9), // "QHostInfo"
QT_MOC_LITERAL(4, 56, 8), // "hostInfo"
QT_MOC_LITERAL(5, 65, 4), // "port"
QT_MOC_LITERAL(6, 70, 5), // "error"
QT_MOC_LITERAL(7, 76, 19), // "DNSServiceErrorType"
QT_MOC_LITERAL(8, 96, 22), // "bonjourSocketReadyRead"
QT_MOC_LITERAL(9, 119, 14), // "cleanupResolve"
QT_MOC_LITERAL(10, 134, 13) // "finishConnect"

    },
    "BonjourServiceResolver\0bonjourRecordResolved\0"
    "\0QHostInfo\0hostInfo\0port\0error\0"
    "DNSServiceErrorType\0bonjourSocketReadyRead\0"
    "cleanupResolve\0finishConnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BonjourServiceResolver[] = {

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
       1,    2,   39,    2, 0x06 /* Public */,
       6,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   47,    2, 0x08 /* Private */,
       9,    0,   48,    2, 0x08 /* Private */,
      10,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void BonjourServiceResolver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BonjourServiceResolver *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->bonjourRecordResolved((*reinterpret_cast< const QHostInfo(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->error((*reinterpret_cast< DNSServiceErrorType(*)>(_a[1]))); break;
        case 2: _t->bonjourSocketReadyRead(); break;
        case 3: _t->cleanupResolve(); break;
        case 4: _t->finishConnect((*reinterpret_cast< const QHostInfo(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BonjourServiceResolver::*)(const QHostInfo & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BonjourServiceResolver::bonjourRecordResolved)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BonjourServiceResolver::*)(DNSServiceErrorType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BonjourServiceResolver::error)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BonjourServiceResolver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BonjourServiceResolver.data,
    qt_meta_data_BonjourServiceResolver,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BonjourServiceResolver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BonjourServiceResolver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BonjourServiceResolver.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BonjourServiceResolver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void BonjourServiceResolver::bonjourRecordResolved(const QHostInfo & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BonjourServiceResolver::error(DNSServiceErrorType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
