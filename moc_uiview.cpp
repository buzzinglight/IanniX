/****************************************************************************
** Meta object code from reading C++ file 'uiview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "gui/uiview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uiview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UiView_t {
    QByteArrayData data[66];
    char stringdata0[1073];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UiView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UiView_t qt_meta_stringdata_UiView = {
    {
QT_MOC_LITERAL(0, 0, 6), // "UiView"
QT_MOC_LITERAL(1, 7, 9), // "forceGoto"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 14), // "arrangeObjects"
QT_MOC_LITERAL(4, 33, 4), // "type"
QT_MOC_LITERAL(5, 38, 23), // "actionRouteReloadScript"
QT_MOC_LITERAL(6, 62, 20), // "actionRouteImportSVG"
QT_MOC_LITERAL(7, 83, 27), // "actionRouteImportBackground"
QT_MOC_LITERAL(8, 111, 21), // "actionRouteImportText"
QT_MOC_LITERAL(9, 133, 21), // "actionRouteCloseEvent"
QT_MOC_LITERAL(10, 155, 12), // "QCloseEvent*"
QT_MOC_LITERAL(11, 168, 30), // "fullscreenDisplaysCountChanged"
QT_MOC_LITERAL(12, 199, 26), // "fullscreenDisplaysSelected"
QT_MOC_LITERAL(13, 226, 9), // "showTimer"
QT_MOC_LITERAL(14, 236, 8), // "showHelp"
QT_MOC_LITERAL(15, 245, 13), // "showTransport"
QT_MOC_LITERAL(16, 259, 13), // "showInspector"
QT_MOC_LITERAL(17, 273, 10), // "showEditor"
QT_MOC_LITERAL(18, 284, 26), // "actionToggleBorderlessMode"
QT_MOC_LITERAL(19, 311, 16), // "toggleFullscreen"
QT_MOC_LITERAL(20, 328, 14), // "goToFullscreen"
QT_MOC_LITERAL(21, 343, 11), // "screenIndex"
QT_MOC_LITERAL(22, 355, 13), // "escFullscreen"
QT_MOC_LITERAL(23, 369, 16), // "actionPlay_pause"
QT_MOC_LITERAL(24, 386, 17), // "actionFast_rewind"
QT_MOC_LITERAL(25, 404, 17), // "actionPerformance"
QT_MOC_LITERAL(26, 422, 18), // "actionReloadScript"
QT_MOC_LITERAL(27, 441, 15), // "actionImportSVG"
QT_MOC_LITERAL(28, 457, 22), // "actionImportBackground"
QT_MOC_LITERAL(29, 480, 16), // "actionImportText"
QT_MOC_LITERAL(30, 497, 15), // "actionAlign_top"
QT_MOC_LITERAL(31, 513, 16), // "actionAlign_left"
QT_MOC_LITERAL(32, 530, 18), // "actionAlign_bottom"
QT_MOC_LITERAL(33, 549, 17), // "actionAlign_right"
QT_MOC_LITERAL(34, 567, 18), // "actionAlign_middle"
QT_MOC_LITERAL(35, 586, 18), // "actionAlign_center"
QT_MOC_LITERAL(36, 605, 17), // "actionDistributeH"
QT_MOC_LITERAL(37, 623, 17), // "actionDistributeV"
QT_MOC_LITERAL(38, 641, 18), // "actionAlign_circle"
QT_MOC_LITERAL(39, 660, 19), // "actionAlign_ellipse"
QT_MOC_LITERAL(40, 680, 14), // "actionSnapshot"
QT_MOC_LITERAL(41, 695, 12), // "actionResize"
QT_MOC_LITERAL(42, 708, 4), // "size"
QT_MOC_LITERAL(43, 713, 10), // "gridChange"
QT_MOC_LITERAL(44, 724, 19), // "actionPatchesFolder"
QT_MOC_LITERAL(45, 744, 12), // "unToogleDraw"
QT_MOC_LITERAL(46, 757, 2), // "id"
QT_MOC_LITERAL(47, 760, 25), // "actionDrawFreeCurveSimple"
QT_MOC_LITERAL(48, 786, 26), // "actionDrawPointCurveSimple"
QT_MOC_LITERAL(49, 813, 19), // "actionDrawFreeCurve"
QT_MOC_LITERAL(50, 833, 6), // "cursor"
QT_MOC_LITERAL(51, 840, 20), // "actionDrawPointCurve"
QT_MOC_LITERAL(52, 861, 18), // "actionDrawTriggers"
QT_MOC_LITERAL(53, 880, 17), // "actionAddTimeline"
QT_MOC_LITERAL(54, 898, 19), // "actionAddFreeCursor"
QT_MOC_LITERAL(55, 918, 17), // "actionCircleCurve"
QT_MOC_LITERAL(56, 936, 18), // "actionAddMathCurve"
QT_MOC_LITERAL(57, 955, 24), // "actionAddMathCurveSimple"
QT_MOC_LITERAL(58, 980, 12), // "editingStart"
QT_MOC_LITERAL(59, 993, 7), // "NxPoint"
QT_MOC_LITERAL(60, 1001, 11), // "editingStop"
QT_MOC_LITERAL(61, 1013, 25), // "editingStopWithoutRemoval"
QT_MOC_LITERAL(62, 1039, 6), // "isLoop"
QT_MOC_LITERAL(63, 1046, 11), // "editingMove"
QT_MOC_LITERAL(64, 1058, 3), // "add"
QT_MOC_LITERAL(65, 1062, 10) // "mouseState"

    },
    "UiView\0forceGoto\0\0arrangeObjects\0type\0"
    "actionRouteReloadScript\0actionRouteImportSVG\0"
    "actionRouteImportBackground\0"
    "actionRouteImportText\0actionRouteCloseEvent\0"
    "QCloseEvent*\0fullscreenDisplaysCountChanged\0"
    "fullscreenDisplaysSelected\0showTimer\0"
    "showHelp\0showTransport\0showInspector\0"
    "showEditor\0actionToggleBorderlessMode\0"
    "toggleFullscreen\0goToFullscreen\0"
    "screenIndex\0escFullscreen\0actionPlay_pause\0"
    "actionFast_rewind\0actionPerformance\0"
    "actionReloadScript\0actionImportSVG\0"
    "actionImportBackground\0actionImportText\0"
    "actionAlign_top\0actionAlign_left\0"
    "actionAlign_bottom\0actionAlign_right\0"
    "actionAlign_middle\0actionAlign_center\0"
    "actionDistributeH\0actionDistributeV\0"
    "actionAlign_circle\0actionAlign_ellipse\0"
    "actionSnapshot\0actionResize\0size\0"
    "gridChange\0actionPatchesFolder\0"
    "unToogleDraw\0id\0actionDrawFreeCurveSimple\0"
    "actionDrawPointCurveSimple\0"
    "actionDrawFreeCurve\0cursor\0"
    "actionDrawPointCurve\0actionDrawTriggers\0"
    "actionAddTimeline\0actionAddFreeCursor\0"
    "actionCircleCurve\0actionAddMathCurve\0"
    "actionAddMathCurveSimple\0editingStart\0"
    "NxPoint\0editingStop\0editingStopWithoutRemoval\0"
    "isLoop\0editingMove\0add\0mouseState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UiView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      60,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  314,    2, 0x06 /* Public */,
       3,    1,  319,    2, 0x06 /* Public */,
       5,    0,  322,    2, 0x06 /* Public */,
       6,    1,  323,    2, 0x06 /* Public */,
       7,    1,  326,    2, 0x06 /* Public */,
       8,    2,  329,    2, 0x06 /* Public */,
       9,    1,  334,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,  337,    2, 0x0a /* Public */,
      12,    0,  338,    2, 0x0a /* Public */,
      13,    0,  339,    2, 0x0a /* Public */,
      14,    0,  340,    2, 0x0a /* Public */,
      15,    0,  341,    2, 0x0a /* Public */,
      16,    0,  342,    2, 0x0a /* Public */,
      17,    0,  343,    2, 0x0a /* Public */,
      18,    0,  344,    2, 0x0a /* Public */,
      19,    1,  345,    2, 0x0a /* Public */,
      20,    0,  348,    2, 0x0a /* Public */,
      20,    1,  349,    2, 0x0a /* Public */,
      22,    0,  352,    2, 0x0a /* Public */,
      23,    0,  353,    2, 0x0a /* Public */,
      24,    0,  354,    2, 0x0a /* Public */,
      25,    0,  355,    2, 0x0a /* Public */,
      26,    0,  356,    2, 0x0a /* Public */,
      27,    0,  357,    2, 0x0a /* Public */,
      28,    0,  358,    2, 0x0a /* Public */,
      29,    0,  359,    2, 0x0a /* Public */,
      30,    0,  360,    2, 0x0a /* Public */,
      31,    0,  361,    2, 0x0a /* Public */,
      32,    0,  362,    2, 0x0a /* Public */,
      33,    0,  363,    2, 0x0a /* Public */,
      34,    0,  364,    2, 0x0a /* Public */,
      35,    0,  365,    2, 0x0a /* Public */,
      36,    0,  366,    2, 0x0a /* Public */,
      37,    0,  367,    2, 0x0a /* Public */,
      38,    0,  368,    2, 0x0a /* Public */,
      39,    0,  369,    2, 0x0a /* Public */,
      40,    0,  370,    2, 0x0a /* Public */,
      41,    0,  371,    2, 0x0a /* Public */,
      41,    1,  372,    2, 0x0a /* Public */,
      43,    0,  375,    2, 0x0a /* Public */,
      44,    0,  376,    2, 0x0a /* Public */,
      45,    1,  377,    2, 0x0a /* Public */,
      45,    0,  380,    2, 0x2a /* Public | MethodCloned */,
      47,    0,  381,    2, 0x0a /* Public */,
      48,    0,  382,    2, 0x0a /* Public */,
      49,    1,  383,    2, 0x0a /* Public */,
      49,    0,  386,    2, 0x2a /* Public | MethodCloned */,
      51,    1,  387,    2, 0x0a /* Public */,
      51,    0,  390,    2, 0x2a /* Public | MethodCloned */,
      52,    0,  391,    2, 0x0a /* Public */,
      53,    0,  392,    2, 0x0a /* Public */,
      54,    0,  393,    2, 0x0a /* Public */,
      55,    0,  394,    2, 0x0a /* Public */,
      56,    0,  395,    2, 0x0a /* Public */,
      57,    0,  396,    2, 0x0a /* Public */,
      58,    1,  397,    2, 0x0a /* Public */,
      60,    0,  400,    2, 0x0a /* Public */,
      61,    1,  401,    2, 0x0a /* Public */,
      61,    0,  404,    2, 0x2a /* Public | MethodCloned */,
      63,    3,  405,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::UShort,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 10,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QSize,   42,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort,   46,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   50,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   50,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 59,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   62,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 59, QMetaType::Bool, QMetaType::Bool,    2,   64,   65,

       0        // eod
};

