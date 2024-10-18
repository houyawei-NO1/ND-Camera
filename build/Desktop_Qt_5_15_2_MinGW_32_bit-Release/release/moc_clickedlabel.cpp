/****************************************************************************
** Meta object code from reading C++ file 'clickedlabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../clickedlabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clickedlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClickedLabel_t {
    QByteArrayData data[7];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClickedLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClickedLabel_t qt_meta_stringdata_ClickedLabel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ClickedLabel"
QT_MOC_LITERAL(1, 13, 7), // "Clicked"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "ClickedLabel*"
QT_MOC_LITERAL(4, 36, 7), // "clicked"
QT_MOC_LITERAL(5, 44, 16), // "ClickedItemIndex"
QT_MOC_LITERAL(6, 61, 15) // "MouseMoveToItem"

    },
    "ClickedLabel\0Clicked\0\0ClickedLabel*\0"
    "clicked\0ClickedItemIndex\0MouseMoveToItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClickedLabel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    2,   32,    2, 0x06 /* Public */,
       6,    2,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,

       0        // eod
};

void ClickedLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClickedLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Clicked((*reinterpret_cast< ClickedLabel*(*)>(_a[1]))); break;
        case 1: _t->ClickedItemIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< ClickedLabel*(*)>(_a[2]))); break;
        case 2: _t->MouseMoveToItem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< ClickedLabel*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ClickedLabel* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ClickedLabel* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ClickedLabel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClickedLabel::*)(ClickedLabel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClickedLabel::Clicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ClickedLabel::*)(int , ClickedLabel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClickedLabel::ClickedItemIndex)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ClickedLabel::*)(int , ClickedLabel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClickedLabel::MouseMoveToItem)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ClickedLabel::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_ClickedLabel.data,
    qt_meta_data_ClickedLabel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ClickedLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClickedLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClickedLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int ClickedLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ClickedLabel::Clicked(ClickedLabel * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClickedLabel::ClickedItemIndex(int _t1, ClickedLabel * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClickedLabel::MouseMoveToItem(int _t1, ClickedLabel * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
