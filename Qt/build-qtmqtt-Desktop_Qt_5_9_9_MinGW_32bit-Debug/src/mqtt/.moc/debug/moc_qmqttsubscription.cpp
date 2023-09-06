/****************************************************************************
** Meta object code from reading C++ file 'qmqttsubscription.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../qtmqtt-5.15/src/mqtt/qmqttsubscription.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmqttsubscription.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QMqttSubscription_t {
    QByteArrayData data[23];
    char stringdata0[289];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QMqttSubscription_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QMqttSubscription_t qt_meta_stringdata_QMqttSubscription = {
    {
QT_MOC_LITERAL(0, 0, 17), // "QMqttSubscription"
QT_MOC_LITERAL(1, 18, 12), // "stateChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 17), // "SubscriptionState"
QT_MOC_LITERAL(4, 50, 5), // "state"
QT_MOC_LITERAL(5, 56, 10), // "qosChanged"
QT_MOC_LITERAL(6, 67, 15), // "messageReceived"
QT_MOC_LITERAL(7, 83, 12), // "QMqttMessage"
QT_MOC_LITERAL(8, 96, 3), // "msg"
QT_MOC_LITERAL(9, 100, 11), // "unsubscribe"
QT_MOC_LITERAL(10, 112, 3), // "qos"
QT_MOC_LITERAL(11, 116, 5), // "topic"
QT_MOC_LITERAL(12, 122, 16), // "QMqttTopicFilter"
QT_MOC_LITERAL(13, 139, 6), // "reason"
QT_MOC_LITERAL(14, 146, 10), // "reasonCode"
QT_MOC_LITERAL(15, 157, 17), // "QMqtt::ReasonCode"
QT_MOC_LITERAL(16, 175, 18), // "sharedSubscription"
QT_MOC_LITERAL(17, 194, 22), // "sharedSubscriptionName"
QT_MOC_LITERAL(18, 217, 12), // "Unsubscribed"
QT_MOC_LITERAL(19, 230, 19), // "SubscriptionPending"
QT_MOC_LITERAL(20, 250, 10), // "Subscribed"
QT_MOC_LITERAL(21, 261, 21), // "UnsubscriptionPending"
QT_MOC_LITERAL(22, 283, 5) // "Error"

    },
    "QMqttSubscription\0stateChanged\0\0"
    "SubscriptionState\0state\0qosChanged\0"
    "messageReceived\0QMqttMessage\0msg\0"
    "unsubscribe\0qos\0topic\0QMqttTopicFilter\0"
    "reason\0reasonCode\0QMqtt::ReasonCode\0"
    "sharedSubscription\0sharedSubscriptionName\0"
    "Unsubscribed\0SubscriptionPending\0"
    "Subscribed\0UnsubscriptionPending\0Error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMqttSubscription[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       7,   44, // properties
       1,   72, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,
       6,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::UChar,    2,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags
       4, 0x80000000 | 3, 0x00495009,
      10, QMetaType::UChar, 0x00495001,
      11, 0x80000000 | 12, 0x00095009,
      13, QMetaType::QString, 0x00095001,
      14, 0x80000000 | 15, 0x00095009,
      16, QMetaType::Bool, 0x00095001,
      17, QMetaType::QString, 0x00095001,

 // properties: notify_signal_id
       0,
       1,
       0,
       0,
       0,
       0,
       0,

 // enums: name, flags, count, data
       3, 0x0,    5,   76,

 // enum data: key, value
      18, uint(QMqttSubscription::Unsubscribed),
      19, uint(QMqttSubscription::SubscriptionPending),
      20, uint(QMqttSubscription::Subscribed),
      21, uint(QMqttSubscription::UnsubscriptionPending),
      22, uint(QMqttSubscription::Error),

       0        // eod
};

void QMqttSubscription::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QMqttSubscription *_t = static_cast<QMqttSubscription *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< SubscriptionState(*)>(_a[1]))); break;
        case 1: _t->qosChanged((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 2: _t->messageReceived((*reinterpret_cast< QMqttMessage(*)>(_a[1]))); break;
        case 3: _t->unsubscribe(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMqttMessage >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QMqttSubscription::*_t)(SubscriptionState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMqttSubscription::stateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QMqttSubscription::*_t)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMqttSubscription::qosChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QMqttSubscription::*_t)(QMqttMessage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMqttSubscription::messageReceived)) {
                *result = 2;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMqttTopicFilter >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        QMqttSubscription *_t = static_cast<QMqttSubscription *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< SubscriptionState*>(_v) = _t->state(); break;
        case 1: *reinterpret_cast< quint8*>(_v) = _t->qos(); break;
        case 2: *reinterpret_cast< QMqttTopicFilter*>(_v) = _t->topic(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->reason(); break;
        case 4: *reinterpret_cast< QMqtt::ReasonCode*>(_v) = _t->reasonCode(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->isSharedSubscription(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->sharedSubscriptionName(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject QMqttSubscription::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QMqttSubscription.data,
      qt_meta_data_QMqttSubscription,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QMqttSubscription::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMqttSubscription::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QMqttSubscription.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QMqttSubscription::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QMqttSubscription::stateChanged(SubscriptionState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QMqttSubscription::qosChanged(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QMqttSubscription::messageReceived(QMqttMessage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
