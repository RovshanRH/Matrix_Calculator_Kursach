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
private slots:
    void createMatrices();
    void createMatrixA();
    void createMatrixB();
    void createMatrixC();
    void createMatricesAB();

    void clearMatrices(QTableWidget* matrix);
    void clearMatrixA();
    void clearMatrixB();
    void clearMatrixC();

    void addMatrices();
    void subtractMatrices();
    void multyplyMatrices();

    void transposeMatrix(QTableWidget *matrix);
    void transposeMatrixA();
    void transposeMatrixB();

    void randomizeMatrices(QTableWidget *matrix);
    void randomizeMatrixA();
    void randomizeMatrixB();

    QVector<QVector<double>> getMatrixFromTable(QTableWidget *table);
    void setMatrixToTable(QTableWidget *table, const QVector<QVector<double>> &matrix);
    double determinant(const QVector<QVector<double>> &matrix);
    QVector<QVector<double>> inverseMatrix(const QVector<QVector<double>> &matrix);
    void invertMatrix(QTableWidget *table);
    void invertMatrixA();
    void invertMatrixB();

    void swapMatrices();

    void multyconstantA();
    void multyconstantB();

private:
    QSpinBox *rowsASpinBox;
    QSpinBox *colsASpinBox;
    QSpinBox *rowsBSpinBox;
    QSpinBox *colsBSpinBox;
    QSpinBox *rowsCSpinBox;
    QSpinBox *colsCSpinBox;
    QSpinBox *razmerSpinBox;
    QSpinBox *constantA;
    QSpinBox *constantB;
    QTableWidget *matrixATable;
    QTableWidget *matrixBTable;
    QTableWidget *matrixCTable;
};

#endif // MATRIX_CALCULATOR_H
