#include "matrix_calculator.h"
#include "randomizer.h"
#include "cleaner.h"
#include "operations.h"
#include <QApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include <QSpinBox>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>
#include <QIcon>
#include <QFrame>
#include <QSize>
#include <cmath>
// #include <random>
#include <stdexcept>

using namespace std;

Matrix_Calculator::Matrix_Calculator(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Калькулятор матриц");
    setMinimumSize(900, 680);

    // глав виджет и компоновка
    QWidget* CentralWidget = new QWidget(this);
    setCentralWidget(CentralWidget);
    QVBoxLayout* MainLayout = new QVBoxLayout(CentralWidget);

    // макет матриц
    QWidget *matricesWidget = new QWidget();
    QHBoxLayout *MatricesLayout = new QHBoxLayout(matricesWidget);

    // Название продкута и линия
    QWidget *vlayoutWidget = new QWidget;
    QHBoxLayout *hlayout = new QHBoxLayout();
    QVBoxLayout *vlayout = new QVBoxLayout(vlayoutWidget);

    QLabel *iconlabel = new QLabel();
    iconlabel->setAlignment(Qt::AlignLeft);
    QIcon *icon = new QIcon(":/Icons/Icon.png");
    iconlabel->setPixmap(icon->pixmap(50, 50));
    hlayout->addWidget(iconlabel);

    QLabel *labeltext = new QLabel("Калькулятор матриц");
    QFont font = labeltext->font();
    font.setPointSize(20);
    labeltext->setFont(font);
    hlayout->addWidget(labeltext);
    QLabel *version = new QLabel("v1.0.0");
    hlayout->addWidget(version);
    hlayout->addStretch();
    vlayout->addLayout(hlayout);
    auto lineA = new QFrame;
    lineA->setFrameShape(QFrame::HLine);
    lineA->setFrameShadow(QFrame::Sunken);
    vlayout->addWidget(lineA);
    vlayout->addStretch();

    QWidget *razmerButtonWidget = new QWidget();
    QHBoxLayout *razmerHButtonLayout = new QHBoxLayout();
    QVBoxLayout *razmerVLayout = new QVBoxLayout(razmerButtonWidget);

    QPushButton* sizeButton = new QPushButton("Установить одинаковый размер X для матриц");
    QLabel *razmer = new QLabel("X :");
    razmerSpinBox = new QSpinBox();
    razmerSpinBox->setRange(1,10);
    razmerSpinBox->setValue(3);
    sizeButton->setFixedSize(500, 30);
    razmerHButtonLayout->setAlignment(Qt::AlignHCenter);
    razmerHButtonLayout->addWidget(sizeButton);
    razmerHButtonLayout->addWidget(razmer);
    razmerHButtonLayout->addWidget(razmerSpinBox);
    razmerVLayout->addLayout(razmerHButtonLayout);
    QPushButton *swapmatrixAB = new QPushButton("Поменять местами матрицы");
    swapmatrixAB->setFixedSize(594, 30);
    razmerVLayout->addWidget(swapmatrixAB, 0, Qt::AlignHCenter);
    razmerVLayout->addStretch();

    MainLayout->addWidget(vlayoutWidget);
    MainLayout->addWidget(razmerButtonWidget);

    // Матрица А
    QWidget* SizeMatrixA = new QWidget();
    QHBoxLayout* SIzeLayout = new QHBoxLayout(SizeMatrixA);

    QWidget *matrixAWidget = new QWidget();
    QVBoxLayout *matrixALayout = new QVBoxLayout(matrixAWidget);
    QLabel *matrixALabel = new QLabel("Матрица A");
    matrixATable = new QTableWidget();
    matrixALayout->addWidget(matrixALabel);
    matrixALayout->addWidget(matrixATable);

    // Кнопки для настройки размера матрицы А
    // Строки
    QLabel *StrokiALabel = new QLabel("Строки A: ");
    rowsASpinBox = new QSpinBox();
    rowsASpinBox->setRange(1, 10);
    rowsASpinBox->setValue(3);

    // Столбцы
    QLabel *StolbciALabel = new QLabel("Столбцы A: ");
    colsASpinBox = new QSpinBox();
    colsASpinBox->setRange(1, 10);
    colsASpinBox->setValue(3);

    QPushButton *CreateMatrixA = new QPushButton("Поменять размер");

    SIzeLayout->addWidget(StrokiALabel);
    SIzeLayout->addWidget(rowsASpinBox);
    SIzeLayout->addWidget(StolbciALabel);
    SIzeLayout->addWidget(colsASpinBox);
    SIzeLayout->addWidget(CreateMatrixA);
    SIzeLayout->addStretch();
    MainLayout->addWidget(SizeMatrixA);

    // Кнопки для матрицы А
    QWidget *matrixAButtonsWidget = new QWidget();
    QHBoxLayout *matrixAButtonsLayout = new QHBoxLayout(matrixAButtonsWidget);
    QPushButton *transposeAButton = new QPushButton("Транспонировать A");
    QPushButton *inverseAButton = new QPushButton("Обратная A⁻¹");
    QPushButton *multyplyConstantA = new QPushButton("Домножить на константу");
    constantA = new QSpinBox();
    constantA->setRange(0, 1000);
    constantA->setValue(1);
    matrixAButtonsLayout->addWidget(transposeAButton);
    matrixAButtonsLayout->addWidget(inverseAButton);
    matrixAButtonsLayout->addWidget(multyplyConstantA);
    matrixAButtonsLayout->addWidget(constantA);
    matrixAButtonsLayout->addStretch();
    matrixALayout->addWidget(matrixAButtonsWidget);

    // Матрица B
    QWidget* SizeMatrixB = new QWidget();
    // QHBoxLayout* SizeLayoutB = new QHBoxLayout(SizeMatrixB);

    QWidget *matrixBWidget = new QWidget();
    QVBoxLayout *matrixBLayout = new QVBoxLayout(matrixBWidget);
    QLabel *matrixBLabel = new QLabel("Матрица B");
    matrixBTable = new QTableWidget();
    matrixBLayout->addWidget(matrixBLabel);
    matrixBLayout->addWidget(matrixBTable);

    // Кнопки для настройки размера матрицы B
    // Строки
    QLabel *StrokiBLabel = new QLabel("Строки B: ");
    rowsBSpinBox = new QSpinBox();
    rowsBSpinBox->setRange(1, 10);
    rowsBSpinBox->setValue(3);

    // Столбцы
    QLabel *StolbciBLabel = new QLabel("Столбцы B: ");
    colsBSpinBox = new QSpinBox();
    colsBSpinBox->setRange(1, 10);
    colsBSpinBox->setValue(3);

    QPushButton *CreateMatrixB = new QPushButton("Поменять размер");

    SIzeLayout->addWidget(StrokiBLabel);
    SIzeLayout->addWidget(rowsBSpinBox);
    SIzeLayout->addWidget(StolbciBLabel);
    SIzeLayout->addWidget(colsBSpinBox);
    SIzeLayout->addWidget(CreateMatrixB);
    SIzeLayout->addStretch();
    MainLayout->addWidget(SizeMatrixB);

    // Кнопки для матрицы B
    QWidget *matrixBButtonsWidget = new QWidget();
    QHBoxLayout *matrixBButtonsLayout = new QHBoxLayout(matrixBButtonsWidget);
    QPushButton *transposeBButton = new QPushButton("Транспонировать B");
    QPushButton *inverseBButton = new QPushButton("Обратная B⁻¹");
    QPushButton *multyplyConstantB = new QPushButton("Домножить на константу");
    constantB = new QSpinBox();
    constantB->setRange(0, 1000);
    constantB->setValue(1);
    matrixBButtonsLayout->addWidget(transposeBButton);
    matrixBButtonsLayout->addWidget(inverseBButton);
    matrixBButtonsLayout->addWidget(multyplyConstantB);
    matrixBButtonsLayout->addWidget(constantB);
    matrixBButtonsLayout->addStretch();
    matrixBLayout->addWidget(matrixBButtonsWidget);

    MatricesLayout->addWidget(matrixAWidget);
    MatricesLayout->addWidget(matrixBWidget);
    MainLayout->addWidget(matricesWidget);

    // операции над матрицами
    QWidget* operationsWidget = new QWidget();
    QHBoxLayout* operationsLayout = new QHBoxLayout(operationsWidget);
    QLabel* operationsLabel = new QLabel("Операции: ");

    QPushButton* summButton = new QPushButton("А+B");
    QPushButton* raznButton = new QPushButton("A-B");
    QPushButton* multiplyButton = new QPushButton("A*B");
    QPushButton* clearButton = new QPushButton("Очистить матрицы");
    QPushButton* randomButton = new QPushButton("Добавить рандомные числа в матрицы A и B");


    operationsLayout->addWidget(operationsLabel);
    operationsLayout->addWidget(summButton);
    operationsLayout->addWidget(raznButton);
    operationsLayout->addWidget(multiplyButton);
    operationsLayout->addWidget(clearButton);
    operationsLayout->addWidget(randomButton);
    operationsLayout->addStretch();
    MainLayout->addWidget(operationsWidget);

    // Результирующая матрица C
    QWidget* SizeMatrixC = new QWidget();
    QWidget* matrixCWidget = new QWidget();
    QVBoxLayout* matrixCLayout = new QVBoxLayout(matrixCWidget);
    QLabel* matrixCLabel = new QLabel("Результирующая матрица");
    matrixCTable = new QTableWidget();
    matrixCLayout->addWidget(matrixCLabel);
    matrixCLayout->addWidget(matrixCTable);

    // Кнопки для настройки размера матрицы С
    // Строки
    rowsCSpinBox = new QSpinBox();
    rowsCSpinBox->setValue(3);

    // Столбцы
    colsCSpinBox = new QSpinBox();
    colsCSpinBox->setValue(3);


    MainLayout->addWidget(SizeMatrixC);

    MainLayout->addWidget(matrixCWidget);



    // соединение сигналов и слотов
    //...
    connect(CreateMatrixA, &QPushButton::clicked, this, &Matrix_Calculator::createMatrixA);
    connect(CreateMatrixB, &QPushButton::clicked, this, &Matrix_Calculator::createMatrixB);
    connect(summButton, &QPushButton::clicked, this, &Matrix_Calculator::addMatrices);
    connect(raznButton, &QPushButton::clicked, this, &Matrix_Calculator::subtractMatrices);
    connect(multiplyButton, &QPushButton::clicked, this, &Matrix_Calculator::multyplyMatrices);
    connect(transposeAButton, &QPushButton::clicked, this, &Matrix_Calculator::transposeMatrixA);
    connect(transposeBButton, &QPushButton::clicked, this, &Matrix_Calculator::transposeMatrixB);
    connect(clearButton, &QPushButton::clicked, this, &Matrix_Calculator::clearMatrixA);
    connect(clearButton, &QPushButton::clicked, this, &Matrix_Calculator::clearMatrixB);
    connect(clearButton, &QPushButton::clicked, this, &Matrix_Calculator::clearMatrixC);

    connect(randomButton, &QPushButton::clicked, this, &Matrix_Calculator::randomizeMatrices);

    connect(sizeButton, &QPushButton::clicked, this, &Matrix_Calculator::createMatricesAB);
    connect(inverseAButton, &QPushButton::clicked, this, &Matrix_Calculator::invertMatrixA);
    connect(inverseBButton, &QPushButton::clicked, this, &Matrix_Calculator::invertMatrixB);
    connect(swapmatrixAB, &QPushButton::clicked, this, &Matrix_Calculator::swapMatrices);

    connect(multyplyConstantB, &QPushButton::clicked, this, &Matrix_Calculator::multyconstantB);
    connect(multyplyConstantA, &QPushButton::clicked, this, &Matrix_Calculator::multyconstantA);


    createMatrices();

}

