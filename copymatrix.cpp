#include "copymatrix.h"

copymatrix::copymatrix(QObject *parent) : QObject(parent) {}

void copymatrix::copy(QTableWidget *matrix) {
    int rows = matrix->rowCount();
    int cols = matrix->columnCount();

    // Формируем данные в виде строки (разделитель - табуляция)
    QStringList lines;
    for (int row = 0; row < rows; ++row) {
        QStringList rowData;
        for (int col = 0; col < cols; ++col) {
            QTableWidgetItem* item = matrix->item(row, col);
            rowData << (item ? item->text() : "\t");
        }
        lines << rowData.join("\t");
    }

    // Объединяем строки с переносом
    QString text = lines.join("\n");

    // Копируем в буфер обмена
    QApplication::clipboard()->setText(text);
}

void copymatrix::copyThreeMatricesToClipboard(QTableWidget* table1, QTableWidget* table2, QTableWidget* table3) {
    QStringList result;

    // Функция для преобразования таблицы в строки
    auto tableToString = [&result](QTableWidget* table, const QString& label) {
        if (!table || table->rowCount() == 0 || table->columnCount() == 0) return;

        result << label;
        for (int row = 0; row < table->rowCount(); ++row) {
            QStringList rowData;
            for (int col = 0; col < table->columnCount(); ++col) {
                QTableWidgetItem* item = table->item(row, col);
                rowData << (item ? item->text() : "");
            }
            result << rowData.join("\t");
        }
        result << ""; // Пустая строка как разделитель
    };

    // Преобразуем каждую таблицу
    tableToString(table1, "#Table1");
    tableToString(table2, "#Table2");
    tableToString(table3, "#Table3");

    // Копируем в буфер обмена
    QString text = result.join("\n");
    QApplication::clipboard()->setText(text);
}
