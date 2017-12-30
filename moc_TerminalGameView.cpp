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
    QByteArrayData data[18];
    char stringdata0[208];
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
QT_MOC_LITERAL(4, 47, 10), // "saveRecord"
QT_MOC_LITERAL(5, 58, 10), // "loadRecord"
QT_MOC_LITERAL(6, 69, 10), // "loadNewMap"
QT_MOC_LITERAL(7, 80, 10), // "clearSaves"
QT_MOC_LITERAL(8, 91, 8), // "wChanged"
QT_MOC_LITERAL(9, 100, 20), // "terminalSpeedChanged"
QT_MOC_LITERAL(10, 121, 7), // "onEnter"
QT_MOC_LITERAL(11, 129, 10), // "encouterEn"
QT_MOC_LITERAL(12, 140, 12), // "encounterPEn"
QT_MOC_LITERAL(13, 153, 10), // "encouterHe"
QT_MOC_LITERAL(14, 164, 11), // "checkNewPos"
QT_MOC_LITERAL(15, 176, 9), // "enemyDead"
QT_MOC_LITERAL(16, 186, 10), // "penemyDead"
QT_MOC_LITERAL(17, 197, 10) // "poisonUser"

    },
    "TerminalGameView\0destinationFind\0\0"
    "automaticRun\0saveRecord\0loadRecord\0"
    "loadNewMap\0clearSaves\0wChanged\0"
    "terminalSpeedChanged\0onEnter\0encouterEn\0"
    "encounterPEn\0encouterHe\0checkNewPos\0"
    "enemyDead\0penemyDead\0poisonUser"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TerminalGameView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    0,   96,    2, 0x06 /* Public */,
       5,    0,   97,    2, 0x06 /* Public */,
       6,    0,   98,    2, 0x06 /* Public */,
       7,    0,   99,    2, 0x06 /* Public */,
       8,    0,  100,    2, 0x06 /* Public */,
       9,    0,  101,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,  102,    2, 0x0a /* Public */,
      11,    0,  103,    2, 0x0a /* Public */,
      12,    0,  104,    2, 0x0a /* Public */,
      13,    0,  105,    2, 0x0a /* Public */,
      14,    0,  106,    2, 0x0a /* Public */,
      15,    0,  107,    2, 0x0a /* Public */,
      16,    0,  108,    2, 0x0a /* Public */,
      17,    0,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        case 2: _t->saveRecord(); break;
        case 3: _t->loadRecord(); break;
        case 4: _t->loadNewMap(); break;
        case 5: _t->clearSaves(); break;
        case 6: _t->wChanged(); break;
        case 7: _t->terminalSpeedChanged(); break;
        case 8: _t->onEnter(); break;
        case 9: _t->encouterEn(); break;
        case 10: _t->encounterPEn(); break;
        case 11: _t->encouterHe(); break;
        case 12: _t->checkNewPos(); break;
        case 13: _t->enemyDead(); break;
        case 14: _t->penemyDead(); break;
        case 15: _t->poisonUser(); break;
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
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TerminalGameView::saveRecord)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TerminalGameView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TerminalGameView::loadRecord)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (TerminalGameView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TerminalGameView::loadNewMap)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (TerminalGameView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TerminalGameView::clearSaves)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (TerminalGameView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TerminalGameView::wChanged)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (TerminalGameView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TerminalGameView::terminalSpeedChanged)) {
                *result = 7;
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
void TerminalGameView::saveRecord()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TerminalGameView::loadRecord()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void TerminalGameView::loadNewMap()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void TerminalGameView::clearSaves()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void TerminalGameView::wChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void TerminalGameView::terminalSpeedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
