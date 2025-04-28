#ifndef MATRIX_H
#define MATRIX_H


#include "cleaner.h"
#include "copymatrix.h"
#include "insertmatrix.h"
#include "inverse.h"
#include "operations.h"
#include "randomizer.h"
#include <QObject>
#include <QSpinBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>

class matrix : public QObject
{
    Q_OBJECT
public:
    matrix(QObject* parent = nullptr);
public slots:
    void create3Matrices(QTableWidget* matrix1, QTableWidget* matrix2, QTableWidget* matrix3, int rows, int cols);
    void create2Matrices(QTableWidget* matrix1, QTableWidget* matrix2, int rows, int cols);
    void createMatrix(QTableWidget* matrix, int rows, int cols);

private:
    QSpinBox* rowsSpinBox;
    QSpinBox* colsSpinBox;
    QLineEdit* constant;
    QSpinBox* razmerSpinBox;
    QTableWidget* matrixTable;
    Cleaner clean;
    Randomizer randomizer;
    inverse inverter;
    Operations oper;
    copymatrix copy;
    insertmatrix insert;

};

#endif // MATRIX_H
