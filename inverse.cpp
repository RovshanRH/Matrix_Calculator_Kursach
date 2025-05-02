#include "inverse.h"
#include <string>
#include <cmath>

inverse::inverse(QObject *parent) : QObject(parent) {}

QVector<QVector<double>> inverse::getMatrixFromTable(QTableWidget *table)
{
    int rows = table->rowCount();
    int cols = table->columnCount();

    QVector<QVector<double>> matrix(rows, QVector<double>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = table->item(i, j)->text().toDouble();
        }
    }

    return matrix;
}


void setMatrixToTable(QTableWidget *table, const QVector<QVector<double>> &matrix)
{
    int rows = matrix.size();
    int cols = rows > 0 ? matrix[0].size() : 0;

    table->setRowCount(rows);
    table->setColumnCount(cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!table->item(i, j)) {
                QTableWidgetItem *item = new QTableWidgetItem();
                table->setItem(i, j, item);
            }

            double value = matrix[i][j];
            double integer_part;
            QString text;
            std::string s = std::to_string(std::modf(value, &integer_part));

            // Для очень маленьких значений, близких к нулю
            if (std::abs(value) < 1e-10) {
                text = "0";
            }
            // Для почти целых чисел
            else if ((std::abs(value - round(value)) < 1e-10) || (s.substr(0, 3) == "000" || s.substr(0, 3) == "999")) {
                text = QString::number(static_cast<int>(round(value)));
            }
            // Для обычных дробных чисел
            else {
                text = QString::number(value, 'g', 3);

                if (text.length() > 10) {
                    text = QString::number(value, 'g', 3);
                }
            }

            table->item(i, j)->setText(text);
        }
    }
}

double determinant(const QVector<QVector<double>> &matrix)
{
    int n = matrix.size();

    if (n == 1) {
        return matrix[0][0];
    }

    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    QVector<QVector<double>> mat = matrix;
    double det = 1.0;

    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int j = i + 1; j < n; j++) {
            if (std::abs(mat[j][i]) > std::abs(mat[maxRow][i])) {
                maxRow = j;
            }
        }

        if (std::abs(mat[maxRow][i]) < 1e-10) {
            return 0.0;
        }

        if (maxRow != i) {
            for (int j = i; j < n; j++) {
                std::swap(mat[i][j], mat[maxRow][j]);
            }
            det *= -1.0;
        }

        double pivot = mat[i][i];
        det *= pivot;

        for (int j = i; j < n; j++) {
            mat[i][j] /= pivot;
        }

        for (int j = i + 1; j < n; j++) {
            double factor = mat[j][i];
            for (int k = i; k < n; k++) {
                mat[j][k] -= factor * mat[i][k];
            }
        }
    }

    return det;
}

QVector<QVector<double>> inverseMatrix(const QVector<QVector<double>> &matrix)
{
    int n = matrix.size();

    QVector<QVector<double>> adj(n, QVector<double>(n, 0));

    if (n == 1) {
        adj[0][0] = 1.0;
        return adj;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            QVector<QVector<double>> minor(n - 1, QVector<double>(n - 1, 0));
            for (int r = 0, row = 0; r < n; r++) {
                if (r == i) continue;
                for (int c = 0, col = 0; c < n; c++) {
                    if (c == j) continue;
                    minor[row][col] = matrix[r][c];
                    col++;
                }
                row++;
            }


            double minorDet = determinant(minor);


            adj[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * minorDet;
        }
    }


    double det = determinant(matrix);

    if (std::abs(det) < 1e-10) {
        throw std::runtime_error("Матрица вырожденная, обратной не существует!");
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] /= det;
        }
    }

    return adj;
}

void inverse::invertMatrix(QTableWidget *table)
{
    int rows = table->rowCount();
    int cols = table->columnCount();


    if (rows != cols) {
        QMessageBox::warning(nullptr, "Ошибка", "Обратная матрица существует только для квадратных матриц");
        return;
    }


    QVector<QVector<double>> matrix = getMatrixFromTable(table);

    try {

        QVector<QVector<double>> inverse = inverseMatrix(matrix);


        setMatrixToTable(table, inverse);
    }
    catch (const std::exception &e) {
        QMessageBox::warning(nullptr, "Ошибка", e.what());
    }
}