void Matrix_Calculator::createMatrices() {
    createMatrixA();
    createMatrixB();
    createMatrixC();
}
void Matrix_Calculator::createMatricesAB() {
    int rows = razmerSpinBox->value();
    int cols = razmerSpinBox->value();

    // настройка
    matrixATable->setRowCount(rows);
    matrixATable->setColumnCount(cols);
    matrixBTable->setRowCount(rows);
    matrixBTable->setColumnCount(cols);

    for (int i {}; i < rows; i++) {
        for (int j {}; j < cols; j++) {
            if (!matrixATable->item(i, j)) {
                QTableWidgetItem *item = new QTableWidgetItem("0");
                matrixATable->setItem(i, j, item);
            }
            if (!matrixBTable->item(i, j)) {
                QTableWidgetItem *item = new QTableWidgetItem("0");
                matrixBTable->setItem(i, j, item);
            }
        }
    }

    matrixATable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixATable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixBTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixBTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Matrix_Calculator::createMatrixA() {

    int rows = rowsASpinBox->value();
    int cols = colsASpinBox->value();

    // настройка
    matrixATable->setRowCount(rows);
    matrixATable->setColumnCount(cols);

    for (int i {}; i < rows; i++) {
        for (int j {}; j < cols; j++) {
            if (!matrixATable->item(i, j)) {
                QTableWidgetItem *item = new QTableWidgetItem("0");
                matrixATable->setItem(i, j, item);
            }
        }
    }

    matrixATable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixATable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void Matrix_Calculator::createMatrixB() {
    int rows = rowsBSpinBox->value();
    int cols = colsBSpinBox->value();

    matrixBTable->setRowCount(rows);
    matrixBTable->setColumnCount(cols);

    for (int i {}; i < rows; i++) {
        for (int j {}; j < cols; j++) {
            if (!matrixBTable->item(i, j)) {
                QTableWidgetItem *item = new QTableWidgetItem("0");
                matrixBTable->setItem(i, j, item);
            }
        }
    }

    matrixBTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixBTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void Matrix_Calculator::createMatrixC()
{
    int rows = rowsCSpinBox->value();
    int cols = colsCSpinBox->value();

    matrixCTable->setRowCount(rows);
    matrixCTable->setColumnCount(cols);

    for (int i {}; i < rows; i++) {
        for (int j {}; j < cols; j++) {
            if (!matrixCTable->item(i, j)) {
                QTableWidgetItem *item = new QTableWidgetItem("0");
                matrixCTable->setItem(i, j, item);
            }
        }
    }

    matrixCTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixCTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void Matrix_Calculator::addMatrices()
{
    // int rowsA = matrixATable->rowCount();
    // int colsA = matrixATable->columnCount();
    // int rowsB = matrixBTable->rowCount();
    // int colsB = matrixBTable->columnCount();

    // if (rowsA != rowsB || colsA != colsB) {
    //     QMessageBox::warning(this, "Ошибка", "Размеры матриц должны совпадать!");
    //     return;
    // }

    // rowsCSpinBox->setValue(rowsA);
    // colsCSpinBox->setValue(colsB);
    // createMatrixC();

    // for (int i {}; i < rowsA; i++) {
    //     for (int j {}; j < colsA; j++) {
    //         double valueA = matrixATable->item(i, j)->text().toDouble();
    //         double valueB = matrixBTable->item(i, j)->text().toDouble();
    //         double result = valueA + valueB;
    //         matrixCTable->item(i, j)->setText(QString::number(result));
    //     }
    // }
    Operations op;
    op.addMatrices(matrixATable, matrixBTable);
}
void Matrix_Calculator::subtractMatrices() {
    // int rowsA = matrixATable->rowCount();
    // int colsA = matrixATable->columnCount();
    // int rowsB = matrixBTable->rowCount();
    // int colsB = matrixBTable->columnCount();

    // if (rowsA != rowsB || colsA != colsB) {
    //     QMessageBox::warning(this, "Ошибка", "Размеры матриц должны совпадать!");
    //     return;
    // }

    // rowsCSpinBox->setValue(rowsA);
    // colsCSpinBox->setValue(colsB);
    // createMatrixC();

    // for (int i {}; i < rowsA; i++) {
    //     for (int j {}; j < colsA; j++) {
    //         double valueA = matrixATable->item(i, j)->text().toDouble();
    //         double valueB = matrixBTable->item(i, j)->text().toDouble();
    //         double result = valueA - valueB;
    //         matrixCTable->item(i, j)->setText(QString::number(result));
    //     }
    // }
    Operations op;
    op.subtractMatrices(matrixATable, matrixBTable);
}

void Matrix_Calculator::multyplyMatrices() {
    // int rowsA = matrixATable->rowCount();
    // int colsA = matrixATable->columnCount();
    // int rowsB = matrixBTable->rowCount();
    // int colsB = matrixBTable->columnCount();

    // if (colsA != rowsB) {
    //     QMessageBox::warning(this, "Ошибка", "Кол-во строк матрицы A должно совпадать с кол-во столбцов матрицы B");
    //     return;
    // }

    // rowsCSpinBox->setValue(rowsA);
    // colsCSpinBox->setValue(colsB);
    // createMatrixC();

    // for (int i {}; i < rowsA; i++) {
    //     for (int j {}; j < colsB; j++) {
    //         double result = 0;
    //         for (int x{}; x < colsA; x++) {
    //             double valueA = matrixATable->item(i, x)->text().toDouble();
    //             double valueB = matrixBTable->item(x, j)->text().toDouble();
    //             result = result + (valueA*valueB);
    //         }
    //         matrixCTable->item(i, j)->setText(QString::number(result));
    //     }
    // }
    Operations op;
    op.multyplyMatrices(matrixATable, matrixBTable);
}

void Matrix_Calculator::clearMatrices(QTableWidget* matrix) {
    Cleaner clean;
    clean.clearMatrices(matrix);
}

void Matrix_Calculator::clearMatrixA() {
    Cleaner clean;
    clean.clearMatrices(matrixATable);
}
void Matrix_Calculator::clearMatrixB() {
    Cleaner clean;
    clean.clearMatrices(matrixBTable);
}
void Matrix_Calculator::clearMatrixC() {
    Cleaner clean;
    clean.clearMatrices(matrixCTable);
}

void Matrix_Calculator::randomizeMatrices() {
    Randomizer random;
    random.randomizeMatrices(matrixATable);
    random.randomizeMatrices(matrixBTable);
}

void Matrix_Calculator::randomizeMatrixA() {
    Randomizer random;
    random.randomizeMatrices(matrixATable);
}

void Matrix_Calculator::randomizeMatrixB() {
    Randomizer random;
    random.randomizeMatrices(matrixBTable);
}

void Matrix_Calculator::transposeMatrix(QTableWidget *matrix) {
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

void Matrix_Calculator::transposeMatrixA() {
    transposeMatrix(matrixATable);
}
void Matrix_Calculator::transposeMatrixB() {
    transposeMatrix(matrixBTable);
}

QVector<QVector<double>> Matrix_Calculator::getMatrixFromTable(QTableWidget *table)
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

void Matrix_Calculator::setMatrixToTable(QTableWidget *table, const QVector<QVector<double>> &matrix)
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
            table->item(i, j)->setText(QString::number(matrix[i][j], 'f', 4));
        }
    }
}

double Matrix_Calculator::determinant(const QVector<QVector<double>> &matrix)
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

QVector<QVector<double>> Matrix_Calculator::inverseMatrix(const QVector<QVector<double>> &matrix)
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

void Matrix_Calculator::invertMatrix(QTableWidget *table)
{
    int rows = table->rowCount();
    int cols = table->columnCount();


    if (rows != cols) {
        QMessageBox::warning(this, "Ошибка", "Обратная матрица существует только для квадратных матриц");
        return;
    }


    QVector<QVector<double>> matrix = getMatrixFromTable(table);

    try {

        QVector<QVector<double>> inverse = inverseMatrix(matrix);


        setMatrixToTable(table, inverse);
    }
    catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void Matrix_Calculator::invertMatrixA()
{
    invertMatrix(matrixATable);
}

void Matrix_Calculator::invertMatrixB()
{
    invertMatrix(matrixBTable);
}
void Matrix_Calculator::swapMatrices() {
    int rowsA = matrixATable->rowCount();
    int colsA = matrixATable->columnCount();
    int rowsB = matrixBTable->rowCount();
    int colsB = matrixBTable->columnCount();

    QVector<QVector<double>> tempA(rowsA, QVector<double>(colsA));
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            tempA[i][j] = matrixATable->item(i, j)->text().toDouble();
        }
    }

    QVector<QVector<double>> tempB(rowsB, QVector<double>(colsB));
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            tempB[i][j] = matrixBTable->item(i, j)->text().toDouble();
        }
    }

    rowsASpinBox->setValue(rowsB);
    colsASpinBox->setValue(colsB);
    rowsBSpinBox->setValue(rowsA);
    colsBSpinBox->setValue(colsA);


    createMatrixA();
    createMatrixB();

    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            matrixATable->item(i, j)->setText(QString::number(tempB[i][j]));
        }
    }

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            matrixBTable->item(i, j)->setText(QString::number(tempA[i][j]));
        }
    }
}
void Matrix_Calculator::multyconstantA()
{
    // int rows = matrixATable->rowCount();
    // int cols = matrixATable->columnCount();
    // double cnst = constantA->value();

    // for(int i{}; i < rows; i++) {
    //     for (int j{}; j < cols; j++) {
    //         double value = matrixATable->item(i, j)->text().toDouble();
    //         double result = cnst*value;
    //         matrixATable->item(i, j)->setText(QString::number(result));
    //     }
    // }
    Operations op;
    op.multyplyconstant(matrixATable, constantA->value());
}

