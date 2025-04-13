#include "operations.h"

Operations::Operations(QObject *parent) : QObject(parent) {}

void Operations::addMatrices(QTableWidget *matrix1, QTableWidget *matrix2, QTableWidget *matrix3)
{
    int rowsA = matrix1->rowCount();
    int colsA = matrix1->columnCount();
    int rowsB = matrix2->rowCount();
    int colsB = matrix2->columnCount();

    if (rowsA != rowsB || colsA != colsB) {
        QMessageBox::warning(nullptr, "Ошибка", "Размеры матриц должны совпадать!");
        return;
    }
    // this->stabilizeSum(rowsA, colsA);

    for (int i {}; i < rowsA; i++) {
        for (int j {}; j < colsA; j++) {
            double valueA = matrix1->item(i, j)->text().toDouble();
            double valueB = matrix2->item(i, j)->text().toDouble();
            double result = valueA + valueB;
            // matrixCTable->item(i, j)->setText(QString::number(result));
            matrix3->item(i, j)->setText(QString::number(result));
        }
    }
}
void Operations::multyplyMatrices(QTableWidget *matrix1, QTableWidget *matrix2, QTableWidget *matrix3) {
    int rowsA = matrix1->rowCount();
    int colsA = matrix1->columnCount();
    int rowsB = matrix2->rowCount();
    int colsB = matrix2->columnCount();

    if (colsA != rowsB) {
        QMessageBox::warning(nullptr, "Ошибка", "Кол-во строк матрицы A должно совпадать с кол-во столбцов матрицы B");
        return;
    }

    // this->stabilizeUmno(rowsA, colsB);

    for (int i {}; i < rowsA; i++) {
        for (int j {}; j < colsB; j++) {
            double result = 0;
            for (int x{}; x < colsA; x++) {
                double valueA = matrix1->item(i, x)->text().toDouble();
                double valueB = matrix2->item(x, j)->text().toDouble();
                result = result + (valueA*valueB);
            }
            matrix3->item(i, j)->setText(QString::number(result));
        }
    }
}

void Operations::subtractMatrices(QTableWidget *matrix1, QTableWidget *matrix2, QTableWidget *matrix3) {
    int rowsA = matrix1->rowCount();
    int colsA = matrix1->columnCount();
    int rowsB = matrix2->rowCount();
    int colsB = matrix2->columnCount();

    if (rowsA != rowsB || colsA != colsB) {
        QMessageBox::warning(nullptr, "Ошибка", "Кол-во строк матрицы A должно совпадать с кол-во столбцов матрицы B");
        return;
    }

    // this->stabilizeSub(rowsA, colsA);

    for (int i {}; i < rowsA; i++) {
        for (int j {}; j < colsA; j++) {
            double valueA = matrix1->item(i, j)->text().toDouble();
            double valueB = matrix2->item(i, j)->text().toDouble();
            double result = valueA - valueB;
            // matrixCTable->item(i, j)->setText(QString::number(result));
            matrix3->item(i, j)->setText(QString::number(result));
        }
    }
}

void Operations::multyplyconstant(QTableWidget *matrix, double cnst) {
    int rows = matrix->rowCount();
    int cols = matrix->columnCount();

    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            QTableWidgetItem *item = matrix->item(i, j);
            if (!item) {
                item = new QTableWidgetItem("0");
                matrix->setItem(i, j, item);
            }

            bool ok;
            double value = item->text().toDouble(&ok);
            if (!ok) {
                // Handle case when cell doesn't contain a valid number
                value = 0.0;
            }

            double result = value * cnst;

            // Format with precision to avoid too many decimal places
            matrix->item(i, j)->setText(QString::number(result, 'g', 10));
        }
    }
}

QVector<QVector<double>> settemp(int rows, int cols, QTableWidget *matrix) {
    QVector<QVector<double>> temp(rows, QVector<double>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            temp[i][j] = matrix->item(i, j)->text().toDouble();
        }
    }
    return temp;
}

QVector<QVector<double>> Operations::settempA(int rows, int cols, QTableWidget *matrix){return settemp(rows, cols, matrix);}
QVector<QVector<double>> Operations::settempB(int rows, int cols, QTableWidget *matrix){return settemp(rows, cols, matrix);}

void Operations::swapMatrices(QTableWidget *matrix1, QTableWidget *matrix2, QVector<QVector<double>> tempB, QVector<QVector<double>> tempA) {
    int rowsA = matrix1->rowCount();
    int colsA = matrix1->columnCount();
    int rowsB = matrix2->rowCount();
    int colsB = matrix2->columnCount();

    // QVector<QVector<double>> tempA(rowsA, QVector<double>(colsA));
    // for (int i = 0; i < rowsA; ++i) {
    //     for (int j = 0; j < colsA; ++j) {
    //         tempA[i][j] = matrix1->item(i, j)->text().toDouble();
    //     }
    // }

    // QVector<QVector<double>> tempB(rowsB, QVector<double>(colsB));
    // for (int i = 0; i < rowsB; ++i) {
    //     for (int j = 0; j < colsB; ++j) {
    //         tempB[i][j] = matrix2->item(i, j)->text().toDouble();
    //     }
    // }

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            matrix1->item(i, j)->setText(QString::number(tempB[i][j]));
        }
    }

    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            matrix2->item(i, j)->setText(QString::number(tempA[i][j]));
        }
    }
}

void Operations::transposeMatrix(QTableWidget *matrix) {
    int rows = matrix->rowCount();
    int cols = matrix->columnCount();

    QVector<QVector<double>> data(rows, QVector<double>(cols, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = matrix->item(i, j)->text().toDouble();
        }
    }

    matrix->setRowCount(cols);
    matrix->setColumnCount(rows);

    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            if (!matrix->item(i, j)) {
                QTableWidgetItem *item = new QTableWidgetItem();
                matrix->setItem(i, j, item);
            }
            matrix->item(i, j)->setText(QString::number(data[j][i]));
        }
    }
}

int Operations::rowsA_getter(QTableWidget *matrix) {return matrix->rowCount();}
int Operations::colsB_getter(QTableWidget *matrix) {return matrix->columnCount();}
int Operations::rowsB_getter(QTableWidget *matrix) {return matrix->rowCount();}
int Operations::colsA_getter(QTableWidget *matrix) {return matrix->columnCount();}
