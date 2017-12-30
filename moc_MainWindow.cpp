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
    QByteArrayData data[20];
    char stringdata0[286];
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
QT_MOC_LITERAL(3, 22, 5), // "speed"
QT_MOC_LITERAL(4, 28, 12), // "speedChanged"
QT_MOC_LITERAL(5, 41, 8), // "newSpeed"
QT_MOC_LITERAL(6, 50, 12), // "refreshEandH"
QT_MOC_LITERAL(7, 63, 12), // "refreshXandY"
QT_MOC_LITERAL(8, 76, 14), // "restartTheGame"
QT_MOC_LITERAL(9, 91, 12), // "showWChanged"
QT_MOC_LITERAL(10, 104, 18), // "handleSwitchButton"
QT_MOC_LITERAL(11, 123, 17), // "handleStartButton"
QT_MOC_LITERAL(12, 141, 15), // "handleMapButton"
QT_MOC_LITERAL(13, 157, 12), // "autoNavigate"
QT_MOC_LITERAL(14, 170, 17), // "handlePauseButton"
QT_MOC_LITERAL(15, 188, 16), // "handleSaveButton"
QT_MOC_LITERAL(16, 205, 16), // "handleLoadButton"
QT_MOC_LITERAL(17, 222, 11), // "handleSpeed"
QT_MOC_LITERAL(18, 234, 25), // "handleAddHealthpackButton"
QT_MOC_LITERAL(19, 260, 25) // "handleClearAllFilesButton"

    },
    "MainWindow\0pathFound\0\0speed\0speedChanged\0"
    "newSpeed\0refreshEandH\0refreshXandY\0"
    "restartTheGame\0showWChanged\0"
    "handleSwitchButton\0handleStartButton\0"
    "handleMapButton\0autoNavigate\0"
    "handlePauseButton\0handleSaveButton\0"
    "handleLoadButton\0handleSpeed\0"
    "handleAddHealthpackButton\0"
    "handleClearAllFilesButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  100,    2, 0x0a /* Public */,
       7,    0,  101,    2, 0x0a /* Public */,
       8,    0,  102,    2, 0x0a /* Public */,
       9,    0,  103,    2, 0x0a /* Public */,
      10,    0,  104,    2, 0x08 /* Private */,
      11,    0,  105,    2, 0x08 /* Private */,
      12,    0,  106,    2, 0x08 /* Private */,
      13,    0,  107,    2, 0x08 /* Private */,
      14,    0,  108,    2, 0x08 /* Private */,
      15,    0,  109,    2, 0x08 /* Private */,
      16,    0,  110,    2, 0x08 /* Private */,
      17,    0,  111,    2, 0x08 /* Private */,
      18,    0,  112,    2, 0x08 /* Private */,
      19,    0,  113,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,

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

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pathFound((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->speedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->refreshEandH(); break;
        case 3: _t->refreshXandY(); break;
        case 4: _t->restartTheGame(); break;
        case 5: _t->showWChanged(); break;
        case 6: _t->handleSwitchButton(); break;
        case 7: _t->handleStartButton(); break;
        case 8: _t->handleMapButton(); break;
        case 9: _t->autoNavigate(); break;
        case 10: _t->handlePauseButton(); break;
        case 11: _t->handleSaveButton(); break;
        case 12: _t->handleLoadButton(); break;
        case 13: _t->handleSpeed(); break;
        case 14: _t->handleAddHealthpackButton(); break;
        case 15: _t->handleClearAllFilesButton(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::pathFound)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(int );
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::pathFound(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::speedChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
