#ifndef MATRIX_H
#define MATRIX_H


#include <QObject>
#include <QSpinBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>

class matrix : public QObject
{
    Q_OBJECT
public:
    matrix(QObject* parent = nullptr);
public slots:
    void create3Matrices(QTableWidget* matrix1, QTableWidget* matrix2, QTableWidget* matrix3, int rows, int cols);
    void create2Matrices(QTableWidget* matrix1, QTableWidget* matrix2, int rows, int cols);
    void createMatrix(QTableWidget* matrix, int rows, int cols);

private:
    QSpinBox* rowsSpinBox;
    QSpinBox* colsSpinBox;
    QLineEdit* constant;
    QSpinBox* razmerSpinBox;
    QTableWidget* matrixTable;

};

#endif // MATRIX_H
