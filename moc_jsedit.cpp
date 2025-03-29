/****************************************************************************
** Meta object code from reading C++ file 'jsedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "gui/qjsedit/jsedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jsedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_JSEdit_t {
    QByteArrayData data[24];
    char stringdata0[287];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JSEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JSEdit_t qt_meta_stringdata_JSEdit = {
    {
QT_MOC_LITERAL(0, 0, 6), // "JSEdit"
QT_MOC_LITERAL(1, 7, 13), // "updateSidebar"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 4), // "mark"
QT_MOC_LITERAL(4, 27, 3), // "str"
QT_MOC_LITERAL(5, 31, 19), // "Qt::CaseSensitivity"
QT_MOC_LITERAL(6, 51, 4), // "sens"
QT_MOC_LITERAL(7, 56, 26), // "setBracketsMatchingEnabled"
QT_MOC_LITERAL(8, 83, 6), // "enable"
QT_MOC_LITERAL(9, 90, 21), // "setCodeFoldingEnabled"
QT_MOC_LITERAL(10, 112, 21), // "setLineNumbersVisible"
QT_MOC_LITERAL(11, 134, 7), // "visible"
QT_MOC_LITERAL(12, 142, 18), // "setTextWrapEnabled"
QT_MOC_LITERAL(13, 161, 4), // "fold"
QT_MOC_LITERAL(14, 166, 4), // "line"
QT_MOC_LITERAL(15, 171, 6), // "unfold"
QT_MOC_LITERAL(16, 178, 10), // "toggleFold"
QT_MOC_LITERAL(17, 189, 12), // "updateCursor"
QT_MOC_LITERAL(18, 202, 4), // "rect"
QT_MOC_LITERAL(19, 207, 1), // "d"
QT_MOC_LITERAL(20, 209, 23), // "bracketsMatchingEnabled"
QT_MOC_LITERAL(21, 233, 18), // "codeFoldingEnabled"
QT_MOC_LITERAL(22, 252, 18), // "lineNumbersVisible"
QT_MOC_LITERAL(23, 271, 15) // "textWrapEnabled"

    },
    "JSEdit\0updateSidebar\0\0mark\0str\0"
    "Qt::CaseSensitivity\0sens\0"
    "setBracketsMatchingEnabled\0enable\0"
    "setCodeFoldingEnabled\0setLineNumbersVisible\0"
    "visible\0setTextWrapEnabled\0fold\0line\0"
    "unfold\0toggleFold\0updateCursor\0rect\0"
    "d\0bracketsMatchingEnabled\0codeFoldingEnabled\0"
    "lineNumbersVisible\0textWrapEnabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JSEdit[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       4,  110, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    2,   75,    2, 0x0a /* Public */,
       3,    1,   80,    2, 0x2a /* Public | MethodCloned */,
       7,    1,   83,    2, 0x0a /* Public */,
       9,    1,   86,    2, 0x0a /* Public */,
      10,    1,   89,    2, 0x0a /* Public */,
      12,    1,   92,    2, 0x0a /* Public */,
      13,    1,   95,    2, 0x0a /* Public */,
      15,    1,   98,    2, 0x0a /* Public */,
      16,    1,  101,    2, 0x0a /* Public */,
      17,    0,  104,    2, 0x08 /* Private */,
       1,    2,  105,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect, QMetaType::Int,   18,   19,

 // properties: name, type, flags
      20, QMetaType::Bool, 0x00095103,
      21, QMetaType::Bool, 0x00095103,
      22, QMetaType::Bool, 0x00095103,
      23, QMetaType::Bool, 0x00095103,

       0        // eod
};

void JSEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<JSEdit *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateSidebar(); break;
        case 1: _t->mark((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< Qt::CaseSensitivity(*)>(_a[2]))); break;
        case 2: _t->mark((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->setBracketsMatchingEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setCodeFoldingEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setLineNumbersVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setTextWrapEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->fold((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->unfold((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->toggleFold((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->updateCursor(); break;
        case 11: _t->updateSidebar((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<JSEdit *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isBracketsMatchingEnabled(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isCodeFoldingEnabled(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isLineNumbersVisible(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->isTextWrapEnabled(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<JSEdit *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBracketsMatchingEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setCodeFoldingEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setLineNumbersVisible(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setTextWrapEnabled(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject JSEdit::staticMetaObject = { {
    QMetaObject::SuperData::link<QPlainTextEdit::staticMetaObject>(),
    qt_meta_stringdata_JSEdit.data,
    qt_meta_data_JSEdit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *JSEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JSEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JSEdit.stringdata0))
        return static_cast<void*>(this);
    return QPlainTextEdit::qt_metacast(_clname);
}

int JSEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
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
