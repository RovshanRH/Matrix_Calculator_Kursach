#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QObject>
#include <QTableWidget>
#include <QMessageBox>
#include <QVector>
#include "inverse.h"

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
    void multyplyconstant(QTableWidget *matrix, double cnst);
    void divisionconstant(QTableWidget *matrix, double cnst);
    int FindRang(QTableWidget *matrix);

    int rows_getter(QTableWidget *matrix);
    int cols_getter(QTableWidget *matrix);

    QVector<QVector<double>> settempA(int rows, int cols, QTableWidget *matrix);
    QVector<QVector<double>> settempB(int rows, int cols, QTableWidget *matrix);

    void transposeMatrix(QTableWidget *matrix);
private:
    inverse inv;

};

#endif // OPERATIONS_H
