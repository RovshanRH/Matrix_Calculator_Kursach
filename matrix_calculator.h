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

class Matrix_Calculator : public QMainWindow {
    Q_OBJECT
public:
    Matrix_Calculator(QWidget* parent = nullptr);
protected slots:
    void createMatrices();
    void createMatrixA();
    void createMatrixB();
    void createMatrixC();
    void createMatricesAB();

    // void clearMatrixA();
    // void clearMatrixB();
    // void clearMatrixC();

    // void addMatrices();
    // void subtractMatrices();
    // void multyplyMatrices();
    // void multyplyconstantA();
    // void multyplyconstantB();
    // void divisionconstantA();
    // void divisionconstantB();

    // void transposeMatrixA();
    // void transposeMatrixB();

    // void randomizeMatrixA();
    // void randomizeMatrixB();

    // void invertMatrixA();
    // void invertMatrixB();

    // void swapMatrices();

    void ChangeSize();
    bool AutoSizeCheck();

    void copymatrixA();
    void copymatrixB();
    void copymatrixC();
    void copyallmatrices();

    void insertmatrixA();
    void insertmatrixB();
    void pasteallmatrices();



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
    bool autoSizeEnabled = false;
    Cleaner clean;
    Randomizer randomizer;
    inverse inverter;
    Operations oper;

};

#endif // MATRIX_CALCULATOR_H
