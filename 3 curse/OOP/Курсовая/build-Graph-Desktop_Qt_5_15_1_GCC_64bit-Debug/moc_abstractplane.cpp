/****************************************************************************
** Meta object code from reading C++ file 'abstractplane.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Graph/abstractplane.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstractplane.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CoordinatePlane_t {
    QByteArrayData data[9];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CoordinatePlane_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CoordinatePlane_t qt_meta_stringdata_CoordinatePlane = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CoordinatePlane"
QT_MOC_LITERAL(1, 16, 11), // "sizeChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "prevSize"
QT_MOC_LITERAL(4, 38, 11), // "currentSize"
QT_MOC_LITERAL(5, 50, 14), // "eventCursorPos"
QT_MOC_LITERAL(6, 65, 16), // "currentCursorPos"
QT_MOC_LITERAL(7, 82, 20), // "helpLinesFlagChanged"
QT_MOC_LITERAL(8, 103, 4) // "flag"

    },
    "CoordinatePlane\0sizeChanged\0\0prevSize\0"
    "currentSize\0eventCursorPos\0currentCursorPos\0"
    "helpLinesFlagChanged\0flag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CoordinatePlane[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   24,    2, 0x06 /* Public */,
       7,    1,   33,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QPointF, QMetaType::QPointF,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void CoordinatePlane::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CoordinatePlane *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sizeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QPointF(*)>(_a[3])),(*reinterpret_cast< QPointF(*)>(_a[4]))); break;
        case 1: _t->helpLinesFlagChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CoordinatePlane::*)(int , int , QPointF , QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CoordinatePlane::sizeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CoordinatePlane::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CoordinatePlane::helpLinesFlagChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CoordinatePlane::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CoordinatePlane.data,
    qt_meta_data_CoordinatePlane,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CoordinatePlane::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CoordinatePlane::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CoordinatePlane.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CoordinatePlane::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CoordinatePlane::sizeChanged(int _t1, int _t2, QPointF _t3, QPointF _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CoordinatePlane::helpLinesFlagChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
