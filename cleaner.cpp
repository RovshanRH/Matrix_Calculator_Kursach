#include "cleaner.h"

Cleaner::Cleaner(QObject *parent) : QObject(parent) {}

void Cleaner::clearMatrices(QTableWidget* matrix) {
    int rows = matrix->rowCount();
    int cols = matrix->columnCount();

    for (int i{}; i < rows; i++) {
        for (int j{}; j < cols; j++) {
            matrix->item(i, j)->setText(QString::number(0));
        }
    }
}

void Cleaner::clearMatrixA() {}
void Cleaner::clearMatrixB() {}
void Cleaner::clearMatrixC() {}
