/****************************************************************************
** Meta object code from reading C++ file 'uirender.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "render/uirender.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uirender.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UiRender_t {
    QByteArrayData data[67];
    char stringdata0[918];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UiRender_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UiRender_t qt_meta_stringdata_UiRender = {
    {
QT_MOC_LITERAL(0, 0, 8), // "UiRender"
QT_MOC_LITERAL(1, 9, 13), // "escFullscreen"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "editingStart"
QT_MOC_LITERAL(4, 37, 7), // "NxPoint"
QT_MOC_LITERAL(5, 45, 11), // "editingStop"
QT_MOC_LITERAL(6, 57, 11), // "editingMove"
QT_MOC_LITERAL(7, 69, 3), // "add"
QT_MOC_LITERAL(8, 73, 10), // "mouseState"
QT_MOC_LITERAL(9, 84, 14), // "objectSelected"
QT_MOC_LITERAL(10, 99, 17), // "UiRenderSelection"
QT_MOC_LITERAL(11, 117, 15), // "mousePosChanged"
QT_MOC_LITERAL(12, 133, 16), // "mouseZoomChanged"
QT_MOC_LITERAL(13, 150, 20), // "mouseRotationChanged"
QT_MOC_LITERAL(14, 171, 14), // "actionRouteNew"
QT_MOC_LITERAL(15, 186, 21), // "actionRouteNew_script"
QT_MOC_LITERAL(16, 208, 15), // "actionRouteOpen"
QT_MOC_LITERAL(17, 224, 15), // "actionRouteSave"
QT_MOC_LITERAL(18, 240, 18), // "actionRouteSave_as"
QT_MOC_LITERAL(19, 259, 19), // "actionRouteSave_all"
QT_MOC_LITERAL(20, 279, 25), // "actionRouteDuplicateScore"
QT_MOC_LITERAL(21, 305, 17), // "actionRouteRename"
QT_MOC_LITERAL(22, 323, 17), // "actionRouteRemove"
QT_MOC_LITERAL(23, 341, 20), // "actionRouteImportSVG"
QT_MOC_LITERAL(24, 362, 27), // "actionRouteImportBackground"
QT_MOC_LITERAL(25, 390, 21), // "actionRouteImportText"
QT_MOC_LITERAL(26, 412, 15), // "actionRouteCopy"
QT_MOC_LITERAL(27, 428, 16), // "actionRoutePaste"
QT_MOC_LITERAL(28, 445, 15), // "actionRouteUndo"
QT_MOC_LITERAL(29, 461, 15), // "actionRouteRedo"
QT_MOC_LITERAL(30, 477, 16), // "selectionChanged"
QT_MOC_LITERAL(31, 494, 7), // "setZoom"
QT_MOC_LITERAL(32, 502, 6), // "zoomIn"
QT_MOC_LITERAL(33, 509, 7), // "zoomOut"
QT_MOC_LITERAL(34, 517, 11), // "zoomInitial"
QT_MOC_LITERAL(35, 529, 24), // "cameraPerspectiveChanged"
QT_MOC_LITERAL(36, 554, 9), // "actionNew"
QT_MOC_LITERAL(37, 564, 10), // "actionOpen"
QT_MOC_LITERAL(38, 575, 10), // "actionSave"
QT_MOC_LITERAL(39, 586, 13), // "actionSave_as"
QT_MOC_LITERAL(40, 600, 14), // "actionSave_all"
QT_MOC_LITERAL(41, 615, 20), // "actionDuplicateScore"
QT_MOC_LITERAL(42, 636, 12), // "actionRename"
QT_MOC_LITERAL(43, 649, 12), // "actionRemove"
QT_MOC_LITERAL(44, 662, 10), // "actionUndo"
QT_MOC_LITERAL(45, 673, 10), // "actionRedo"
QT_MOC_LITERAL(46, 684, 15), // "actionImportSVG"
QT_MOC_LITERAL(47, 700, 3), // "val"
QT_MOC_LITERAL(48, 704, 22), // "actionImportBackground"
QT_MOC_LITERAL(49, 727, 16), // "actionImportText"
QT_MOC_LITERAL(50, 744, 4), // "val2"
QT_MOC_LITERAL(51, 749, 11), // "actionPaste"
QT_MOC_LITERAL(52, 761, 10), // "actionCopy"
QT_MOC_LITERAL(53, 772, 15), // "actionDuplicate"
QT_MOC_LITERAL(54, 788, 9), // "actionCut"
QT_MOC_LITERAL(55, 798, 16), // "actionSelect_all"
QT_MOC_LITERAL(56, 815, 12), // "actionDelete"
QT_MOC_LITERAL(57, 828, 14), // "arrangeObjects"
QT_MOC_LITERAL(58, 843, 4), // "type"
QT_MOC_LITERAL(59, 848, 9), // "NxObject*"
QT_MOC_LITERAL(60, 858, 5), // "objet"
QT_MOC_LITERAL(61, 864, 2), // "pt"
QT_MOC_LITERAL(62, 867, 7), // "capture"
QT_MOC_LITERAL(63, 875, 11), // "scaleFactor"
QT_MOC_LITERAL(64, 887, 12), // "captureFrame"
QT_MOC_LITERAL(65, 900, 8), // "filename"
QT_MOC_LITERAL(66, 909, 8) // "updateGL"

    },
    "UiRender\0escFullscreen\0\0editingStart\0"
    "NxPoint\0editingStop\0editingMove\0add\0"
    "mouseState\0objectSelected\0UiRenderSelection\0"
    "mousePosChanged\0mouseZoomChanged\0"
    "mouseRotationChanged\0actionRouteNew\0"
    "actionRouteNew_script\0actionRouteOpen\0"
    "actionRouteSave\0actionRouteSave_as\0"
    "actionRouteSave_all\0actionRouteDuplicateScore\0"
    "actionRouteRename\0actionRouteRemove\0"
    "actionRouteImportSVG\0actionRouteImportBackground\0"
    "actionRouteImportText\0actionRouteCopy\0"
    "actionRoutePaste\0actionRouteUndo\0"
    "actionRouteRedo\0selectionChanged\0"
    "setZoom\0zoomIn\0zoomOut\0zoomInitial\0"
    "cameraPerspectiveChanged\0actionNew\0"
    "actionOpen\0actionSave\0actionSave_as\0"
    "actionSave_all\0actionDuplicateScore\0"
    "actionRename\0actionRemove\0actionUndo\0"
    "actionRedo\0actionImportSVG\0val\0"
    "actionImportBackground\0actionImportText\0"
    "val2\0actionPaste\0actionCopy\0actionDuplicate\0"
    "actionCut\0actionSelect_all\0actionDelete\0"
    "arrangeObjects\0type\0NxObject*\0objet\0"
    "pt\0capture\0scaleFactor\0captureFrame\0"
    "filename\0updateGL"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UiRender[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      55,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      25,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  289,    2, 0x06 /* Public */,
       3,    1,  290,    2, 0x06 /* Public */,
       5,    0,  293,    2, 0x06 /* Public */,
       6,    3,  294,    2, 0x06 /* Public */,
       9,    1,  301,    2, 0x06 /* Public */,
      11,    1,  304,    2, 0x06 /* Public */,
      12,    1,  307,    2, 0x06 /* Public */,
      13,    1,  310,    2, 0x06 /* Public */,
      14,    0,  313,    2, 0x06 /* Public */,
      15,    0,  314,    2, 0x06 /* Public */,
      16,    0,  315,    2, 0x06 /* Public */,
      17,    0,  316,    2, 0x06 /* Public */,
      18,    0,  317,    2, 0x06 /* Public */,
      19,    0,  318,    2, 0x06 /* Public */,
      20,    0,  319,    2, 0x06 /* Public */,
      21,    0,  320,    2, 0x06 /* Public */,
      22,    0,  321,    2, 0x06 /* Public */,
      23,    1,  322,    2, 0x06 /* Public */,
      24,    1,  325,    2, 0x06 /* Public */,
      25,    2,  328,    2, 0x06 /* Public */,
      26,    0,  333,    2, 0x06 /* Public */,
      27,    0,  334,    2, 0x06 /* Public */,
      28,    0,  335,    2, 0x06 /* Public */,
      29,    0,  336,    2, 0x06 /* Public */,
      30,    0,  337,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      31,    0,  338,    2, 0x0a /* Public */,
      32,    0,  339,    2, 0x0a /* Public */,
      33,    0,  340,    2, 0x0a /* Public */,
      34,    0,  341,    2, 0x0a /* Public */,
      35,    0,  342,    2, 0x0a /* Public */,
      36,    0,  343,    2, 0x0a /* Public */,
      37,    0,  344,    2, 0x0a /* Public */,
      38,    0,  345,    2, 0x0a /* Public */,
      39,    0,  346,    2, 0x0a /* Public */,
      40,    0,  347,    2, 0x0a /* Public */,
      41,    0,  348,    2, 0x0a /* Public */,
      42,    0,  349,    2, 0x0a /* Public */,
      43,    0,  350,    2, 0x0a /* Public */,
      44,    0,  351,    2, 0x0a /* Public */,
      45,    0,  352,    2, 0x0a /* Public */,
      46,    1,  353,    2, 0x0a /* Public */,
      48,    1,  356,    2, 0x0a /* Public */,
      49,    2,  359,    2, 0x0a /* Public */,
      51,    0,  364,    2, 0x0a /* Public */,
      52,    0,  365,    2, 0x0a /* Public */,
      53,    0,  366,    2, 0x0a /* Public */,
      54,    0,  367,    2, 0x0a /* Public */,
      55,    0,  368,    2, 0x0a /* Public */,
      56,    0,  369,    2, 0x0a /* Public */,
      57,    1,  370,    2, 0x0a /* Public */,
      57,    2,  373,    2, 0x0a /* Public */,
      62,    1,  378,    2, 0x0a /* Public */,
      64,    2,  381,    2, 0x0a /* Public */,
      64,    1,  386,    2, 0x2a /* Public | MethodCloned */,
      66,    0,  389,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Bool, QMetaType::Bool,    2,    7,    8,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
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
    QMetaType::Void, QMetaType::QString,   47,
    QMetaType::Void, QMetaType::QString,   47,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   47,   50,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort,   58,
    QMetaType::Void, 0x80000000 | 59, 0x80000000 | 4,   60,   61,
    QMetaType::Void, QMetaType::QReal,   63,
    QMetaType::Bool, QMetaType::QReal, QMetaType::QString,   63,   65,
    QMetaType::Bool, QMetaType::QReal,   63,
    QMetaType::Void,

       0        // eod
};

