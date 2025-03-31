#include "operations.h"
#include "stabilizingcsize.h"

Operations::Operations(QWidget *parent) : stabilizingCsize(parent) {}

void Operations::addMatrices(QTableWidget *matrix1, QTableWidget *matrix2)
{
    int rowsA = matrix1->rowCount();
    int colsA = matrix1->columnCount();
    int rowsB = matrix2->rowCount();
    int colsB = matrix2->columnCount();

    if (rowsA != rowsB || colsA != colsB) {
        QMessageBox::warning(this, "Ошибка", "Размеры матриц должны совпадать!");
        return;
    }
    this->stabilizeSum(rowsA, colsA);
}
void Operations::multyplyMatrices(QTableWidget *matrix1, QTableWidget *matrix2) {
    int rowsA = matrix1->rowCount();
    int colsA = matrix1->columnCount();
    int rowsB = matrix2->rowCount();
    int colsB = matrix2->columnCount();

    if (colsA != rowsB) {
        QMessageBox::warning(this, "Ошибка", "Кол-во строк матрицы A должно совпадать с кол-во столбцов матрицы B");
        return;
    }

    this->stabilizeUmno(rowsA, colsB);
}

void Operations::subtractMatrices(QTableWidget *matrix1, QTableWidget *matrix2) {
    int rowsA = matrix1->rowCount();
    int colsA = matrix1->columnCount();
    int rowsB = matrix2->rowCount();
    int colsB = matrix2->columnCount();

    if (rowsA != rowsB || colsA != colsB) {
        QMessageBox::warning(this, "Ошибка", "Кол-во строк матрицы A должно совпадать с кол-во столбцов матрицы B");
        return;
    }

    this->stabilizeSub(rowsA, colsA);
}

void Operations::multyplyconstant(QTableWidget *matrix, double cnst) {
    int rows = matrix->rowCount();
    int cols = matrix->columnCount();
    // double cnst = constant->value();

    for(int i{}; i < rows; i++) {
        for (int j{}; j < cols; j++) {
            double value = matrix->item(i, j)->text().toDouble();
            double result = cnst*value;
            matrix->item(i, j)->setText(QString::number(result));
        }
    }
}

