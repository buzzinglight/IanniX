/****************************************************************************
** Meta object code from reading C++ file 'iannix.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "iannix.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iannix.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IanniX_t {
    QByteArrayData data[71];
    char stringdata0[927];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IanniX_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IanniX_t qt_meta_stringdata_IanniX = {
    {
QT_MOC_LITERAL(0, 0, 6), // "IanniX"
QT_MOC_LITERAL(1, 7, 21), // "waitForMessageArrived"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "execute"
QT_MOC_LITERAL(4, 38, 16), // "MessageIncomming"
QT_MOC_LITERAL(5, 55, 7), // "command"
QT_MOC_LITERAL(6, 63, 23), // "createNewObjectIfExists"
QT_MOC_LITERAL(7, 87, 10), // "needOutput"
QT_MOC_LITERAL(8, 98, 13), // "ExecuteSource"
QT_MOC_LITERAL(9, 112, 6), // "source"
QT_MOC_LITERAL(10, 119, 15), // "executeAsScript"
QT_MOC_LITERAL(11, 135, 6), // "script"
QT_MOC_LITERAL(12, 142, 14), // "argvFullString"
QT_MOC_LITERAL(13, 157, 4), // "argv"
QT_MOC_LITERAL(14, 162, 5), // "index"
QT_MOC_LITERAL(15, 168, 10), // "argvDouble"
QT_MOC_LITERAL(16, 179, 15), // "incomingMessage"
QT_MOC_LITERAL(17, 195, 12), // "needToScript"
QT_MOC_LITERAL(18, 208, 17), // "openMessageEditor"
QT_MOC_LITERAL(19, 226, 4), // "send"
QT_MOC_LITERAL(20, 231, 7), // "Message"
QT_MOC_LITERAL(21, 239, 7), // "message"
QT_MOC_LITERAL(22, 247, 12), // "QStringList*"
QT_MOC_LITERAL(23, 260, 11), // "sentMessage"
QT_MOC_LITERAL(24, 272, 13), // "getMainWindow"
QT_MOC_LITERAL(25, 286, 12), // "QMainWindow*"
QT_MOC_LITERAL(26, 299, 16), // "getRenderPreview"
QT_MOC_LITERAL(27, 316, 16), // "UiRenderPreview*"
QT_MOC_LITERAL(28, 333, 21), // "getPerformancePreview"
QT_MOC_LITERAL(29, 355, 9), // "timerTick"
QT_MOC_LITERAL(30, 365, 5), // "force"
QT_MOC_LITERAL(31, 371, 5), // "delta"
QT_MOC_LITERAL(32, 377, 9), // "timerTrig"
QT_MOC_LITERAL(33, 387, 6), // "object"
QT_MOC_LITERAL(34, 394, 23), // "checkForUpdatesFinished"
QT_MOC_LITERAL(35, 418, 14), // "QNetworkReply*"
QT_MOC_LITERAL(36, 433, 9), // "forceGoto"
QT_MOC_LITERAL(37, 443, 8), // "midiSync"
QT_MOC_LITERAL(38, 452, 19), // "forceSchedulerTimer"
QT_MOC_LITERAL(39, 472, 16), // "forceOpenGLTimer"
QT_MOC_LITERAL(40, 489, 15), // "actionPlayPause"
QT_MOC_LITERAL(41, 505, 8), // "actionCC"
QT_MOC_LITERAL(42, 514, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(43, 531, 9), // "actionNew"
QT_MOC_LITERAL(44, 541, 10), // "actionOpen"
QT_MOC_LITERAL(45, 552, 10), // "actionSave"
QT_MOC_LITERAL(46, 563, 19), // "actionSaveAndReload"
QT_MOC_LITERAL(47, 583, 13), // "actionSave_as"
QT_MOC_LITERAL(48, 597, 13), // "actionRefresh"
QT_MOC_LITERAL(49, 611, 22), // "currentDocumentChanged"
QT_MOC_LITERAL(50, 634, 11), // "UiSyncItem*"
QT_MOC_LITERAL(51, 646, 10), // "actionUndo"
QT_MOC_LITERAL(52, 657, 10), // "actionRedo"
QT_MOC_LITERAL(53, 668, 15), // "actionImportSVG"
QT_MOC_LITERAL(54, 684, 8), // "filename"
QT_MOC_LITERAL(55, 693, 22), // "actionImportBackground"
QT_MOC_LITERAL(56, 716, 16), // "actionImportText"
QT_MOC_LITERAL(57, 733, 4), // "font"
QT_MOC_LITERAL(58, 738, 4), // "text"
QT_MOC_LITERAL(59, 743, 18), // "actionReloadScript"
QT_MOC_LITERAL(60, 762, 16), // "actionCloseEvent"
QT_MOC_LITERAL(61, 779, 12), // "QCloseEvent*"
QT_MOC_LITERAL(62, 792, 5), // "event"
QT_MOC_LITERAL(63, 798, 18), // "actionUnmuteGroups"
QT_MOC_LITERAL(64, 817, 19), // "actionUnmuteObjects"
QT_MOC_LITERAL(65, 837, 18), // "actionUnsoloGroups"
QT_MOC_LITERAL(66, 856, 19), // "actionUnsoloObjects"
QT_MOC_LITERAL(67, 876, 14), // "waitForMessage"
QT_MOC_LITERAL(68, 891, 12), // "pushSnapshot"
QT_MOC_LITERAL(69, 904, 11), // "actionPaste"
QT_MOC_LITERAL(70, 916, 10) // "actionCopy"

    },
    "IanniX\0waitForMessageArrived\0\0execute\0"
    "MessageIncomming\0command\0"
    "createNewObjectIfExists\0needOutput\0"
    "ExecuteSource\0source\0executeAsScript\0"
    "script\0argvFullString\0argv\0index\0"
    "argvDouble\0incomingMessage\0needToScript\0"
    "openMessageEditor\0send\0Message\0message\0"
    "QStringList*\0sentMessage\0getMainWindow\0"
    "QMainWindow*\0getRenderPreview\0"
    "UiRenderPreview*\0getPerformancePreview\0"
    "timerTick\0force\0delta\0timerTrig\0object\0"
    "checkForUpdatesFinished\0QNetworkReply*\0"
    "forceGoto\0midiSync\0forceSchedulerTimer\0"
    "forceOpenGLTimer\0actionPlayPause\0"
    "actionCC\0QTreeWidgetItem*\0actionNew\0"
    "actionOpen\0actionSave\0actionSaveAndReload\0"
    "actionSave_as\0actionRefresh\0"
    "currentDocumentChanged\0UiSyncItem*\0"
    "actionUndo\0actionRedo\0actionImportSVG\0"
    "filename\0actionImportBackground\0"
    "actionImportText\0font\0text\0"
    "actionReloadScript\0actionCloseEvent\0"
    "QCloseEvent*\0event\0actionUnmuteGroups\0"
    "actionUnmuteObjects\0actionUnsoloGroups\0"
    "actionUnsoloObjects\0waitForMessage\0"
    "pushSnapshot\0actionPaste\0actionCopy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IanniX[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      53,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  279,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    3,  280,    2, 0x0a /* Public */,
       3,    2,  287,    2, 0x2a /* Public | MethodCloned */,
       3,    1,  292,    2, 0x2a /* Public | MethodCloned */,
       3,    4,  295,    2, 0x0a /* Public */,
       3,    3,  304,    2, 0x2a /* Public | MethodCloned */,
       3,    2,  311,    2, 0x2a /* Public | MethodCloned */,
      10,    1,  316,    2, 0x0a /* Public */,
      12,    3,  319,    2, 0x0a /* Public */,
      15,    2,  326,    2, 0x0a /* Public */,
      16,    3,  331,    2, 0x0a /* Public */,
      16,    2,  338,    2, 0x2a /* Public | MethodCloned */,
      16,    1,  343,    2, 0x2a /* Public | MethodCloned */,
      18,    0,  346,    2, 0x0a /* Public */,
      19,    2,  347,    2, 0x0a /* Public */,
      19,    1,  352,    2, 0x2a /* Public | MethodCloned */,
      24,    0,  355,    2, 0x0a /* Public */,
      26,    0,  356,    2, 0x0a /* Public */,
      28,    0,  357,    2, 0x0a /* Public */,
      29,    0,  358,    2, 0x08 /* Private */,
      29,    1,  359,    2, 0x08 /* Private */,
      29,    1,  362,    2, 0x08 /* Private */,
      32,    2,  365,    2, 0x08 /* Private */,
      32,    1,  370,    2, 0x28 /* Private | MethodCloned */,
      34,    1,  373,    2, 0x08 /* Private */,
      36,    2,  376,    2, 0x0a /* Public */,
      36,    1,  381,    2, 0x2a /* Public | MethodCloned */,
      38,    1,  384,    2, 0x0a /* Public */,
      39,    1,  387,    2, 0x0a /* Public */,
      40,    0,  390,    2, 0x0a /* Public */,
      41,    2,  391,    2, 0x0a /* Public */,
      43,    0,  396,    2, 0x0a /* Public */,
      44,    0,  397,    2, 0x0a /* Public */,
      45,    0,  398,    2, 0x0a /* Public */,
      46,    0,  399,    2, 0x0a /* Public */,
      47,    0,  400,    2, 0x0a /* Public */,
      48,    0,  401,    2, 0x0a /* Public */,
      49,    1,  402,    2, 0x0a /* Public */,
      51,    0,  405,    2, 0x0a /* Public */,
      52,    0,  406,    2, 0x0a /* Public */,
      53,    1,  407,    2, 0x0a /* Public */,
      55,    1,  410,    2, 0x0a /* Public */,
      56,    2,  413,    2, 0x0a /* Public */,
      59,    0,  418,    2, 0x0a /* Public */,
      60,    1,  419,    2, 0x0a /* Public */,
      63,    0,  422,    2, 0x0a /* Public */,
      64,    0,  423,    2, 0x0a /* Public */,
      65,    0,  424,    2, 0x0a /* Public */,
      66,    0,  425,    2, 0x0a /* Public */,
      67,    0,  426,    2, 0x0a /* Public */,
      68,    0,  427,    2, 0x0a /* Public */,
      69,    0,  428,    2, 0x0a /* Public */,
      70,    0,  429,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::QVariant, 0x80000000 | 4, QMetaType::Bool, QMetaType::Bool,    5,    6,    7,
    QMetaType::QVariant, 0x80000000 | 4, QMetaType::Bool,    5,    6,
    QMetaType::QVariant, 0x80000000 | 4,    5,
    QMetaType::QVariant, QMetaType::QString, 0x80000000 | 8, QMetaType::Bool, QMetaType::Bool,    5,    9,    6,    7,
    QMetaType::QVariant, QMetaType::QString, 0x80000000 | 8, QMetaType::Bool,    5,    9,    6,
    QMetaType::QVariant, QMetaType::QString, 0x80000000 | 8,    5,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::QString, QMetaType::QString, QMetaType::QStringList, QMetaType::UShort,    5,   13,   14,
    QMetaType::QReal, QMetaType::QStringList, QMetaType::UShort,   13,   14,
    QMetaType::QString, 0x80000000 | 4, QMetaType::Bool, QMetaType::Bool,    9,    7,   17,
    QMetaType::QString, 0x80000000 | 4, QMetaType::Bool,    9,    7,
    QMetaType::QString, 0x80000000 | 4,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 22,   21,   23,
    QMetaType::Void, 0x80000000 | 20,   21,
    0x80000000 | 25,
    0x80000000 | 27,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::QReal,   31,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::Bool,   33,   30,
    QMetaType::Void, QMetaType::VoidStar,   33,
    QMetaType::Void, 0x80000000 | 35,    2,
    QMetaType::Void, QMetaType::QReal, QMetaType::Bool,    2,   37,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 42, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 50,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   54,
    QMetaType::Void, QMetaType::QString,   54,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   57,   58,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 61,   62,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IanniX::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IanniX *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->waitForMessageArrived(); break;
        case 1: { QVariant _r = _t->execute((*reinterpret_cast< const MessageIncomming(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 2: { QVariant _r = _t->execute((*reinterpret_cast< const MessageIncomming(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 3: { QVariant _r = _t->execute((*reinterpret_cast< const MessageIncomming(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariant _r = _t->execute((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< ExecuteSource(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 5: { QVariant _r = _t->execute((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< ExecuteSource(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 6: { QVariant _r = _t->execute((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< ExecuteSource(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->executeAsScript((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: { QString _r = _t->argvFullString((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 9: { qreal _r = _t->argvDouble((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = std::move(_r); }  break;
        case 10: { QString _r = _t->incomingMessage((*reinterpret_cast< const MessageIncomming(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->incomingMessage((*reinterpret_cast< const MessageIncomming(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: { QString _r = _t->incomingMessage((*reinterpret_cast< const MessageIncomming(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->openMessageEditor(); break;
        case 14: _t->send((*reinterpret_cast< const Message(*)>(_a[1])),(*reinterpret_cast< QStringList*(*)>(_a[2]))); break;
        case 15: _t->send((*reinterpret_cast< const Message(*)>(_a[1]))); break;
        case 16: { QMainWindow* _r = _t->getMainWindow();
            if (_a[0]) *reinterpret_cast< QMainWindow**>(_a[0]) = std::move(_r); }  break;
        case 17: { UiRenderPreview* _r = _t->getRenderPreview();
            if (_a[0]) *reinterpret_cast< UiRenderPreview**>(_a[0]) = std::move(_r); }  break;
        case 18: { bool _r = _t->getPerformancePreview();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: _t->timerTick(); break;
        case 20: _t->timerTick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->timerTick((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 22: _t->timerTrig((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 23: _t->timerTrig((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 24: _t->checkForUpdatesFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 25: _t->forceGoto((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 26: _t->forceGoto((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 27: _t->forceSchedulerTimer((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 28: _t->forceOpenGLTimer((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 29: _t->actionPlayPause(); break;
        case 30: _t->actionCC((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 31: _t->actionNew(); break;
        case 32: _t->actionOpen(); break;
        case 33: _t->actionSave(); break;
        case 34: _t->actionSaveAndReload(); break;
        case 35: _t->actionSave_as(); break;
        case 36: _t->actionRefresh(); break;
        case 37: _t->currentDocumentChanged((*reinterpret_cast< UiSyncItem*(*)>(_a[1]))); break;
        case 38: _t->actionUndo(); break;
        case 39: _t->actionRedo(); break;
        case 40: _t->actionImportSVG((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 41: _t->actionImportBackground((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 42: _t->actionImportText((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 43: _t->actionReloadScript(); break;
        case 44: _t->actionCloseEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 45: _t->actionUnmuteGroups(); break;
        case 46: _t->actionUnmuteObjects(); break;
        case 47: _t->actionUnsoloGroups(); break;
        case 48: _t->actionUnsoloObjects(); break;
        case 49: { QString _r = _t->waitForMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 50: _t->pushSnapshot(); break;
        case 51: _t->actionPaste(); break;
        case 52: _t->actionCopy(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IanniX::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IanniX::waitForMessageArrived)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IanniX::staticMetaObject = { {
    QMetaObject::SuperData::link<ApplicationCurrent::staticMetaObject>(),
    qt_meta_stringdata_IanniX.data,
    qt_meta_data_IanniX,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IanniX::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IanniX::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IanniX.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NxObjectDispatchProperty"))
        return static_cast< NxObjectDispatchProperty*>(this);
    if (!strcmp(_clname, "MessageDispatcher"))
        return static_cast< MessageDispatcher*>(this);
    return ApplicationCurrent::qt_metacast(_clname);
}

int IanniX::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ApplicationCurrent::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    }
    return _id;
}

// SIGNAL 0
void IanniX::waitForMessageArrived()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
