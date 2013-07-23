/****************************************************************************
** Meta object code from reading C++ file 'view_ticks.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "view_ticks.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view_ticks.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ViewTicks[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      25,   10,   10,   10, 0x08,
      38,   10,   10,   10, 0x08,
      50,   10,   10,   10, 0x08,
      63,   10,   10,   10, 0x08,
      82,   10,   10,   10, 0x08,
     100,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ViewTicks[] = {
    "ViewTicks\0\0updateTicks()\0applyTicks()\0"
    "doneTicks()\0labelProps()\0updateLabelProps()\0"
    "applyLabelProps()\0doneLabelProps()\0"
};

void ViewTicks::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ViewTicks *_t = static_cast<ViewTicks *>(_o);
        switch (_id) {
        case 0: _t->updateTicks(); break;
        case 1: _t->applyTicks(); break;
        case 2: _t->doneTicks(); break;
        case 3: _t->labelProps(); break;
        case 4: _t->updateLabelProps(); break;
        case 5: _t->applyLabelProps(); break;
        case 6: _t->doneLabelProps(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ViewTicks::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ViewTicks::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ViewTicks,
      qt_meta_data_ViewTicks, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ViewTicks::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ViewTicks::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ViewTicks::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ViewTicks))
        return static_cast<void*>(const_cast< ViewTicks*>(this));
    return QDialog::qt_metacast(_clname);
}

int ViewTicks::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
