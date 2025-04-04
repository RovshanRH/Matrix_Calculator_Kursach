#include "matrix_calculator.h"
#include "randomizer.h"
#include "cleaner.h"
#include "operations.h"
#include "inverse.h"
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
#include <QLineEdit>
#include <QDoubleValidator>
#include <cmath>

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

    // constantA = new QLineEdit();
    // constantA->setRange(0, 1000);
    // constantA->setValue(1);

    // QLineEdit *constantA = new QLineEdit();
    // QDoubleValidator *validatorA = new QDoubleValidator(0.0, 1000.0, 1, constantA);
    // constantA->setValidator(validatorA);

    QLineEdit *constantA = new QLineEdit();
    QDoubleValidator *validatorA = new QDoubleValidator(-1000.0, 1000.0, 2, constantA);
    constantA->setValidator(validatorA);
    constantA->setPlaceholderText("Введите константу (например, 2.5)");
    constantA->setText("1.0");
    matrixAButtonsLayout->addWidget(constantA);

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
    // constantB = new QLineEdit();
    // constantB->setRange(0, 1000);
    // constantB->setValue(1);

    // QLineEdit *constantB = new QLineEdit();
    // QDoubleValidator *validatorB = new QDoubleValidator(0.0, 1000.0, 1, constantB);
    // constantA->setValidator(validatorB);

    QLineEdit *constantB = new QLineEdit();
    QDoubleValidator *validatorB = new QDoubleValidator(-1000.0, 1000.0, 2, constantB);
    constantB->setValidator(validatorB);
    constantB->setPlaceholderText("Введите константу (например, 2.5)");
    constantB->setText("1.0");
    matrixBButtonsLayout->addWidget(constantB);

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

    connect(randomButton, &QPushButton::clicked, this, &Matrix_Calculator::randomizeMatrixA);
    connect(randomButton, &QPushButton::clicked, this, &Matrix_Calculator::randomizeMatrixB);


    connect(sizeButton, &QPushButton::clicked, this, &Matrix_Calculator::createMatricesAB);
    connect(inverseAButton, &QPushButton::clicked, this, &Matrix_Calculator::invertMatrixA);
    connect(inverseBButton, &QPushButton::clicked, this, &Matrix_Calculator::invertMatrixB);
    connect(swapmatrixAB, &QPushButton::clicked, this, &Matrix_Calculator::swapMatrices);

    connect(multyplyConstantA, &QPushButton::clicked, this, &Matrix_Calculator::multyplyconstantA);
    connect(multyplyConstantB, &QPushButton::clicked, this, &Matrix_Calculator::multyplyconstantB);


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

void Matrix_Calculator::randomizeMatrixA() {
    Randomizer random;
    random.randomizeMatrices(matrixATable);
}

void Matrix_Calculator::randomizeMatrixB() {
    Randomizer random;
    random.randomizeMatrices(matrixBTable);
}

void Matrix_Calculator::transposeMatrixA() {
    Operations op;
    op.transposeMatrix(matrixATable);
}
void Matrix_Calculator::transposeMatrixB() {
    Operations op;
    op.transposeMatrix(matrixBTable);
}


void Matrix_Calculator::invertMatrixA()
{
    inverse invert;
    invert.invertMatrix(matrixATable);
}

void Matrix_Calculator::invertMatrixB()
{
    inverse invert;
    invert.invertMatrix(matrixBTable);
}
void Matrix_Calculator::swapMatrices() {
    Operations op;

    QVector<QVector<double>> tempA = op.settempA(op.rowsA_getter(matrixATable), op.colsA_getter(matrixATable), matrixATable);
    QVector<QVector<double>> tempB = op.settempB(op.rowsB_getter(matrixBTable), op.colsB_getter(matrixBTable), matrixBTable);

    rowsASpinBox->setValue(op.rowsA_getter(matrixATable));
    colsASpinBox->setValue(op.colsA_getter(matrixATable));
    rowsBSpinBox->setValue(op.rowsB_getter(matrixBTable));
    colsBSpinBox->setValue(op.colsB_getter(matrixBTable));

    createMatrixA();
    createMatrixB();

    op.swapMatrices(matrixATable, matrixBTable, tempB, tempA);


}

void Matrix_Calculator::addMatrices() {
    Operations op;
    rowsCSpinBox->setValue(op.rowsA_getter(matrixATable));
    colsCSpinBox->setValue(op.colsB_getter(matrixBTable));
    createMatrixC();
    op.addMatrices(matrixATable, matrixBTable, matrixCTable);
}


void Matrix_Calculator::subtractMatrices() {

    Operations op;
    rowsCSpinBox->setValue(op.rowsA_getter(matrixATable));
    colsCSpinBox->setValue(op.colsB_getter(matrixBTable));
    createMatrixC();
    op.subtractMatrices(matrixATable, matrixBTable, matrixCTable);

}
void Matrix_Calculator::multyplyMatrices() {
    Operations op;
    rowsCSpinBox->setValue(op.rowsA_getter(matrixATable));
    colsCSpinBox->setValue(op.colsB_getter(matrixBTable));
    createMatrixC();
    op.multyplyMatrices(matrixATable, matrixBTable, matrixCTable);
}

void Matrix_Calculator::multyplyconstant(QTableWidget *matrix, QString cnst) {
    Operations op;
    op.multyplyconstant(matrix, cnst);
}

void Matrix_Calculator::multyplyconstantA() {
    // bool ok;
    // double constant = constantA->text().toDouble(&ok);
    // if (!ok || constantA->text().isEmpty()) {
    //     QMessageBox::warning(this, "Ошибка", "Введите корректное число для константы A!");
    //     return;
    // }
    Operations op;
    op.multyplyconstant(matrixATable, constantA->text());
}

void Matrix_Calculator::multyplyconstantB() {
    // bool ok;
    // double constant = constantB->text().toDouble(&ok);
    // if (!ok || constantB->text().isEmpty()) {
    //     QMessageBox::warning(this, "Ошибка", "Введите корректное число для константы B!");
    //     return;
    // }

    Operations op;
    op.multyplyconstant(matrixBTable, constantB->text());
}