void Matrix_Calculator::multyconstantB() {
    // int rows = matrixBTable->rowCount();
    // int cols = matrixBTable->columnCount();
    // double cnst = constantB->value();

    // for(int i{}; i < rows; i++) {
    //     for (int j{}; j < cols; j++) {
    //         double value = matrixBTable->item(i, j)->text().toDouble();
    //         double result = cnst*value;
    //         matrixBTable->item(i, j)->setText(QString::number(result));
    //     }
    // }
    Operations op;
    op.multyplyconstant(matrixBTable, constantB->value());
}

void Matrix_Calculator::set_CSpinBox(int rows, int cols) {
    rowsCSpinBox->setValue(rows);
    colsCSpinBox->setValue(cols);
}

double Matrix_Calculator::set_double_value(QTableWidget *matrix, int i, int j) {return matrix->item(i, j)->text().toDouble();}
void Matrix_Calculator::set_text_value(QTableWidget *matrix, int i, int j, double result) {matrix->item(i, j)->setText(QString::number(result)); }

double Matrix_Calculator::set_double_value_A(int i, int j) {
    return set_double_value(matrixATable, i, j);
}
double Matrix_Calculator::set_double_value_B(int i, int j) {
    return set_double_value(matrixBTable, i, j);
}
void Matrix_Calculator::set_text_value_C(int i, int j, double result) {
    set_text_value(matrixCTable, i, j, result);
}
