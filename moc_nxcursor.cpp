/****************************************************************************
** Meta object code from reading C++ file 'nxcursor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "objects/nxcursor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nxcursor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NxCursor_t {
    QByteArrayData data[16];
    char stringdata0[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NxCursor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NxCursor_t qt_meta_stringdata_NxCursor = {
    {
QT_MOC_LITERAL(0, 0, 8), // "NxCursor"
QT_MOC_LITERAL(1, 9, 9), // "setoffset"
QT_MOC_LITERAL(2, 19, 10), // "setpattern"
QT_MOC_LITERAL(3, 30, 19), // "setboundssourcemode"
QT_MOC_LITERAL(4, 50, 15), // "setboundssource"
QT_MOC_LITERAL(5, 66, 15), // "setboundstarget"
QT_MOC_LITERAL(6, 82, 8), // "setspeed"
QT_MOC_LITERAL(7, 91, 9), // "setspeedf"
QT_MOC_LITERAL(8, 101, 8), // "setwidth"
QT_MOC_LITERAL(9, 110, 8), // "setdepth"
QT_MOC_LITERAL(10, 119, 7), // "settime"
QT_MOC_LITERAL(11, 127, 14), // "settimepercent"
QT_MOC_LITERAL(12, 142, 7), // "setfire"
QT_MOC_LITERAL(13, 150, 4), // "trig"
QT_MOC_LITERAL(14, 155, 16), // "settextureactive"
QT_MOC_LITERAL(15, 172, 18) // "settextureinactive"

    },
    "NxCursor\0setoffset\0setpattern\0"
    "setboundssourcemode\0setboundssource\0"
    "setboundstarget\0setspeed\0setspeedf\0"
    "setwidth\0setdepth\0settime\0settimepercent\0"
    "setfire\0trig\0settextureactive\0"
    "settextureinactive"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NxCursor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
      15,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QString, 0x00095003,
       2, QMetaType::QString, 0x00095003,
       3, QMetaType::UShort, 0x00095003,
       4, QMetaType::QString, 0x00095003,
       5, QMetaType::QString, 0x00095003,
       6, QMetaType::QString, 0x00095003,
       7, QMetaType::QReal, 0x00095003,
       8, QMetaType::QReal, 0x00095003,
       9, QMetaType::QReal, 0x00095003,
      10, QMetaType::QReal, 0x00095003,
      11, QMetaType::QReal, 0x00095003,
      12, QMetaType::QString, 0x00095003,
      13, QMetaType::Bool, 0x00095003,
      14, QMetaType::QString, 0x00095003,
      15, QMetaType::QString, 0x00095003,

       0        // eod
};

void NxCursor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<NxCursor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getOffset(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getStart(); break;
        case 2: *reinterpret_cast< quint16*>(_v) = _t->getBoundsSourceMode(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->getBoundsSource(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->getBoundsTarget(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->getTimeFactorStr(); break;
        case 6: *reinterpret_cast< qreal*>(_v) = _t->getTimeFactorF(); break;
        case 7: *reinterpret_cast< qreal*>(_v) = _t->getWidth(); break;
        case 8: *reinterpret_cast< qreal*>(_v) = _t->getDepth(); break;
        case 9: *reinterpret_cast< qreal*>(_v) = _t->getTimeLocal(); break;
        case 10: *reinterpret_cast< qreal*>(_v) = _t->getTimeLocalPercent(); break;
        case 11: *reinterpret_cast< QString*>(_v) = _t->getFire(); break;
        case 12: *reinterpret_cast< bool*>(_v) = _t->getForceTrig(); break;
        case 13: *reinterpret_cast< QString*>(_v) = _t->getTextureActive(); break;
        case 14: *reinterpret_cast< QString*>(_v) = _t->getTextureInactive(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<NxCursor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setOffset(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setStart(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setBoundsSourceMode(*reinterpret_cast< quint16*>(_v)); break;
        case 3: _t->setBoundsSource(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setBoundsTarget(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setTimeFactorStr(*reinterpret_cast< QString*>(_v)); break;
        case 6: _t->setTimeFactorF(*reinterpret_cast< qreal*>(_v)); break;
        case 7: _t->setWidth(*reinterpret_cast< qreal*>(_v)); break;
        case 8: _t->setDepth(*reinterpret_cast< qreal*>(_v)); break;
        case 9: _t->setTimeLocal(*reinterpret_cast< qreal*>(_v)); break;
        case 10: _t->setTimeLocalPercent(*reinterpret_cast< qreal*>(_v)); break;
        case 11: _t->setFire(*reinterpret_cast< QString*>(_v)); break;
        case 12: _t->setForceTrig(*reinterpret_cast< bool*>(_v)); break;
        case 13: _t->setTextureActive(*reinterpret_cast< QString*>(_v)); break;
        case 14: _t->setTextureInactive(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject NxCursor::staticMetaObject = { {
    QMetaObject::SuperData::link<NxObject::staticMetaObject>(),
    qt_meta_stringdata_NxCursor.data,
    qt_meta_data_NxCursor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NxCursor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NxCursor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NxCursor.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NxCursorAbstraction"))
        return static_cast< NxCursorAbstraction*>(this);
    return NxObject::qt_metacast(_clname);
}

int NxCursor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NxObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 15;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 15;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 15;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 15;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 15;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
