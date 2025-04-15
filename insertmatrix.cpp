#include "insertmatrix.h"

insertmatrix::insertmatrix(QObject *parent) : QObject(parent) {}

void insertmatrix::insert(QTableWidget *matrix) {
    QString text = QApplication::clipboard()->text();
    if (text.isEmpty()) return;

    // Разделяем текст на строки
    QStringList lines = text.split("\n", Qt::SkipEmptyParts);
    if (lines.isEmpty()) return;

    // Определяем количество столбцов по первой строке (разделитель - табуляция)
    QStringList firstRow = lines[0].split("\t", Qt::SkipEmptyParts);
    int cols = firstRow.size();
    int rows = lines.size();

    // Устанавливаем размеры таблицы
    matrix->clear();
    matrix->setRowCount(rows);
    matrix->setColumnCount(cols);

    // Заполняем таблицу данными
    for (int row = 0; row < rows; ++row) {
        QStringList rowData = lines[row].split("\t", Qt::SkipEmptyParts);
        for (int col = 0; col < cols && col < rowData.size(); ++col) {
            matrix->setItem(row, col, new QTableWidgetItem(rowData[col]));
        }
    }
}
