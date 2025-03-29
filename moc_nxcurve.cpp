/****************************************************************************
** Meta object code from reading C++ file 'nxcurve.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "objects/nxcurve.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nxcurve.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NxCurve_t {
    QByteArrayData data[28];
    char stringdata0[389];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NxCurve_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NxCurve_t qt_meta_stringdata_NxCurve = {
    {
QT_MOC_LITERAL(0, 0, 7), // "NxCurve"
QT_MOC_LITERAL(1, 8, 9), // "curveType"
QT_MOC_LITERAL(2, 18, 9), // "CurveType"
QT_MOC_LITERAL(3, 28, 18), // "displaycurveeditor"
QT_MOC_LITERAL(4, 47, 20), // "displaycurveresample"
QT_MOC_LITERAL(5, 68, 13), // "setelasticity"
QT_MOC_LITERAL(6, 82, 9), // "setlength"
QT_MOC_LITERAL(7, 92, 9), // "setresize"
QT_MOC_LITERAL(8, 102, 10), // "setresizef"
QT_MOC_LITERAL(9, 113, 11), // "setequation"
QT_MOC_LITERAL(10, 125, 16), // "setequationparam"
QT_MOC_LITERAL(11, 142, 20), // "setequationparamlist"
QT_MOC_LITERAL(12, 163, 19), // "setequationnbpoints"
QT_MOC_LITERAL(13, 183, 16), // "setpointsellipse"
QT_MOC_LITERAL(14, 200, 13), // "removepointat"
QT_MOC_LITERAL(15, 214, 11), // "shiftpoints"
QT_MOC_LITERAL(16, 226, 15), // "translatepoints"
QT_MOC_LITERAL(17, 242, 14), // "translatepoint"
QT_MOC_LITERAL(18, 257, 12), // "setpointsimg"
QT_MOC_LITERAL(19, 270, 14), // "setpointslines"
QT_MOC_LITERAL(20, 285, 13), // "setpointspath"
QT_MOC_LITERAL(21, 299, 12), // "setpointstxt"
QT_MOC_LITERAL(22, 312, 11), // "setpointxat"
QT_MOC_LITERAL(23, 324, 12), // "QList<qreal>"
QT_MOC_LITERAL(24, 337, 11), // "setpointyat"
QT_MOC_LITERAL(25, 349, 11), // "setpointzat"
QT_MOC_LITERAL(26, 361, 10), // "setpointat"
QT_MOC_LITERAL(27, 372, 16) // "setsmoothpointat"

    },
    "NxCurve\0curveType\0CurveType\0"
    "displaycurveeditor\0displaycurveresample\0"
    "setelasticity\0setlength\0setresize\0"
    "setresizef\0setequation\0setequationparam\0"
    "setequationparamlist\0setequationnbpoints\0"
    "setpointsellipse\0removepointat\0"
    "shiftpoints\0translatepoints\0translatepoint\0"
    "setpointsimg\0setpointslines\0setpointspath\0"
    "setpointstxt\0setpointxat\0QList<qreal>\0"
    "setpointyat\0setpointzat\0setpointat\0"
    "setsmoothpointat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NxCurve[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
      25,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x00095009,
       3, QMetaType::Bool, 0x00095003,
       4, QMetaType::Bool, 0x00095003,
       5, QMetaType::QReal, 0x00095003,
       6, QMetaType::QReal, 0x00095003,
       7, QMetaType::QString, 0x00095003,
       8, QMetaType::QReal, 0x00095003,
       9, QMetaType::QString, 0x00095003,
      10, QMetaType::QString, 0x00095003,
      11, QMetaType::QString, 0x00095003,
      12, QMetaType::UShort, 0x00095003,
      13, QMetaType::QString, 0x00095003,
      14, QMetaType::UShort, 0x00095003,
      15, QMetaType::QString, 0x00095003,
      16, QMetaType::QString, 0x00095003,
      17, QMetaType::QString, 0x00095003,
      18, QMetaType::QString, 0x00095003,
      19, QMetaType::QString, 0x00095003,
      20, QMetaType::QString, 0x00095003,
      21, QMetaType::QString, 0x00095003,
      22, 0x80000000 | 23, 0x0009500b,
      24, 0x80000000 | 23, 0x0009500b,
      25, 0x80000000 | 23, 0x0009500b,
      26, 0x80000000 | 23, 0x0009500b,
      27, 0x80000000 | 23, 0x0009500b,

       0        // eod
};

void NxCurve::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 24:
        case 23:
        case 22:
        case 21:
        case 20:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<qreal> >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<NxCurve *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< CurveType*>(_v) = _t->getCurveType(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->getShowPathPointsEditor(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->getShowPathPointsResample(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = _t->getInertie(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = _t->getPathLength(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->getResizeStr(); break;
        case 6: *reinterpret_cast< qreal*>(_v) = _t->getResizeF(); break;
        case 7: *reinterpret_cast< QString*>(_v) = _t->getEquationStr(); break;
        case 8: *reinterpret_cast< QString*>(_v) = _t->getEquationParamStr(); break;
        case 9: *reinterpret_cast< QString*>(_v) = _t->getEquationParamListStr(); break;
        case 10: *reinterpret_cast< quint16*>(_v) = _t->getEquationPoints(); break;
        case 11: *reinterpret_cast< QString*>(_v) = _t->getEllipseStr(); break;
        case 12: *reinterpret_cast< quint16*>(_v) = _t->getRemovePointAt(); break;
        case 13: *reinterpret_cast< QString*>(_v) = _t->getShiftPointAt(); break;
        case 14: *reinterpret_cast< QString*>(_v) = _t->getTranslate(); break;
        case 15: *reinterpret_cast< QString*>(_v) = _t->getTranslatePoint(); break;
        case 16: *reinterpret_cast< QString*>(_v) = _t->getResizeStr(); break;
        case 17: *reinterpret_cast< QString*>(_v) = _t->getResizeStr(); break;
        case 18: *reinterpret_cast< QString*>(_v) = _t->getResizeStr(); break;
        case 19: *reinterpret_cast< QString*>(_v) = _t->getResizeStr(); break;
        case 20: *reinterpret_cast< QList<qreal>*>(_v) = _t->getPointAtList(); break;
        case 21: *reinterpret_cast< QList<qreal>*>(_v) = _t->getPointAtList(); break;
        case 22: *reinterpret_cast< QList<qreal>*>(_v) = _t->getPointAtList(); break;
        case 23: *reinterpret_cast< QList<qreal>*>(_v) = _t->getPointAtList(); break;
        case 24: *reinterpret_cast< QList<qreal>*>(_v) = _t->getPointAtList(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<NxCurve *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setShowPathPointsEditor(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setShowPathPointsResample(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setInertie(*reinterpret_cast< qreal*>(_v)); break;
        case 4: _t->setPathLength(*reinterpret_cast< qreal*>(_v)); break;
        case 5: _t->setResizeStr(*reinterpret_cast< QString*>(_v)); break;
        case 6: _t->setResizeF(*reinterpret_cast< qreal*>(_v)); break;
        case 7: _t->setEquationStr(*reinterpret_cast< QString*>(_v)); break;
        case 8: _t->setEquationParamStr(*reinterpret_cast< QString*>(_v)); break;
        case 9: _t->setEquationParamListStr(*reinterpret_cast< QString*>(_v)); break;
        case 10: _t->setEquationPoints(*reinterpret_cast< quint16*>(_v)); break;
        case 11: _t->setEllipseStr(*reinterpret_cast< QString*>(_v)); break;
        case 12: _t->setRemovePointAt(*reinterpret_cast< quint16*>(_v)); break;
        case 13: _t->setShiftPointAt(*reinterpret_cast< QString*>(_v)); break;
        case 14: _t->setTranslate(*reinterpret_cast< QString*>(_v)); break;
        case 15: _t->setTranslatePoint(*reinterpret_cast< QString*>(_v)); break;
        case 16: _t->setImage(*reinterpret_cast< QString*>(_v)); break;
        case 17: _t->setSVG2(*reinterpret_cast< QString*>(_v)); break;
        case 18: _t->setSVG(*reinterpret_cast< QString*>(_v)); break;
        case 19: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        case 20: _t->setPointXAt(*reinterpret_cast< QList<qreal>*>(_v)); break;
        case 21: _t->setPointYAt(*reinterpret_cast< QList<qreal>*>(_v)); break;
        case 22: _t->setPointZAt(*reinterpret_cast< QList<qreal>*>(_v)); break;
        case 23: _t->setPointAtList(*reinterpret_cast< QList<qreal>*>(_v)); break;
        case 24: _t->setSmoothPointAtList(*reinterpret_cast< QList<qreal>*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_o;
}

QT_INIT_METAOBJECT const QMetaObject NxCurve::staticMetaObject = { {
    QMetaObject::SuperData::link<NxObject::staticMetaObject>(),
    qt_meta_stringdata_NxCurve.data,
    qt_meta_data_NxCurve,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NxCurve::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NxCurve::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NxCurve.stringdata0))
        return static_cast<void*>(this);
    return NxObject::qt_metacast(_clname);
}

int NxCurve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NxObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 25;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 25;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 25;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 25;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 25;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
