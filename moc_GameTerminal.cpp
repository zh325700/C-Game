/****************************************************************************
** Meta object code from reading C++ file 'GameTerminal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GameTerminal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GameTerminal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameTerminal_t {
    QByteArrayData data[8];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameTerminal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameTerminal_t qt_meta_stringdata_GameTerminal = {
    {
QT_MOC_LITERAL(0, 0, 12), // "GameTerminal"
QT_MOC_LITERAL(1, 13, 15), // "penemyDefeating"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "onEnter"
QT_MOC_LITERAL(4, 38, 9), // "enemyDead"
QT_MOC_LITERAL(5, 48, 10), // "penemyDead"
QT_MOC_LITERAL(6, 59, 10), // "poisonUser"
QT_MOC_LITERAL(7, 70, 8) // "newLevel"

    },
    "GameTerminal\0penemyDefeating\0\0onEnter\0"
    "enemyDead\0penemyDead\0poisonUser\0"
    "newLevel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameTerminal[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    7,

       0        // eod
};

void GameTerminal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameTerminal *_t = static_cast<GameTerminal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->penemyDefeating(); break;
        case 1: _t->onEnter(); break;
        case 2: _t->enemyDead(); break;
        case 3: _t->penemyDead(); break;
        case 4: _t->poisonUser((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GameTerminal::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameTerminal::penemyDefeating)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject GameTerminal::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GameTerminal.data,
      qt_meta_data_GameTerminal,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GameTerminal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameTerminal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameTerminal.stringdata0))
        return static_cast<void*>(const_cast< GameTerminal*>(this));
    return QWidget::qt_metacast(_clname);
}

int GameTerminal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void GameTerminal::penemyDefeating()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
