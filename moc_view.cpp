/****************************************************************************
** Meta object code from reading C++ file 'view.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "view.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ViewMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      18,    9,    9,    9, 0x0a,
      28,    9,    9,    9, 0x0a,
      36,    9,    9,    9, 0x0a,
      46,    9,    9,    9, 0x0a,
      61,    9,    9,    9, 0x08,
      75,    9,    9,    9, 0x08,
      90,    9,    9,    9, 0x08,
     104,    9,    9,    9, 0x08,
     123,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ViewMenu[] = {
    "ViewMenu\0\0world()\0symbols()\0ticks()\0"
    "legends()\0applyLegends()\0doneLegends()\0"
    "placeLegends()\0legendsEdit()\0"
    "applyLegendsEdit()\0doneLegendsEdit()\0"
};

void ViewMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ViewMenu *_t = static_cast<ViewMenu *>(_o);
        switch (_id) {
        case 0: _t->world(); break;
        case 1: _t->symbols(); break;
        case 2: _t->ticks(); break;
        case 3: _t->legends(); break;
        case 4: _t->applyLegends(); break;
        case 5: _t->doneLegends(); break;
        case 6: _t->placeLegends(); break;
        case 7: _t->legendsEdit(); break;
        case 8: _t->applyLegendsEdit(); break;
        case 9: _t->doneLegendsEdit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ViewMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ViewMenu::staticMetaObject = {
    { &QMenu::staticMetaObject, qt_meta_stringdata_ViewMenu,
      qt_meta_data_ViewMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ViewMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ViewMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ViewMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ViewMenu))
        return static_cast<void*>(const_cast< ViewMenu*>(this));
    return QMenu::qt_metacast(_clname);
}

int ViewMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
