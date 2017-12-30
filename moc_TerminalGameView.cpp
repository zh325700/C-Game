/****************************************************************************
** Meta object code from reading C++ file 'TerminalGameView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TerminalGameView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TerminalGameView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TerminalGameView_t {
    QByteArrayData data[14];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TerminalGameView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TerminalGameView_t qt_meta_stringdata_TerminalGameView = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TerminalGameView"
QT_MOC_LITERAL(1, 17, 15), // "destinationFind"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 12), // "automaticRun"
QT_MOC_LITERAL(4, 47, 8), // "wChanged"
QT_MOC_LITERAL(5, 56, 20), // "terminalSpeedChanged"
QT_MOC_LITERAL(6, 77, 7), // "onEnter"
QT_MOC_LITERAL(7, 85, 10), // "encouterEn"
QT_MOC_LITERAL(8, 96, 12), // "encounterPEn"
QT_MOC_LITERAL(9, 109, 10), // "encouterHe"
QT_MOC_LITERAL(10, 120, 11), // "checkNewPos"
QT_MOC_LITERAL(11, 132, 9), // "enemyDead"
QT_MOC_LITERAL(12, 142, 10), // "penemyDead"
QT_MOC_LITERAL(13, 153, 10) // "poisonUser"

    },
    "TerminalGameView\0destinationFind\0\0"
    "automaticRun\0wChanged\0terminalSpeedChanged\0"
    "onEnter\0encouterEn\0encounterPEn\0"
    "encouterHe\0checkNewPos\0enemyDead\0"
    "penemyDead\0poisonUser"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TerminalGameView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,
       5,    0,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    0,   82,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    0,   84,    2, 0x0a /* Public */,
      13,    0,   85,    2, 0x0a /* Public */,

 // signals: parameters
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

       0        // eod
};

void TerminalGameView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TerminalGameView *_t = static_cast<TerminalGameView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->destinationFind(); break;
        case 1: _t->automaticRun(); break;
        case 2: _t->wChanged(); break;
        case 3: _t->terminalSpeedChanged(); break;
        case 4: _t->onEnter(); break;
        case 5: _t->encouterEn(); break;
        case 6: _t->encounterPEn(); break;
        case 7: _t->encouterHe(); break;
        case 8: _t->checkNewPos(); break;
        case 9: _t->enemyDead(); break;
        case 10: _t->penemyDead(); break;
        case 11: _t->poisonUser(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TerminalGameView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TerminalGameView::destinationFind)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TerminalGameView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TerminalGameView::automaticRun)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TerminalGameView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TerminalGameView::wChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TerminalGameView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TerminalGameView::terminalSpeedChanged)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TerminalGameView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TerminalGameView.data,
      qt_meta_data_TerminalGameView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TerminalGameView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TerminalGameView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TerminalGameView.stringdata0))
        return static_cast<void*>(const_cast< TerminalGameView*>(this));
    return QWidget::qt_metacast(_clname);
}

int TerminalGameView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void TerminalGameView::destinationFind()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TerminalGameView::automaticRun()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TerminalGameView::wChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TerminalGameView::terminalSpeedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
