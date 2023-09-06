/****************************************************************************
** Meta object code from reading C++ file 'qmqttmessage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../qtmqtt-5.15/src/mqtt/qmqttmessage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmqttmessage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QMqttMessage_t {
    QByteArrayData data[8];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QMqttMessage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QMqttMessage_t qt_meta_stringdata_QMqttMessage = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QMqttMessage"
QT_MOC_LITERAL(1, 13, 5), // "topic"
QT_MOC_LITERAL(2, 19, 14), // "QMqttTopicName"
QT_MOC_LITERAL(3, 34, 7), // "payload"
QT_MOC_LITERAL(4, 42, 2), // "id"
QT_MOC_LITERAL(5, 45, 3), // "qos"
QT_MOC_LITERAL(6, 49, 9), // "duplicate"
QT_MOC_LITERAL(7, 59, 6) // "retain"

    },
    "QMqttMessage\0topic\0QMqttTopicName\0"
    "payload\0id\0qos\0duplicate\0retain"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMqttMessage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       6,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x00095409,
       3, QMetaType::QByteArray, 0x00095401,
       4, QMetaType::UShort, 0x00095401,
       5, QMetaType::UChar, 0x00095401,
       6, QMetaType::Bool, 0x00095401,
       7, QMetaType::Bool, 0x00095401,

       0        // eod
};

void QMqttMessage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMqttTopicName >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        QMqttMessage *_t = reinterpret_cast<QMqttMessage *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QMqttTopicName*>(_v) = _t->topic(); break;
        case 1: *reinterpret_cast< QByteArray*>(_v) = _t->payload(); break;
        case 2: *reinterpret_cast< quint16*>(_v) = _t->id(); break;
        case 3: *reinterpret_cast< quint8*>(_v) = _t->qos(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->duplicate(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->retain(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
}

const QMetaObject QMqttMessage::staticMetaObject = {
    { nullptr, qt_meta_stringdata_QMqttMessage.data,
      qt_meta_data_QMqttMessage,  qt_static_metacall, nullptr, nullptr}
};

QT_WARNING_POP
QT_END_MOC_NAMESPACE
