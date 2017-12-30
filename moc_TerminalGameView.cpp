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
    char stringdata0[149];
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
QT_MOC_LITERAL(3, 34, 5), // "speed"
QT_MOC_LITERAL(4, 40, 12), // "automaticRun"
QT_MOC_LITERAL(5, 53, 8), // "wChanged"
QT_MOC_LITERAL(6, 62, 7), // "onEnter"
QT_MOC_LITERAL(7, 70, 10), // "encouterEn"
QT_MOC_LITERAL(8, 81, 12), // "encounterPEn"
QT_MOC_LITERAL(9, 94, 10), // "encouterHe"
QT_MOC_LITERAL(10, 105, 11), // "checkNewPos"
QT_MOC_LITERAL(11, 117, 9), // "enemyDead"
QT_MOC_LITERAL(12, 127, 10), // "penemyDead"
QT_MOC_LITERAL(13, 138, 10) // "poisonUser"

    },
    "TerminalGameView\0destinationFind\0\0"
    "speed\0automaticRun\0wChanged\0onEnter\0"
    "encouterEn\0encounterPEn\0encouterHe\0"
    "checkNewPos\0enemyDead\0penemyDead\0"
    "poisonUser"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TerminalGameView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    0,   72,    2, 0x06 /* Public */,
       5,    0,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   74,    2, 0x0a /* Public */,
       7,    0,   75,    2, 0x0a /* Public */,
       8,    0,   76,    2, 0x0a /* Public */,
       9,    0,   77,    2, 0x0a /* Public */,
      10,    0,   78,    2, 0x0a /* Public */,
      11,    0,   79,    2, 0x0a /* Public */,
      12,    0,   80,    2, 0x0a /* Public */,
      13,    0,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
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
        case 0: _t->destinationFind((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->automaticRun(); break;
        case 2: _t->wChanged(); break;
        case 3: _t->onEnter(); break;
        case 4: _t->encouterEn(); break;
        case 5: _t->encounterPEn(); break;
        case 6: _t->encouterHe(); break;
        case 7: _t->checkNewPos(); break;
        case 8: _t->enemyDead(); break;
        case 9: _t->penemyDead(); break;
        case 10: _t->poisonUser(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TerminalGameView::*_t)(int );
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
    }
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void TerminalGameView::destinationFind(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
