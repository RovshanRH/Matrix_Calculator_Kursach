/****************************************************************************
** Meta object code from reading C++ file 'operations.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../operations.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'operations.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10OperationsE_t {};
} // unnamed namespace

template <> constexpr inline auto Operations::qt_create_metaobjectdata<qt_meta_tag_ZN10OperationsE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Operations",
        "addMatrices",
        "",
        "QTableWidget*",
        "matrix1",
        "matrix2",
        "matrix3",
        "subtractMatrices",
        "multyplyMatrices",
        "swapMatrices",
        "QList<QList<double>>",
        "tempB",
        "tempA",
        "multyplyconstant",
        "matrix",
        "cnst",
        "divisionconstant",
        "rows_getter",
        "cols_getter",
        "settempA",
        "rows",
        "cols",
        "settempB",
        "transposeMatrix"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'addMatrices'
        QtMocHelpers::SlotData<void(QTableWidget *, QTableWidget *, QTableWidget *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 3, 5 }, { 0x80000000 | 3, 6 },
        }}),
        // Slot 'subtractMatrices'
        QtMocHelpers::SlotData<void(QTableWidget *, QTableWidget *, QTableWidget *)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 3, 5 }, { 0x80000000 | 3, 6 },
        }}),
        // Slot 'multyplyMatrices'
        QtMocHelpers::SlotData<void(QTableWidget *, QTableWidget *, QTableWidget *)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 3, 5 }, { 0x80000000 | 3, 6 },
        }}),
        // Slot 'swapMatrices'
        QtMocHelpers::SlotData<void(QTableWidget *, QTableWidget *, QVector<QVector<double>>, QVector<QVector<double>>)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 3, 5 }, { 0x80000000 | 10, 11 }, { 0x80000000 | 10, 12 },
        }}),
        // Slot 'multyplyconstant'
        QtMocHelpers::SlotData<void(QTableWidget *, double)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 14 }, { QMetaType::Double, 15 },
        }}),
        // Slot 'divisionconstant'
        QtMocHelpers::SlotData<void(QTableWidget *, double)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 14 }, { QMetaType::Double, 15 },
        }}),
        // Slot 'rows_getter'
        QtMocHelpers::SlotData<int(QTableWidget *)>(17, 2, QMC::AccessPublic, QMetaType::Int, {{
            { 0x80000000 | 3, 14 },
        }}),
        // Slot 'cols_getter'
        QtMocHelpers::SlotData<int(QTableWidget *)>(18, 2, QMC::AccessPublic, QMetaType::Int, {{
            { 0x80000000 | 3, 14 },
        }}),
        // Slot 'settempA'
        QtMocHelpers::SlotData<QVector<QVector<double>>(int, int, QTableWidget *)>(19, 2, QMC::AccessPublic, 0x80000000 | 10, {{
            { QMetaType::Int, 20 }, { QMetaType::Int, 21 }, { 0x80000000 | 3, 14 },
        }}),
        // Slot 'settempB'
        QtMocHelpers::SlotData<QVector<QVector<double>>(int, int, QTableWidget *)>(22, 2, QMC::AccessPublic, 0x80000000 | 10, {{
            { QMetaType::Int, 20 }, { QMetaType::Int, 21 }, { 0x80000000 | 3, 14 },
        }}),
        // Slot 'transposeMatrix'
        QtMocHelpers::SlotData<void(QTableWidget *)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 14 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Operations, qt_meta_tag_ZN10OperationsE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Operations::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10OperationsE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10OperationsE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10OperationsE_t>.metaTypes,
    nullptr
} };

void Operations::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Operations *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->addMatrices((*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[3]))); break;
        case 1: _t->subtractMatrices((*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[3]))); break;
        case 2: _t->multyplyMatrices((*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[3]))); break;
        case 3: _t->swapMatrices((*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QList<QList<double>>>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QList<QList<double>>>>(_a[4]))); break;
        case 4: _t->multyplyconstant((*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 5: _t->divisionconstant((*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 6: { int _r = _t->rows_getter((*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: { int _r = _t->cols_getter((*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: { QList<QList<double>> _r = _t->settempA((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QList<QList<double>>*>(_a[0]) = std::move(_r); }  break;
        case 9: { QList<QList<double>> _r = _t->settempB((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QList<QList<double>>*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->transposeMatrix((*reinterpret_cast< std::add_pointer_t<QTableWidget*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTableWidget* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTableWidget* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTableWidget* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 3:
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QList<double>> >(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTableWidget* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTableWidget* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTableWidget* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTableWidget* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTableWidget* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTableWidget* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTableWidget* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTableWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *Operations::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10OperationsE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Operations::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
