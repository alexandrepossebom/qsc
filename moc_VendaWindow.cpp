/****************************************************************************
** Meta object code from reading C++ file 'VendaWindow.h'
**
** Created: Fri Sep 11 15:13:36 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "VendaWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VendaWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VendaWindow[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_VendaWindow[] = {
    "VendaWindow\0"
};

const QMetaObject VendaWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_VendaWindow,
      qt_meta_data_VendaWindow, 0 }
};

const QMetaObject *VendaWindow::metaObject() const
{
    return &staticMetaObject;
}

void *VendaWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VendaWindow))
        return static_cast<void*>(const_cast< VendaWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int VendaWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
