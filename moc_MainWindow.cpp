/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[328];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 9), // "pathFound"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "speedChanged"
QT_MOC_LITERAL(4, 35, 12), // "refreshEandH"
QT_MOC_LITERAL(5, 48, 12), // "refreshXandY"
QT_MOC_LITERAL(6, 61, 14), // "restartTheGame"
QT_MOC_LITERAL(7, 76, 18), // "handleSwitchButton"
QT_MOC_LITERAL(8, 95, 16), // "showSpeedChanged"
QT_MOC_LITERAL(9, 112, 11), // "handleSpeed"
QT_MOC_LITERAL(10, 124, 3), // "idx"
QT_MOC_LITERAL(11, 128, 17), // "handleStartButton"
QT_MOC_LITERAL(12, 146, 15), // "handleMapButton"
QT_MOC_LITERAL(13, 162, 7), // "handleW"
QT_MOC_LITERAL(14, 170, 12), // "showWChanged"
QT_MOC_LITERAL(15, 183, 12), // "autoNavigate"
QT_MOC_LITERAL(16, 196, 17), // "handlePauseButton"
QT_MOC_LITERAL(17, 214, 16), // "handleSaveButton"
QT_MOC_LITERAL(18, 231, 16), // "handleLoadButton"
QT_MOC_LITERAL(19, 248, 25), // "handleAddHealthpackButton"
QT_MOC_LITERAL(20, 274, 25), // "handleClearAllFilesButton"
QT_MOC_LITERAL(21, 300, 12), // "switchLayout"
QT_MOC_LITERAL(22, 313, 14) // "recoverButtons"

    },
    "MainWindow\0pathFound\0\0speedChanged\0"
    "refreshEandH\0refreshXandY\0restartTheGame\0"
    "handleSwitchButton\0showSpeedChanged\0"
    "handleSpeed\0idx\0handleStartButton\0"
    "handleMapButton\0handleW\0showWChanged\0"
    "autoNavigate\0handlePauseButton\0"
    "handleSaveButton\0handleLoadButton\0"
    "handleAddHealthpackButton\0"
    "handleClearAllFilesButton\0switchLayout\0"
    "recoverButtons"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x06 /* Public */,
       3,    0,  115,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  116,    2, 0x0a /* Public */,
       5,    0,  117,    2, 0x0a /* Public */,
       6,    0,  118,    2, 0x0a /* Public */,
       7,    0,  119,    2, 0x08 /* Private */,
       8,    0,  120,    2, 0x08 /* Private */,
       9,    1,  121,    2, 0x08 /* Private */,
      11,    0,  124,    2, 0x08 /* Private */,
      12,    0,  125,    2, 0x08 /* Private */,
      13,    0,  126,    2, 0x08 /* Private */,
      14,    0,  127,    2, 0x08 /* Private */,
      15,    0,  128,    2, 0x08 /* Private */,
      16,    0,  129,    2, 0x08 /* Private */,
      17,    0,  130,    2, 0x08 /* Private */,
      18,    0,  131,    2, 0x08 /* Private */,
      19,    0,  132,    2, 0x08 /* Private */,
      20,    0,  133,    2, 0x08 /* Private */,
      21,    0,  134,    2, 0x08 /* Private */,
      22,    0,  135,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
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

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pathFound(); break;
        case 1: _t->speedChanged(); break;
        case 2: _t->refreshEandH(); break;
        case 3: _t->refreshXandY(); break;
        case 4: _t->restartTheGame(); break;
        case 5: _t->handleSwitchButton(); break;
        case 6: _t->showSpeedChanged(); break;
        case 7: _t->handleSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->handleStartButton(); break;
        case 9: _t->handleMapButton(); break;
        case 10: _t->handleW(); break;
        case 11: _t->showWChanged(); break;
        case 12: _t->autoNavigate(); break;
        case 13: _t->handlePauseButton(); break;
        case 14: _t->handleSaveButton(); break;
        case 15: _t->handleLoadButton(); break;
        case 16: _t->handleAddHealthpackButton(); break;
        case 17: _t->handleClearAllFilesButton(); break;
        case 18: _t->switchLayout(); break;
        case 19: _t->recoverButtons(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::pathFound)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::speedChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::pathFound()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::speedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
