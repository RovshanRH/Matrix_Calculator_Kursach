#ifndef STABILIZINGCSIZE_H
#define STABILIZINGCSIZE_H

#include <QObject>
#include "matrix_calculator.h"

class stabilizingCsize : protected Matrix_Calculator
{
    Q_OBJECT
public:
    stabilizingCsize(QWidget *parent = nullptr);
protected slots:
    void stabilizeSum(int rows, int cols);
    void stabilizeSub(int rows, int cols);
    void stabilizeUmno(int rows, int cols);
};

#endif // STABILIZINGCSIZE_H
