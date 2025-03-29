/****************************************************************************
** Meta object code from reading C++ file 'uitreeview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "items/uitreeview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uitreeview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UiTreeView_t {
    QByteArrayData data[11];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UiTreeView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UiTreeView_t qt_meta_stringdata_UiTreeView = {
    {
QT_MOC_LITERAL(0, 0, 10), // "UiTreeView"
QT_MOC_LITERAL(1, 11, 12), // "actionImport"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 13), // "QFileInfoList"
QT_MOC_LITERAL(4, 39, 22), // "currentDocumentChanged"
QT_MOC_LITERAL(5, 62, 11), // "UiSyncItem*"
QT_MOC_LITERAL(6, 74, 6), // "action"
QT_MOC_LITERAL(7, 81, 9), // "dropEvent"
QT_MOC_LITERAL(8, 91, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(9, 108, 6), // "source"
QT_MOC_LITERAL(10, 115, 11) // "destination"

    },
    "UiTreeView\0actionImport\0\0QFileInfoList\0"
    "currentDocumentChanged\0UiSyncItem*\0"
    "action\0dropEvent\0QTreeWidgetItem*\0"
    "source\0destination"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UiTreeView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   40,    2, 0x0a /* Public */,
       7,    2,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,    9,   10,

       0        // eod
};

void UiTreeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UiTreeView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->actionImport((*reinterpret_cast< const QFileInfoList(*)>(_a[1]))); break;
        case 1: _t->currentDocumentChanged((*reinterpret_cast< UiSyncItem*(*)>(_a[1]))); break;
        case 2: _t->action(); break;
        case 3: _t->dropEvent((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UiTreeView::*)(const QFileInfoList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiTreeView::actionImport)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UiTreeView::*)(UiSyncItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiTreeView::currentDocumentChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UiTreeView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_UiTreeView.data,
    qt_meta_data_UiTreeView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UiTreeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UiTreeView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UiTreeView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int UiTreeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void UiTreeView::actionImport(const QFileInfoList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UiTreeView::currentDocumentChanged(UiSyncItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
