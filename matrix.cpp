#include "matrix.h"

matrix::matrix(QObject* parent) : QObject(parent) {}

void matrix::createMatrix(QTableWidget* matrix, int rows, int cols) {
    // настройка
    matrix->setRowCount(rows);
    matrix->setColumnCount(cols);

    for (int i {}; i < rows; i++) {
        for (int j {}; j < cols; j++) {
            if (!matrix->item(i, j)) {
                QTableWidgetItem *item = new QTableWidgetItem("0");
                matrix->setItem(i, j, item);
            }
        }
    }

    matrix->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrix->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void matrix::create3Matrices(QTableWidget* matrix1, QTableWidget* matrix2, QTableWidget* matrix3, int rows, int cols) {
    createMatrix(matrix1, rows, cols);
    createMatrix(matrix2, rows, cols);
    createMatrix(matrix3, rows, cols);
}

void matrix::create2Matrices(QTableWidget* matrix1, QTableWidget* matrix2, int rows, int cols) {
    createMatrix(matrix1, rows, cols);
    createMatrix(matrix2, rows, cols);
}





