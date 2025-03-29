/****************************************************************************
** Meta object code from reading C++ file 'application.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "misc/application.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'application.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ApplicationCurrent_t {
    QByteArrayData data[21];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ApplicationCurrent_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ApplicationCurrent_t qt_meta_stringdata_ApplicationCurrent = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ApplicationCurrent"
QT_MOC_LITERAL(1, 19, 17), // "openMessageEditor"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 12), // "pushSnapshot"
QT_MOC_LITERAL(4, 51, 8), // "getCount"
QT_MOC_LITERAL(5, 60, 10), // "objectType"
QT_MOC_LITERAL(6, 71, 9), // "serialize"
QT_MOC_LITERAL(7, 81, 12), // "readyToStart"
QT_MOC_LITERAL(8, 94, 13), // "getMainWindow"
QT_MOC_LITERAL(9, 108, 12), // "QMainWindow*"
QT_MOC_LITERAL(10, 121, 16), // "getRenderPreview"
QT_MOC_LITERAL(11, 138, 16), // "UiRenderPreview*"
QT_MOC_LITERAL(12, 155, 21), // "getPerformancePreview"
QT_MOC_LITERAL(13, 177, 9), // "timerTrig"
QT_MOC_LITERAL(14, 187, 6), // "object"
QT_MOC_LITERAL(15, 194, 5), // "force"
QT_MOC_LITERAL(16, 200, 14), // "waitForMessage"
QT_MOC_LITERAL(17, 215, 13), // "getObjectById"
QT_MOC_LITERAL(18, 229, 2), // "id"
QT_MOC_LITERAL(19, 232, 15), // "executeAsScript"
QT_MOC_LITERAL(20, 248, 6) // "script"

    },
    "ApplicationCurrent\0openMessageEditor\0"
    "\0pushSnapshot\0getCount\0objectType\0"
    "serialize\0readyToStart\0getMainWindow\0"
    "QMainWindow*\0getRenderPreview\0"
    "UiRenderPreview*\0getPerformancePreview\0"
    "timerTrig\0object\0force\0waitForMessage\0"
    "getObjectById\0id\0executeAsScript\0"
    "script"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ApplicationCurrent[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    1,   86,    2, 0x0a /* Public */,
       4,    0,   89,    2, 0x2a /* Public | MethodCloned */,
       6,    0,   90,    2, 0x0a /* Public */,
       7,    0,   91,    2, 0x0a /* Public */,
       8,    0,   92,    2, 0x0a /* Public */,
      10,    0,   93,    2, 0x0a /* Public */,
      12,    0,   94,    2, 0x0a /* Public */,
      13,    2,   95,    2, 0x0a /* Public */,
      13,    1,  100,    2, 0x2a /* Public | MethodCloned */,
      16,    0,  103,    2, 0x0a /* Public */,
      17,    1,  104,    2, 0x0a /* Public */,
      19,    1,  107,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::UShort, QMetaType::SChar,    5,
    QMetaType::UShort,
    QMetaType::QString,
    QMetaType::Void,
    0x80000000 | 9,
    0x80000000 | 11,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::Bool,   14,   15,
    QMetaType::Void, QMetaType::VoidStar,   14,
    QMetaType::QString,
    QMetaType::VoidStar, QMetaType::UShort,   18,
    QMetaType::Void, QMetaType::QString,   20,

       0        // eod
};

void ApplicationCurrent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ApplicationCurrent *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openMessageEditor(); break;
        case 1: _t->pushSnapshot(); break;
        case 2: { quint16 _r = _t->getCount((*reinterpret_cast< qint8(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 3: { quint16 _r = _t->getCount();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->serialize();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->readyToStart(); break;
        case 6: { QMainWindow* _r = _t->getMainWindow();
            if (_a[0]) *reinterpret_cast< QMainWindow**>(_a[0]) = std::move(_r); }  break;
        case 7: { UiRenderPreview* _r = _t->getRenderPreview();
            if (_a[0]) *reinterpret_cast< UiRenderPreview**>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->getPerformancePreview();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->timerTrig((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 10: _t->timerTrig((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 11: { QString _r = _t->waitForMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: { void* _r = _t->getObjectById((*reinterpret_cast< quint16(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< void**>(_a[0]) = std::move(_r); }  break;
        case 13: _t->executeAsScript((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ApplicationCurrent::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ApplicationCurrent.data,
    qt_meta_data_ApplicationCurrent,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ApplicationCurrent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApplicationCurrent::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ApplicationCurrent.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ApplicationExecute"))
        return static_cast< ApplicationExecute*>(this);
    return QObject::qt_metacast(_clname);
}

int ApplicationCurrent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
    return _id;
}
struct qt_meta_stringdata_Application_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Application_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Application_t qt_meta_stringdata_Application = {
    {
QT_MOC_LITERAL(0, 0, 11) // "Application"

    },
    "Application"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Application[] = {

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

void Application::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject Application::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Application.data,
    qt_meta_data_Application,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Application::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Application::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Application.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Application::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
