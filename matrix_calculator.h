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
    void multyplyconstant(QTableWidget *matrix, QString cnst);
    void multyplyconstantA();
    void multyplyconstantB();

    void transposeMatrixA();
    void transposeMatrixB();

    void randomizeMatrixA();
    void randomizeMatrixB();

    // QVector<QVector<double>> getMatrixFromTable(QTableWidget *table);
    // void setMatrixToTable(QTableWidget *table, const QVector<QVector<double>> &matrix);
    // double determinant(const QVector<QVector<double>> &matrix);
    // QVector<QVector<double>> inverseMatrix(const QVector<QVector<double>> &matrix);
    // void invertMatrix(QTableWidget *table);
    void invertMatrixA();
    void invertMatrixB();

    void swapMatrices();

    // void multyconstantA();
    // void multyconstantB();

    // void set_CSpinBox(int rows, int cols);
    // double set_double_value(QTableWidget *matrix, int i, int j);
    // void set_text_value(QTableWidget *matrix, int i, int j, double result);

    // double set_double_value_A(int i, int j);
    // double set_double_value_B(int i, int j);
    // void set_text_value_C(int i, int j, double result);

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