void UiView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UiView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->forceGoto((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->arrangeObjects((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 2: _t->actionRouteReloadScript(); break;
        case 3: _t->actionRouteImportSVG((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->actionRouteImportBackground((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->actionRouteImportText((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->actionRouteCloseEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 7: _t->fullscreenDisplaysCountChanged(); break;
        case 8: _t->fullscreenDisplaysSelected(); break;
        case 9: _t->showTimer(); break;
        case 10: _t->showHelp(); break;
        case 11: _t->showTransport(); break;
        case 12: _t->showInspector(); break;
        case 13: _t->showEditor(); break;
        case 14: _t->actionToggleBorderlessMode(); break;
        case 15: _t->toggleFullscreen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->goToFullscreen(); break;
        case 17: _t->goToFullscreen((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 18: _t->escFullscreen(); break;
        case 19: _t->actionPlay_pause(); break;
        case 20: _t->actionFast_rewind(); break;
        case 21: _t->actionPerformance(); break;
        case 22: _t->actionReloadScript(); break;
        case 23: _t->actionImportSVG(); break;
        case 24: _t->actionImportBackground(); break;
        case 25: _t->actionImportText(); break;
        case 26: _t->actionAlign_top(); break;
        case 27: _t->actionAlign_left(); break;
        case 28: _t->actionAlign_bottom(); break;
        case 29: _t->actionAlign_right(); break;
        case 30: _t->actionAlign_middle(); break;
        case 31: _t->actionAlign_center(); break;
        case 32: _t->actionDistributeH(); break;
        case 33: _t->actionDistributeV(); break;
        case 34: _t->actionAlign_circle(); break;
        case 35: _t->actionAlign_ellipse(); break;
        case 36: _t->actionSnapshot(); break;
        case 37: _t->actionResize(); break;
        case 38: _t->actionResize((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 39: _t->gridChange(); break;
        case 40: _t->actionPatchesFolder(); break;
        case 41: _t->unToogleDraw((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 42: _t->unToogleDraw(); break;
        case 43: _t->actionDrawFreeCurveSimple(); break;
        case 44: _t->actionDrawPointCurveSimple(); break;
        case 45: _t->actionDrawFreeCurve((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 46: _t->actionDrawFreeCurve(); break;
        case 47: _t->actionDrawPointCurve((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 48: _t->actionDrawPointCurve(); break;
        case 49: _t->actionDrawTriggers(); break;
        case 50: _t->actionAddTimeline(); break;
        case 51: _t->actionAddFreeCursor(); break;
        case 52: _t->actionCircleCurve(); break;
        case 53: _t->actionAddMathCurve(); break;
        case 54: _t->actionAddMathCurveSimple(); break;
        case 55: _t->editingStart((*reinterpret_cast< const NxPoint(*)>(_a[1]))); break;
        case 56: _t->editingStop(); break;
        case 57: _t->editingStopWithoutRemoval((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 58: _t->editingStopWithoutRemoval(); break;
        case 59: _t->editingMove((*reinterpret_cast< const NxPoint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UiView::*)(qreal , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiView::forceGoto)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UiView::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiView::arrangeObjects)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UiView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiView::actionRouteReloadScript)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UiView::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiView::actionRouteImportSVG)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (UiView::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiView::actionRouteImportBackground)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (UiView::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiView::actionRouteImportText)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (UiView::*)(QCloseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiView::actionRouteCloseEvent)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UiView::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_UiView.data,
    qt_meta_data_UiView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UiView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UiView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UiView.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int UiView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 60)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 60;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 60)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 60;
    }
    return _id;
}

// SIGNAL 0
void UiView::forceGoto(qreal _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UiView::arrangeObjects(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UiView::actionRouteReloadScript()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void UiView::actionRouteImportSVG(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UiView::actionRouteImportBackground(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void UiView::actionRouteImportText(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void UiView::actionRouteCloseEvent(QCloseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
