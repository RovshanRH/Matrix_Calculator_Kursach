#ifndef MATRIX_CALCULATOR_H
#define MATRIX_CALCULATOR_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSpinBox>
#include <QVector>

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

    void clearMatrixA();
    void clearMatrixB();
    void clearMatrixC();

    void addMatrices();
    void subtractMatrices();
    void multyplyMatrices();
    void multyplyconstantA();
    void multyplyconstantB();

    void transposeMatrixA();
    void transposeMatrixB();

    void randomizeMatrixA();
    void randomizeMatrixB();

    void invertMatrixA();
    void invertMatrixB();

    void swapMatrices();

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
};

#endif // MATRIX_CALCULATOR_H
