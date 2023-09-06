/****************************************************************************
** Meta object code from reading C++ file 'dial.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../smart_home/dial.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dial.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dial_t {
    QByteArrayData data[17];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dial_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dial_t qt_meta_stringdata_Dial = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Dial"
QT_MOC_LITERAL(1, 5, 8), // "setTitle"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 5), // "title"
QT_MOC_LITERAL(4, 21, 8), // "setValue"
QT_MOC_LITERAL(5, 30, 5), // "value"
QT_MOC_LITERAL(6, 36, 13), // "setScaleMinor"
QT_MOC_LITERAL(7, 50, 10), // "scaleMinor"
QT_MOC_LITERAL(8, 61, 11), // "setMinValue"
QT_MOC_LITERAL(9, 73, 8), // "minValue"
QT_MOC_LITERAL(10, 82, 11), // "setMaxValue"
QT_MOC_LITERAL(11, 94, 8), // "maxValue"
QT_MOC_LITERAL(12, 103, 8), // "setRange"
QT_MOC_LITERAL(13, 112, 13), // "setForeground"
QT_MOC_LITERAL(14, 126, 10), // "foreground"
QT_MOC_LITERAL(15, 137, 13), // "setBackground"
QT_MOC_LITERAL(16, 151, 10) // "background"

    },
    "Dial\0setTitle\0\0title\0setValue\0value\0"
    "setScaleMinor\0scaleMinor\0setMinValue\0"
    "minValue\0setMaxValue\0maxValue\0setRange\0"
    "setForeground\0foreground\0setBackground\0"
    "background"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dial[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       4,    1,   57,    2, 0x0a /* Public */,
       6,    1,   60,    2, 0x0a /* Public */,
       8,    1,   63,    2, 0x0a /* Public */,
      10,    1,   66,    2, 0x0a /* Public */,
      12,    2,   69,    2, 0x0a /* Public */,
      13,    1,   74,    2, 0x0a /* Public */,
      15,    1,   77,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   11,
    QMetaType::Void, QMetaType::QColor,   14,
    QMetaType::Void, QMetaType::QColor,   16,

       0        // eod
};

void Dial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dial *_t = static_cast<Dial *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setScaleMinor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setMinValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setMaxValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->setForeground((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 7: _t->setBackground((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Dial::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Dial.data,
      qt_meta_data_Dial,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Dial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dial.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Dial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
