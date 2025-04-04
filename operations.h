#ifndef OPERATIONS_H
#define OPERATIONS_H

// #include "stabilizingcsize.h"
#include <QObject>
#include <QTableWidget>
#include <QMessageBox>

class Operations : public QObject
{
    Q_OBJECT
public:
    Operations(QObject *parent = nullptr);
public slots:
    void addMatrices(QTableWidget *matrix1, QTableWidget *matrix2, QTableWidget *matrix3);
    void subtractMatrices(QTableWidget *matrix1, QTableWidget *matrix2, QTableWidget *matrix3);
    void multyplyMatrices(QTableWidget *matrix1, QTableWidget *matrix2, QTableWidget *matrix3);
    void swapMatrices(QTableWidget *matrix1, QTableWidget *matrix2, QVector<QVector<double>> tempB, QVector<QVector<double>> tempA);
    void multyplyconstant(QTableWidget *matrix, QString cnst);

    int rowsA_getter(QTableWidget *matrix);
    int rowsB_getter(QTableWidget *matrix);
    int colsA_getter(QTableWidget *matrix);
    int colsB_getter(QTableWidget *matrix);

    QVector<QVector<double>> settempA(int rows, int cols, QTableWidget *matrix);
    QVector<QVector<double>> settempB(int rows, int cols, QTableWidget *matrix);

    void transposeMatrix(QTableWidget *matrix);

};

#endif // OPERATIONS_H
