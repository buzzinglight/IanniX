/****************************************************************************
** Meta object code from reading C++ file 'uieditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "transport/uieditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uieditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UiEditor_t {
    QByteArrayData data[10];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UiEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UiEditor_t qt_meta_stringdata_UiEditor = {
    {
QT_MOC_LITERAL(0, 0, 8), // "UiEditor"
QT_MOC_LITERAL(1, 9, 7), // "askSave"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 10), // "askRefresh"
QT_MOC_LITERAL(4, 29, 4), // "save"
QT_MOC_LITERAL(5, 34, 7), // "refresh"
QT_MOC_LITERAL(6, 42, 13), // "cursorChanged"
QT_MOC_LITERAL(7, 56, 11), // "scriptError"
QT_MOC_LITERAL(8, 68, 6), // "errors"
QT_MOC_LITERAL(9, 75, 4) // "line"

    },
    "UiEditor\0askSave\0\0askRefresh\0save\0"
    "refresh\0cursorChanged\0scriptError\0"
    "errors\0line"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UiEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    2,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList, QMetaType::Short,    8,    9,

       0        // eod
};

void UiEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UiEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->askSave(); break;
        case 1: _t->askRefresh(); break;
        case 2: _t->save(); break;
        case 3: _t->refresh(); break;
        case 4: _t->cursorChanged(); break;
        case 5: _t->scriptError((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UiEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiEditor::askSave)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UiEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiEditor::askRefresh)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UiEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_UiEditor.data,
    qt_meta_data_UiEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UiEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UiEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UiEditor.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int UiEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void UiEditor::askSave()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void UiEditor::askRefresh()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
