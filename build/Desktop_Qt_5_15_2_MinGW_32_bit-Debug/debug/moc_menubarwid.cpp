/****************************************************************************
** Meta object code from reading C++ file 'menubarwid.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../menubarwid.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menubarwid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MenuBarWid_t {
    QByteArrayData data[12];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MenuBarWid_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MenuBarWid_t qt_meta_stringdata_MenuBarWid = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MenuBarWid"
QT_MOC_LITERAL(1, 11, 13), // "CurSelectPage"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "showMin"
QT_MOC_LITERAL(4, 34, 7), // "showMax"
QT_MOC_LITERAL(5, 42, 11), // "closeWidget"
QT_MOC_LITERAL(6, 54, 20), // "slot_btnGroupClicked"
QT_MOC_LITERAL(7, 75, 6), // "btnNum"
QT_MOC_LITERAL(8, 82, 15), // "slotSetTotleNum"
QT_MOC_LITERAL(9, 98, 12), // "rec_TotleNum"
QT_MOC_LITERAL(10, 111, 3), // "num"
QT_MOC_LITERAL(11, 115, 6) // "ReInit"

    },
    "MenuBarWid\0CurSelectPage\0\0showMin\0"
    "showMax\0closeWidget\0slot_btnGroupClicked\0"
    "btnNum\0slotSetTotleNum\0rec_TotleNum\0"
    "num\0ReInit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuBarWid[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    0,   57,    2, 0x06 /* Public */,
       4,    0,   58,    2, 0x06 /* Public */,
       5,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   60,    2, 0x0a /* Public */,
       8,    0,   63,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      11,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,

       0        // eod
};

void MenuBarWid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MenuBarWid *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CurSelectPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->showMin(); break;
        case 2: _t->showMax(); break;
        case 3: _t->closeWidget(); break;
        case 4: _t->slot_btnGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slotSetTotleNum(); break;
        case 6: _t->rec_TotleNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->ReInit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MenuBarWid::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuBarWid::CurSelectPage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MenuBarWid::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuBarWid::showMin)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MenuBarWid::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuBarWid::showMax)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MenuBarWid::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuBarWid::closeWidget)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MenuBarWid::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MenuBarWid.data,
    qt_meta_data_MenuBarWid,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MenuBarWid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuBarWid::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MenuBarWid.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MenuBarWid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void MenuBarWid::CurSelectPage(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MenuBarWid::showMin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MenuBarWid::showMax()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MenuBarWid::closeWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
