/****************************************************************************
** Meta object code from reading C++ file 'nxtrigger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "objects/nxtrigger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nxtrigger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NxTrigger_t {
    QByteArrayData data[7];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NxTrigger_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NxTrigger_t qt_meta_stringdata_NxTrigger = {
    {
QT_MOC_LITERAL(0, 0, 9), // "NxTrigger"
QT_MOC_LITERAL(1, 10, 7), // "trigEnd"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 16), // "settextureactive"
QT_MOC_LITERAL(4, 36, 18), // "settextureinactive"
QT_MOC_LITERAL(5, 55, 13), // "settriggeroff"
QT_MOC_LITERAL(6, 69, 4) // "trig"

    },
    "NxTrigger\0trigEnd\0\0settextureactive\0"
    "settextureinactive\0settriggeroff\0trig"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NxTrigger[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       4,   20, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags
       3, QMetaType::QString, 0x00095003,
       4, QMetaType::QString, 0x00095003,
       5, QMetaType::QReal, 0x00095003,
       6, QMetaType::Bool, 0x00095003,

       0        // eod
};

void NxTrigger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NxTrigger *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->trigEnd(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<NxTrigger *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getTextureActive(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getTextureInactive(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = _t->getTriggerOff(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->getForceTrig(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<NxTrigger *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTextureActive(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setTextureInactive(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setTriggerOff(*reinterpret_cast< qreal*>(_v)); break;
        case 3: _t->setForceTrig(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject NxTrigger::staticMetaObject = { {
    QMetaObject::SuperData::link<NxObject::staticMetaObject>(),
    qt_meta_stringdata_NxTrigger.data,
    qt_meta_data_NxTrigger,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NxTrigger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NxTrigger::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NxTrigger.stringdata0))
        return static_cast<void*>(this);
    return NxObject::qt_metacast(_clname);
}

int NxTrigger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NxObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
