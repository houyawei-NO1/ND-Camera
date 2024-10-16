/****************************************************************************
** Meta object code from reading C++ file 'ndmassegebox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ndmassegebox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ndmassegebox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ndmassegebox_t {
    QByteArrayData data[7];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ndmassegebox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ndmassegebox_t qt_meta_stringdata_ndmassegebox = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ndmassegebox"
QT_MOC_LITERAL(1, 13, 14), // "Clicked_btn_OK"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 18), // "Clicked_btn_Cancel"
QT_MOC_LITERAL(4, 48, 11), // "okBtn_press"
QT_MOC_LITERAL(5, 60, 15), // "cancleBtn_press"
QT_MOC_LITERAL(6, 76, 14) // "closeBtn_press"

    },
    "ndmassegebox\0Clicked_btn_OK\0\0"
    "Clicked_btn_Cancel\0okBtn_press\0"
    "cancleBtn_press\0closeBtn_press"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ndmassegebox[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   43,    2, 0x0a /* Public */,
       5,    0,   44,    2, 0x0a /* Public */,
       6,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ndmassegebox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ndmassegebox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Clicked_btn_OK((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->Clicked_btn_Cancel(); break;
        case 2: _t->okBtn_press(); break;
        case 3: _t->cancleBtn_press(); break;
        case 4: _t->closeBtn_press(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ndmassegebox::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ndmassegebox::Clicked_btn_OK)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ndmassegebox::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ndmassegebox::Clicked_btn_Cancel)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ndmassegebox::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ndmassegebox.data,
    qt_meta_data_ndmassegebox,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ndmassegebox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ndmassegebox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ndmassegebox.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ndmassegebox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ndmassegebox::Clicked_btn_OK(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ndmassegebox::Clicked_btn_Cancel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
