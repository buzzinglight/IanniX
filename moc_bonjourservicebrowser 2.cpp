/****************************************************************************
** Meta object code from reading C++ file 'bonjourservicebrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "interfaces/zeroconf/bonjourservicebrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bonjourservicebrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BonjourServiceBrowser_t {
    QByteArrayData data[9];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BonjourServiceBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BonjourServiceBrowser_t qt_meta_stringdata_BonjourServiceBrowser = {
    {
QT_MOC_LITERAL(0, 0, 21), // "BonjourServiceBrowser"
QT_MOC_LITERAL(1, 22, 28), // "currentBonjourRecordsChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 20), // "QList<BonjourRecord>"
QT_MOC_LITERAL(4, 73, 4), // "list"
QT_MOC_LITERAL(5, 78, 5), // "error"
QT_MOC_LITERAL(6, 84, 19), // "DNSServiceErrorType"
QT_MOC_LITERAL(7, 104, 3), // "err"
QT_MOC_LITERAL(8, 108, 22) // "bonjourSocketReadyRead"

    },
    "BonjourServiceBrowser\0"
    "currentBonjourRecordsChanged\0\0"
    "QList<BonjourRecord>\0list\0error\0"
    "DNSServiceErrorType\0err\0bonjourSocketReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BonjourServiceBrowser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void BonjourServiceBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BonjourServiceBrowser *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->currentBonjourRecordsChanged((*reinterpret_cast< const QList<BonjourRecord>(*)>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< DNSServiceErrorType(*)>(_a[1]))); break;
        case 2: _t->bonjourSocketReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<BonjourRecord> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BonjourServiceBrowser::*)(const QList<BonjourRecord> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BonjourServiceBrowser::currentBonjourRecordsChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BonjourServiceBrowser::*)(DNSServiceErrorType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BonjourServiceBrowser::error)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BonjourServiceBrowser::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BonjourServiceBrowser.data,
    qt_meta_data_BonjourServiceBrowser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BonjourServiceBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BonjourServiceBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BonjourServiceBrowser.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BonjourServiceBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void BonjourServiceBrowser::currentBonjourRecordsChanged(const QList<BonjourRecord> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BonjourServiceBrowser::error(DNSServiceErrorType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
