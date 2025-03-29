/****************************************************************************
** Meta object code from reading C++ file 'nxdocument.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "objects/nxdocument.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nxdocument.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NxDocument_t {
    QByteArrayData data[29];
    char stringdata0[279];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NxDocument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NxDocument_t qt_meta_stringdata_NxDocument = {
    {
QT_MOC_LITERAL(0, 0, 10), // "NxDocument"
QT_MOC_LITERAL(1, 11, 11), // "askFileOpen"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "mode"
QT_MOC_LITERAL(4, 29, 11), // "askFileSave"
QT_MOC_LITERAL(5, 41, 13), // "askFileReload"
QT_MOC_LITERAL(6, 55, 12), // "askFileClose"
QT_MOC_LITERAL(7, 68, 4), // "open"
QT_MOC_LITERAL(8, 73, 4), // "save"
QT_MOC_LITERAL(9, 78, 16), // "setCurrentObject"
QT_MOC_LITERAL(10, 95, 9), // "NxObject*"
QT_MOC_LITERAL(11, 105, 14), // "_currentObject"
QT_MOC_LITERAL(12, 120, 15), // "setCurrentGroup"
QT_MOC_LITERAL(13, 136, 8), // "NxGroup*"
QT_MOC_LITERAL(14, 145, 13), // "_currentGroup"
QT_MOC_LITERAL(15, 159, 16), // "getCurrentObject"
QT_MOC_LITERAL(16, 176, 15), // "getCurrentCurve"
QT_MOC_LITERAL(17, 192, 8), // "NxCurve*"
QT_MOC_LITERAL(18, 201, 15), // "getCurrentGroup"
QT_MOC_LITERAL(19, 217, 3), // "ask"
QT_MOC_LITERAL(20, 221, 5), // "group"
QT_MOC_LITERAL(21, 227, 6), // "prompt"
QT_MOC_LITERAL(22, 234, 5), // "value"
QT_MOC_LITERAL(23, 240, 3), // "def"
QT_MOC_LITERAL(24, 244, 4), // "meta"
QT_MOC_LITERAL(25, 249, 7), // "execute"
QT_MOC_LITERAL(26, 257, 7), // "command"
QT_MOC_LITERAL(27, 265, 4), // "load"
QT_MOC_LITERAL(28, 270, 8) // "filename"

    },
    "NxDocument\0askFileOpen\0\0mode\0askFileSave\0"
    "askFileReload\0askFileClose\0open\0save\0"
    "setCurrentObject\0NxObject*\0_currentObject\0"
    "setCurrentGroup\0NxGroup*\0_currentGroup\0"
    "getCurrentObject\0getCurrentCurve\0"
    "NxCurve*\0getCurrentGroup\0ask\0group\0"
    "prompt\0value\0def\0meta\0execute\0command\0"
    "load\0filename"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NxDocument[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       1,    1,   95,    2, 0x0a /* Public */,
       4,    0,   98,    2, 0x0a /* Public */,
       5,    0,   99,    2, 0x0a /* Public */,
       6,    0,  100,    2, 0x0a /* Public */,
       7,    0,  101,    2, 0x0a /* Public */,
       8,    0,  102,    2, 0x0a /* Public */,
       9,    1,  103,    2, 0x0a /* Public */,
      12,    1,  106,    2, 0x0a /* Public */,
      15,    0,  109,    2, 0x0a /* Public */,
      16,    0,  110,    2, 0x0a /* Public */,
      18,    0,  111,    2, 0x0a /* Public */,
      19,    4,  112,    2, 0x0a /* Public */,
      24,    1,  121,    2, 0x0a /* Public */,
      25,    1,  124,    2, 0x0a /* Public */,
      27,    1,  127,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    0x80000000 | 10,
    0x80000000 | 17,
    0x80000000 | 13,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   20,   21,   22,   23,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::QVariant, QMetaType::QString,   26,
    QMetaType::QVariant, QMetaType::QString,   28,

       0        // eod
};

void NxDocument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NxDocument *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->askFileOpen(); break;
        case 1: _t->askFileOpen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->askFileSave(); break;
        case 3: _t->askFileReload(); break;
        case 4: _t->askFileClose(); break;
        case 5: _t->open(); break;
        case 6: _t->save(); break;
        case 7: _t->setCurrentObject((*reinterpret_cast< NxObject*(*)>(_a[1]))); break;
        case 8: _t->setCurrentGroup((*reinterpret_cast< NxGroup*(*)>(_a[1]))); break;
        case 9: { NxObject* _r = _t->getCurrentObject();
            if (_a[0]) *reinterpret_cast< NxObject**>(_a[0]) = std::move(_r); }  break;
        case 10: { NxCurve* _r = _t->getCurrentCurve();
            if (_a[0]) *reinterpret_cast< NxCurve**>(_a[0]) = std::move(_r); }  break;
        case 11: { NxGroup* _r = _t->getCurrentGroup();
            if (_a[0]) *reinterpret_cast< NxGroup**>(_a[0]) = std::move(_r); }  break;
        case 12: _t->ask((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 13: _t->meta((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: { QVariant _r = _t->execute((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 15: { QVariant _r = _t->load((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NxObject* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NxGroup* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NxDocument::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NxDocument.data,
    qt_meta_data_NxDocument,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NxDocument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NxDocument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NxDocument.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QTreeWidgetItem"))
        return static_cast< QTreeWidgetItem*>(this);
    if (!strcmp(_clname, "MessageDispatcher"))
        return static_cast< MessageDispatcher*>(this);
    if (!strcmp(_clname, "NxObjectDispatchProperty"))
        return static_cast< NxObjectDispatchProperty*>(this);
    return QObject::qt_metacast(_clname);
}

int NxDocument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
