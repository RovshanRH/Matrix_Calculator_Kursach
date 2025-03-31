#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "stabilizingcsize.h"
#include <QObject>
#include <QTableWidget>
#include <QMessageBox>

class Operations : protected stabilizingCsize
{
    Q_OBJECT
public:
    Operations(QWidget *parent = nullptr);
public slots:
    void addMatrices(QTableWidget *matrix1, QTableWidget *matrix2);
    void subtractMatrices(QTableWidget *matrix1, QTableWidget *matrix2);
    void multyplyMatrices(QTableWidget *matrix1, QTableWidget *matrix2);
    // void swapMatrices();
    void multyplyconstant(QTableWidget *matrix, double cnst);
};

#endif // OPERATIONS_H
