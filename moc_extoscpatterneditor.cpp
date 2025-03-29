/****************************************************************************
** Meta object code from reading C++ file 'extoscpatterneditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "interfaces/extoscpatterneditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'extoscpatterneditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QPlainTextEditWithFocus_t {
    QByteArrayData data[4];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QPlainTextEditWithFocus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QPlainTextEditWithFocus_t qt_meta_stringdata_QPlainTextEditWithFocus = {
    {
QT_MOC_LITERAL(0, 0, 23), // "QPlainTextEditWithFocus"
QT_MOC_LITERAL(1, 24, 8), // "focusOut"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7) // "focusIn"

    },
    "QPlainTextEditWithFocus\0focusOut\0\0"
    "focusIn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QPlainTextEditWithFocus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QPlainTextEditWithFocus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QPlainTextEditWithFocus *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->focusOut(); break;
        case 1: _t->focusIn(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QPlainTextEditWithFocus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QPlainTextEditWithFocus::focusOut)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QPlainTextEditWithFocus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QPlainTextEditWithFocus::focusIn)) {
                *result = 1;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject QPlainTextEditWithFocus::staticMetaObject = { {
    QMetaObject::SuperData::link<QPlainTextEdit::staticMetaObject>(),
    qt_meta_stringdata_QPlainTextEditWithFocus.data,
    qt_meta_data_QPlainTextEditWithFocus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QPlainTextEditWithFocus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QPlainTextEditWithFocus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QPlainTextEditWithFocus.stringdata0))
        return static_cast<void*>(this);
    return QPlainTextEdit::qt_metacast(_clname);
}

int QPlainTextEditWithFocus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QPlainTextEditWithFocus::focusOut()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QPlainTextEditWithFocus::focusIn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_QComboBoxWithFocus_t {
    QByteArrayData data[4];
    char stringdata0[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QComboBoxWithFocus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QComboBoxWithFocus_t qt_meta_stringdata_QComboBoxWithFocus = {
    {
QT_MOC_LITERAL(0, 0, 18), // "QComboBoxWithFocus"
QT_MOC_LITERAL(1, 19, 8), // "focusOut"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 7) // "focusIn"

    },
    "QComboBoxWithFocus\0focusOut\0\0focusIn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QComboBoxWithFocus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QComboBoxWithFocus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QComboBoxWithFocus *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->focusOut(); break;
        case 1: _t->focusIn(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QComboBoxWithFocus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QComboBoxWithFocus::focusOut)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QComboBoxWithFocus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QComboBoxWithFocus::focusIn)) {
                *result = 1;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject QComboBoxWithFocus::staticMetaObject = { {
    QMetaObject::SuperData::link<QComboBox::staticMetaObject>(),
    qt_meta_stringdata_QComboBoxWithFocus.data,
    qt_meta_data_QComboBoxWithFocus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QComboBoxWithFocus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QComboBoxWithFocus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QComboBoxWithFocus.stringdata0))
        return static_cast<void*>(this);
    return QComboBox::qt_metacast(_clname);
}

int QComboBoxWithFocus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QComboBoxWithFocus::focusOut()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QComboBoxWithFocus::focusIn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_ExtOscPatternEditor_t {
    QByteArrayData data[13];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExtOscPatternEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExtOscPatternEditor_t qt_meta_stringdata_ExtOscPatternEditor = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ExtOscPatternEditor"
QT_MOC_LITERAL(1, 20, 17), // "actionRouteRemove"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 20), // "ExtOscPatternEditor*"
QT_MOC_LITERAL(4, 60, 16), // "actionRouteFocus"
QT_MOC_LITERAL(5, 77, 10), // "QComboBox*"
QT_MOC_LITERAL(6, 88, 15), // "QPlainTextEdit*"
QT_MOC_LITERAL(7, 104, 18), // "currentItemChanged"
QT_MOC_LITERAL(8, 123, 18), // "textPatternChanged"
QT_MOC_LITERAL(9, 142, 13), // "clearApattern"
QT_MOC_LITERAL(10, 156, 12), // "fieldFocusIn"
QT_MOC_LITERAL(11, 169, 5), // "learn"
QT_MOC_LITERAL(12, 175, 13) // "applyTemplate"

    },
    "ExtOscPatternEditor\0actionRouteRemove\0"
    "\0ExtOscPatternEditor*\0actionRouteFocus\0"
    "QComboBox*\0QPlainTextEdit*\0"
    "currentItemChanged\0textPatternChanged\0"
    "clearApattern\0fieldFocusIn\0learn\0"
    "applyTemplate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExtOscPatternEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    2,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   62,    2, 0x0a /* Public */,
       8,    0,   63,    2, 0x0a /* Public */,
       9,    0,   64,    2, 0x0a /* Public */,
      10,    0,   65,    2, 0x0a /* Public */,
      11,    0,   66,    2, 0x0a /* Public */,
      12,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 6,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ExtOscPatternEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ExtOscPatternEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->actionRouteRemove((*reinterpret_cast< ExtOscPatternEditor*(*)>(_a[1]))); break;
        case 1: _t->actionRouteFocus((*reinterpret_cast< QComboBox*(*)>(_a[1])),(*reinterpret_cast< QPlainTextEdit*(*)>(_a[2]))); break;
        case 2: _t->currentItemChanged(); break;
        case 3: _t->textPatternChanged(); break;
        case 4: _t->clearApattern(); break;
        case 5: _t->fieldFocusIn(); break;
        case 6: _t->learn(); break;
        case 7: _t->applyTemplate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ExtOscPatternEditor* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QComboBox* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QPlainTextEdit* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ExtOscPatternEditor::*)(ExtOscPatternEditor * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExtOscPatternEditor::actionRouteRemove)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ExtOscPatternEditor::*)(QComboBox * , QPlainTextEdit * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExtOscPatternEditor::actionRouteFocus)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ExtOscPatternEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ExtOscPatternEditor.data,
    qt_meta_data_ExtOscPatternEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExtOscPatternEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExtOscPatternEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExtOscPatternEditor.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ExtOscPatternEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ExtOscPatternEditor::actionRouteRemove(ExtOscPatternEditor * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExtOscPatternEditor::actionRouteFocus(QComboBox * _t1, QPlainTextEdit * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
