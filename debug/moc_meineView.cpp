/****************************************************************************
** Meta object code from reading C++ file 'meineView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../meineView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'meineView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MeineView_t {
    QByteArrayData data[4];
    char stringdata[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MeineView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MeineView_t qt_meta_stringdata_MeineView = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 12),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 13)
    },
    "MeineView\0zoomInSignal\0\0zoomOutSignal\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MeineView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x05,
       3,    0,   25,    2, 0x05,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MeineView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MeineView *_t = static_cast<MeineView *>(_o);
        switch (_id) {
        case 0: _t->zoomInSignal(); break;
        case 1: _t->zoomOutSignal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MeineView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MeineView::zoomInSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (MeineView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MeineView::zoomOutSignal)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MeineView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_MeineView.data,
      qt_meta_data_MeineView,  qt_static_metacall, 0, 0}
};


const QMetaObject *MeineView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeineView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MeineView.stringdata))
        return static_cast<void*>(const_cast< MeineView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int MeineView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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
void MeineView::zoomInSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MeineView::zoomOutSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
