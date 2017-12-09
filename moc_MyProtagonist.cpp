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
    QByteArrayData data[9];
    char stringdata0[124];
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
QT_MOC_LITERAL(4, 47, 14), // "moveToNextSpot"
QT_MOC_LITERAL(5, 62, 13), // "aquire_target"
QT_MOC_LITERAL(6, 76, 20), // "checkProtagonistDead"
QT_MOC_LITERAL(7, 97, 14), // "ifInPoisonarea"
QT_MOC_LITERAL(8, 112, 11) // "poisonValue"

    },
    "MyProtagonist\0protagonistDead\0\0"
    "encounterPenemy\0moveToNextSpot\0"
    "aquire_target\0checkProtagonistDead\0"
    "ifInPoisonarea\0poisonValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyProtagonist[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    1,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    8,

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
        case 2: _t->moveToNextSpot(); break;
        case 3: _t->aquire_target(); break;
        case 4: _t->checkProtagonistDead(); break;
        case 5: _t->ifInPoisonarea((*reinterpret_cast< float(*)>(_a[1]))); break;
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
