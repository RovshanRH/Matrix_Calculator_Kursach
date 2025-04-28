#ifndef MATRIX_CALCULATOR_H
#define MATRIX_CALCULATOR_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSpinBox>
#include <QVector>
#include <QApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include <QSpinBox>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>
#include <QIcon>
#include <QFrame>
#include <QSize>
#include <QLineEdit>
#include <QDoubleValidator>
#include <cmath>
#include "cleaner.h"
#include "inverse.h"
#include "operations.h"
#include "randomizer.h"
#include "copymatrix.h"
#include "insertmatrix.h"
#include "matrix.h"

class Matrix_Calculator : public QMainWindow {
    Q_OBJECT
public:
    Matrix_Calculator(QWidget* parent = nullptr);
    ~Matrix_Calculator();
private:
    QSpinBox *rowsASpinBox;
    QSpinBox *colsASpinBox;
    QSpinBox *rowsBSpinBox;
    QSpinBox *colsBSpinBox;
    QSpinBox *rowsCSpinBox;
    QSpinBox *colsCSpinBox;
    QSpinBox *razmerSpinBox;
    QLineEdit *constantA;
    QLineEdit *constantB;
    QTableWidget *matrixATable;
    QTableWidget *matrixBTable;
    QTableWidget *matrixCTable;
    matrix matr;
    Cleaner clean;
    Randomizer randomizer;
    inverse inverter;
    Operations oper;
    copymatrix copy;
    insertmatrix insert;
    QIcon *appIcon;
};

#endif // MATRIX_CALCULATOR_H
