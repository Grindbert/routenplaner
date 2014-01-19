/****************************************************************************
** Meta object code from reading C++ file 'meineSzene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../meineSzene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'meineSzene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MeineSzene_t {
    QByteArrayData data[8];
    char stringdata[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MeineSzene_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MeineSzene_t qt_meta_stringdata_MeineSzene = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 15),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 22),
QT_MOC_LITERAL(4, 51, 23),
QT_MOC_LITERAL(5, 75, 15),
QT_MOC_LITERAL(6, 91, 25),
QT_MOC_LITERAL(7, 117, 17)
    },
    "MeineSzene\0rechteMaustaste\0\0"
    "linkeMaustasteGedruckt\0linkeMaustasteLoslassen\0"
    "mousePressEvent\0QGraphicsSceneMouseEvent*\0"
    "mouseReleaseEvent\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MeineSzene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x05,
       3,    2,   42,    2, 0x05,
       4,    2,   47,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    1,   52,    2, 0x08,
       7,    1,   55,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QPointF,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QPointF,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

       0        // eod
};

void MeineSzene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MeineSzene *_t = static_cast<MeineSzene *>(_o);
        switch (_id) {
        case 0: _t->rechteMaustaste((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 1: _t->linkeMaustasteGedruckt((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 2: _t->linkeMaustasteLoslassen((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 3: _t->mousePressEvent((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->mouseReleaseEvent((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MeineSzene::*_t)(QPointF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MeineSzene::rechteMaustaste)) {
                *result = 0;
            }
        }
        {
            typedef void (MeineSzene::*_t)(bool , QPointF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MeineSzene::linkeMaustasteGedruckt)) {
                *result = 1;
            }
        }
        {
            typedef void (MeineSzene::*_t)(bool , QPointF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MeineSzene::linkeMaustasteLoslassen)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject MeineSzene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_MeineSzene.data,
      qt_meta_data_MeineSzene,  qt_static_metacall, 0, 0}
};


const QMetaObject *MeineSzene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeineSzene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MeineSzene.stringdata))
        return static_cast<void*>(const_cast< MeineSzene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int MeineSzene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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
void MeineSzene::rechteMaustaste(QPointF _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MeineSzene::linkeMaustasteGedruckt(bool _t1, QPointF _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MeineSzene::linkeMaustasteLoslassen(bool _t1, QPointF _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
