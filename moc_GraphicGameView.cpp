/****************************************************************************
** Meta object code from reading C++ file 'GraphicGameView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GraphicGameView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GraphicGameView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GraphicGameView_t {
    QByteArrayData data[10];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicGameView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicGameView_t qt_meta_stringdata_GraphicGameView = {
    {
QT_MOC_LITERAL(0, 0, 15), // "GraphicGameView"
QT_MOC_LITERAL(1, 16, 17), // "EnermyNrDecreased"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 18), // "PEnermyNrDecreased"
QT_MOC_LITERAL(4, 54, 17), // "drawPoinsonCircle"
QT_MOC_LITERAL(5, 72, 11), // "deletePnemy"
QT_MOC_LITERAL(6, 84, 11), // "deleteEnemy"
QT_MOC_LITERAL(7, 96, 11), // "drawThePath"
QT_MOC_LITERAL(8, 108, 17), // "changeCircleColor"
QT_MOC_LITERAL(9, 126, 11) // "changeTimer"

    },
    "GraphicGameView\0EnermyNrDecreased\0\0"
    "PEnermyNrDecreased\0drawPoinsonCircle\0"
    "deletePnemy\0deleteEnemy\0drawThePath\0"
    "changeCircleColor\0changeTimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicGameView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GraphicGameView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphicGameView *_t = static_cast<GraphicGameView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->EnermyNrDecreased(); break;
        case 1: _t->PEnermyNrDecreased(); break;
        case 2: _t->drawPoinsonCircle(); break;
        case 3: _t->deletePnemy(); break;
        case 4: _t->deleteEnemy(); break;
        case 5: _t->drawThePath(); break;
        case 6: _t->changeCircleColor(); break;
        case 7: _t->changeTimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GraphicGameView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicGameView::EnermyNrDecreased)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GraphicGameView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicGameView::PEnermyNrDecreased)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject GraphicGameView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GraphicGameView.data,
      qt_meta_data_GraphicGameView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GraphicGameView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicGameView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicGameView.stringdata0))
        return static_cast<void*>(const_cast< GraphicGameView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GraphicGameView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void GraphicGameView::EnermyNrDecreased()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GraphicGameView::PEnermyNrDecreased()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