void UiRender::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UiRender *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->escFullscreen(); break;
        case 1: _t->editingStart((*reinterpret_cast< const NxPoint(*)>(_a[1]))); break;
        case 2: _t->editingStop(); break;
        case 3: _t->editingMove((*reinterpret_cast< const NxPoint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 4: _t->objectSelected((*reinterpret_cast< UiRenderSelection(*)>(_a[1]))); break;
        case 5: _t->mousePosChanged((*reinterpret_cast< const NxPoint(*)>(_a[1]))); break;
        case 6: _t->mouseZoomChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 7: _t->mouseRotationChanged((*reinterpret_cast< const NxPoint(*)>(_a[1]))); break;
        case 8: _t->actionRouteNew(); break;
        case 9: _t->actionRouteNew_script(); break;
        case 10: _t->actionRouteOpen(); break;
        case 11: _t->actionRouteSave(); break;
        case 12: _t->actionRouteSave_as(); break;
        case 13: _t->actionRouteSave_all(); break;
        case 14: _t->actionRouteDuplicateScore(); break;
        case 15: _t->actionRouteRename(); break;
        case 16: _t->actionRouteRemove(); break;
        case 17: _t->actionRouteImportSVG((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->actionRouteImportBackground((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->actionRouteImportText((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 20: _t->actionRouteCopy(); break;
        case 21: _t->actionRoutePaste(); break;
        case 22: _t->actionRouteUndo(); break;
        case 23: _t->actionRouteRedo(); break;
        case 24: _t->selectionChanged(); break;
        case 25: _t->setZoom(); break;
        case 26: _t->zoomIn(); break;
        case 27: _t->zoomOut(); break;
        case 28: _t->zoomInitial(); break;
        case 29: _t->cameraPerspectiveChanged(); break;
        case 30: _t->actionNew(); break;
        case 31: _t->actionOpen(); break;
        case 32: _t->actionSave(); break;
        case 33: _t->actionSave_as(); break;
        case 34: _t->actionSave_all(); break;
        case 35: _t->actionDuplicateScore(); break;
        case 36: _t->actionRename(); break;
        case 37: _t->actionRemove(); break;
        case 38: _t->actionUndo(); break;
        case 39: _t->actionRedo(); break;
        case 40: _t->actionImportSVG((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 41: _t->actionImportBackground((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 42: _t->actionImportText((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 43: _t->actionPaste(); break;
        case 44: _t->actionCopy(); break;
        case 45: _t->actionDuplicate(); break;
        case 46: _t->actionCut(); break;
        case 47: _t->actionSelect_all(); break;
        case 48: _t->actionDelete(); break;
        case 49: _t->arrangeObjects((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 50: _t->arrangeObjects((*reinterpret_cast< NxObject*(*)>(_a[1])),(*reinterpret_cast< const NxPoint(*)>(_a[2]))); break;
        case 51: _t->capture((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 52: { bool _r = _t->captureFrame((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 53: { bool _r = _t->captureFrame((*reinterpret_cast< qreal(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 54: _t->updateGL(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 50:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NxObject* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::escFullscreen)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UiRender::*)(const NxPoint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::editingStart)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::editingStop)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UiRender::*)(const NxPoint & , bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::editingMove)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (UiRender::*)(UiRenderSelection );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::objectSelected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (UiRender::*)(const NxPoint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::mousePosChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (UiRender::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::mouseZoomChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (UiRender::*)(const NxPoint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::mouseRotationChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteNew)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteNew_script)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteOpen)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteSave)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteSave_as)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteSave_all)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteDuplicateScore)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteRename)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteRemove)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (UiRender::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteImportSVG)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (UiRender::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteImportBackground)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (UiRender::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteImportText)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteCopy)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRoutePaste)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteUndo)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::actionRouteRedo)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (UiRender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UiRender::selectionChanged)) {
                *result = 24;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UiRender::staticMetaObject = { {
    QMetaObject::SuperData::link<Render::staticMetaObject>(),
    qt_meta_stringdata_UiRender.data,
    qt_meta_data_UiRender,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UiRender::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UiRender::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UiRender.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NxEventsPropagation"))
        return static_cast< NxEventsPropagation*>(this);
    return Render::qt_metacast(_clname);
}

int UiRender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Render::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 55)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 55;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 55)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 55;
    }
    return _id;
}

// SIGNAL 0
void UiRender::escFullscreen()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void UiRender::editingStart(const NxPoint & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UiRender::editingStop()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void UiRender::editingMove(const NxPoint & _t1, bool _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UiRender::objectSelected(UiRenderSelection _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void UiRender::mousePosChanged(const NxPoint & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void UiRender::mouseZoomChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void UiRender::mouseRotationChanged(const NxPoint & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void UiRender::actionRouteNew()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void UiRender::actionRouteNew_script()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void UiRender::actionRouteOpen()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void UiRender::actionRouteSave()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void UiRender::actionRouteSave_as()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void UiRender::actionRouteSave_all()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void UiRender::actionRouteDuplicateScore()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void UiRender::actionRouteRename()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void UiRender::actionRouteRemove()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void UiRender::actionRouteImportSVG(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void UiRender::actionRouteImportBackground(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void UiRender::actionRouteImportText(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void UiRender::actionRouteCopy()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void UiRender::actionRoutePaste()
{
    QMetaObject::activate(this, &staticMetaObject, 21, nullptr);
}

// SIGNAL 22
void UiRender::actionRouteUndo()
{
    QMetaObject::activate(this, &staticMetaObject, 22, nullptr);
}

// SIGNAL 23
void UiRender::actionRouteRedo()
{
    QMetaObject::activate(this, &staticMetaObject, 23, nullptr);
}

// SIGNAL 24
void UiRender::selectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 24, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
