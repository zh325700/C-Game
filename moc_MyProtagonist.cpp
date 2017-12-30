/****************************************************************************
** Meta object code from reading C++ file 'MyProtagonist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MyProtagonist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyProtagonist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyProtagonist_t {
    QByteArrayData data[15];
    char stringdata0[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyProtagonist_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyProtagonist_t qt_meta_stringdata_MyProtagonist = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MyProtagonist"
QT_MOC_LITERAL(1, 14, 15), // "protagonistDead"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 15), // "encounterPenemy"
QT_MOC_LITERAL(4, 47, 14), // "encounterEnemy"
QT_MOC_LITERAL(5, 62, 19), // "encounterHealthPack"
QT_MOC_LITERAL(6, 82, 8), // "inCircle"
QT_MOC_LITERAL(7, 91, 8), // "findNext"
QT_MOC_LITERAL(8, 100, 17), // "recoverAllButtons"
QT_MOC_LITERAL(9, 118, 14), // "moveToNextSpot"
QT_MOC_LITERAL(10, 133, 13), // "aquire_target"
QT_MOC_LITERAL(11, 147, 20), // "checkProtagonistDead"
QT_MOC_LITERAL(12, 168, 14), // "ifInPoisonarea"
QT_MOC_LITERAL(13, 183, 11), // "poisonValue"
QT_MOC_LITERAL(14, 195, 17) // "moveAlongWithPath"

    },
    "MyProtagonist\0protagonistDead\0\0"
    "encounterPenemy\0encounterEnemy\0"
    "encounterHealthPack\0inCircle\0findNext\0"
    "recoverAllButtons\0moveToNextSpot\0"
    "aquire_target\0checkProtagonistDead\0"
    "ifInPoisonarea\0poisonValue\0moveAlongWithPath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyProtagonist[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,
       5,    0,   77,    2, 0x06 /* Public */,
       6,    0,   78,    2, 0x06 /* Public */,
       7,    0,   79,    2, 0x06 /* Public */,
       8,    0,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   81,    2, 0x0a /* Public */,
      10,    0,   82,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    1,   84,    2, 0x0a /* Public */,
      14,    0,   87,    2, 0x0a /* Public */,

 // signals: parameters
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
    QMetaType::Void, QMetaType::Float,   13,
    QMetaType::Void,

       0        // eod
};

void MyProtagonist::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyProtagonist *_t = static_cast<MyProtagonist *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->protagonistDead(); break;
        case 1: _t->encounterPenemy(); break;
        case 2: _t->encounterEnemy(); break;
        case 3: _t->encounterHealthPack(); break;
        case 4: _t->inCircle(); break;
        case 5: _t->findNext(); break;
        case 6: _t->recoverAllButtons(); break;
        case 7: _t->moveToNextSpot(); break;
        case 8: _t->aquire_target(); break;
        case 9: _t->checkProtagonistDead(); break;
        case 10: _t->ifInPoisonarea((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->moveAlongWithPath(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyProtagonist::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyProtagonist::protagonistDead)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MyProtagonist::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyProtagonist::encounterPenemy)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MyProtagonist::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyProtagonist::encounterEnemy)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MyProtagonist::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyProtagonist::encounterHealthPack)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MyProtagonist::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyProtagonist::inCircle)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MyProtagonist::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyProtagonist::findNext)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MyProtagonist::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyProtagonist::recoverAllButtons)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject MyProtagonist::staticMetaObject = {
    { &Protagonist::staticMetaObject, qt_meta_stringdata_MyProtagonist.data,
      qt_meta_data_MyProtagonist,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyProtagonist::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyProtagonist::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyProtagonist.stringdata0))
        return static_cast<void*>(const_cast< MyProtagonist*>(this));
    if (!strcmp(_clname, "QGraphicsPixmapItem"))
        return static_cast< QGraphicsPixmapItem*>(const_cast< MyProtagonist*>(this));
    return Protagonist::qt_metacast(_clname);
}

int MyProtagonist::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Protagonist::qt_metacall(_c, _id, _a);
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
void MyProtagonist::protagonistDead()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MyProtagonist::encounterPenemy()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MyProtagonist::encounterEnemy()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MyProtagonist::encounterHealthPack()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MyProtagonist::inCircle()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MyProtagonist::findNext()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MyProtagonist::recoverAllButtons()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
