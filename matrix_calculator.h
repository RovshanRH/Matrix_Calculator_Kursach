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
    void divisionconstantA();
    void divisionconstantB();

    void transposeMatrixA();
    void transposeMatrixB();

    void randomizeMatrixA();
    void randomizeMatrixB();

    void invertMatrixA();
    void invertMatrixB();

    void swapMatrices();

    void ChangeSize();
    bool AutoSizeCheck();

    void copymatrixA();
    void copymatrixB();
    void copymatrixC();
    void copyallmatrices();

    void insertmatrixA();
    void insertmatrixB();
    void insertmatrixC();

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
};

#endif // MATRIX_CALCULATOR_H
