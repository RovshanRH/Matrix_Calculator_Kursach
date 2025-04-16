#include "insertmatrix.h"
#include <QApplication>
#include <QClipboard>
#include <QStringList>

insertmatrix::insertmatrix(QObject *parent) : QObject(parent) {}

void insertmatrix::insert(QTableWidget *matrix) {
    QString text = QApplication::clipboard()->text();
    if (text.isEmpty()) return;

    // Разделяем текст на строки
    QStringList lines = text.split("\n", Qt::SkipEmptyParts);
    if (lines.isEmpty()) return;

    // Функция для определения лучшего разделителя
    auto findBestDelimiter = [](const QString &line) {
        QStringList delimiters = {"\t", ",", " ", ";"};
        QString bestDelimiter = "\t";
        int maxColumns = 0;

        for (const QString &delimiter : delimiters) {
            QStringList parts = line.split(delimiter, Qt::SkipEmptyParts);
            if (parts.size() > maxColumns) {
                maxColumns = parts.size();
                bestDelimiter = delimiter;
            }
        }
        return bestDelimiter;
    };

    // Определяем разделитель по первой строке
    QString delimiter = findBestDelimiter(lines[0]);
    QStringList firstRow = lines[0].split(delimiter, Qt::SkipEmptyParts);
    int cols = firstRow.size();
    int rows = lines.size();

    // Устанавливаем размеры таблицы
    matrix->clear();
    matrix->setRowCount(rows);
    matrix->setColumnCount(cols);

    // Заполняем таблицу данными
    for (int row = 0; row < rows; ++row) {
        QStringList rowData = lines[row].split(delimiter, Qt::SkipEmptyParts);
        for (int col = 0; col < cols && col < rowData.size(); ++col) {
            matrix->setItem(row, col, new QTableWidgetItem(rowData[col]));
        }
    }
}

void insertmatrix::insertThreeMatrices(QTableWidget *table1, QTableWidget *table2, QTableWidget *table3) {
    QString text = QApplication::clipboard()->text();
    if (text.isEmpty()) return;

    QStringList lines = text.split("\n");
    if (lines.isEmpty()) return;

    // Функция для вставки одной таблицы с динамическим разделителем
    auto insertTable = [](QTableWidget *table, const QStringList &tableLines) {
        if (!table || tableLines.isEmpty()) return;

        // Функция для определения лучшего разделителя
        auto findBestDelimiter = [](const QString &line) {
            QStringList delimiters = {"\t", ", ", " ", ";"};
            QString bestDelimiter = "\t";
            int maxColumns = 0;

            for (const QString &delimiter : delimiters) {
                QStringList parts = line.split(delimiter, Qt::SkipEmptyParts);
                if (parts.size() > maxColumns) {
                    maxColumns = parts.size();
                    bestDelimiter = delimiter;
                }
            }
            return bestDelimiter;
        };

        // Определяем разделитель по первой строке
        QString delimiter = findBestDelimiter(tableLines[0]);
        QStringList firstRow = tableLines[0].split(delimiter, Qt::SkipEmptyParts);
        int cols = firstRow.size();
        int rows = tableLines.size();

        // Устанавливаем размеры таблицы
        table->clear();
        table->setRowCount(rows);
        table->setColumnCount(cols);

        // Заполняем таблицу
        for (int row = 0; row < rows; ++row) {
            QStringList rowData = tableLines[row].split(delimiter, Qt::SkipEmptyParts);
            for (int col = 0; col < cols && col < rowData.size(); ++col) {
                table->setItem(row, col, new QTableWidgetItem(rowData[col]));
            }
        }
    };

    // Переменные для накопления строк каждой таблицы
    QStringList table1Lines, table2Lines, table3Lines;
    QStringList *currentLines = nullptr;

    // Разбираем строки
    for (const QString &line : std::as_const(lines)) {
        if (line.trimmed().isEmpty()) {
            continue; // Пропускаем пустые строки
        }
        if (line == "#Table1") {
            currentLines = &table1Lines;
            continue;
        }
        if (line == "#Table2") {
            currentLines = &table2Lines;
            continue;
        }
        if (line == "#Table3") {
            currentLines = &table3Lines;
            continue;
        }
        if (currentLines) {
            currentLines->append(line);
        }
    }

    // Вставляем данные в таблицы
    insertTable(table1, table1Lines);
    insertTable(table2, table2Lines);
    insertTable(table3, table3Lines);
}


