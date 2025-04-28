#include "matrix_calculator.h"
#include "randomizer.h"
#include "cleaner.h"
#include "operations.h"
#include "inverse.h"
#include "copymatrix.h"
#include "insertmatrix.h"


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
    razmerSpinBox->setRange(1,100);
    razmerSpinBox->setValue(3);
    QPushButton *copymatrices = new QPushButton("Скопировать 3 матрицы");
    QPushButton *insertmatrices = new QPushButton("Вставить 3 матрицы");
    sizeButton->setFixedSize(320, 30);
    razmerHButtonLayout->setAlignment(Qt::AlignHCenter);
    razmerHButtonLayout->addWidget(sizeButton);
    razmerHButtonLayout->addWidget(razmer);
    razmerHButtonLayout->addWidget(razmerSpinBox);
    razmerHButtonLayout->addWidget(copymatrices);
    razmerHButtonLayout->addWidget(insertmatrices);
    razmerVLayout->addLayout(razmerHButtonLayout);
    QPushButton *swapmatrixAB = new QPushButton("Поменять местами матрицы");
    swapmatrixAB->setFixedSize(650, 30);
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

    QPushButton *CopyMatrixA = new QPushButton("Скопировать");
    QPushButton *InsertMatrixA = new QPushButton("Вставить");

    SIzeLayout->addWidget(StrokiALabel);
    SIzeLayout->addWidget(rowsASpinBox);
    SIzeLayout->addWidget(StolbciALabel);
    SIzeLayout->addWidget(colsASpinBox);
    SIzeLayout->addWidget(CreateMatrixA);
    SIzeLayout->addWidget(CopyMatrixA);
    SIzeLayout->addWidget(InsertMatrixA);
    SIzeLayout->addStretch();
    MainLayout->addWidget(SizeMatrixA);

    // Кнопки для матрицы А
    QWidget *matrixAButtonsWidget = new QWidget();
    QHBoxLayout *matrixAButtonsLayout = new QHBoxLayout(matrixAButtonsWidget);
    QPushButton *transposeAButton = new QPushButton("Aᵀ");
    QPushButton *inverseAButton = new QPushButton("A⁻¹");
    QPushButton *multyplyConstantA = new QPushButton("* на c");
    QPushButton *divideConstantA = new QPushButton("/ на c");

    constantA = new QLineEdit();
    QDoubleValidator *validatorA = new QDoubleValidator(-1000.0, 1000.0, 2, constantA);
    constantA->setValidator(validatorA);
    constantA->setPlaceholderText("c");
    matrixAButtonsLayout->addWidget(constantA);

    matrixAButtonsLayout->addWidget(transposeAButton);
    matrixAButtonsLayout->addWidget(inverseAButton);
    matrixAButtonsLayout->addWidget(multyplyConstantA);
    matrixAButtonsLayout->addWidget(divideConstantA);
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

    QPushButton *CopyMatrixB = new QPushButton("Скопировать");
    QPushButton *InsertMatrixB = new QPushButton("Вставить");

    SIzeLayout->addWidget(StrokiBLabel);
    SIzeLayout->addWidget(rowsBSpinBox);
    SIzeLayout->addWidget(StolbciBLabel);
    SIzeLayout->addWidget(colsBSpinBox);
    SIzeLayout->addWidget(CreateMatrixB);
    SIzeLayout->addWidget(CopyMatrixB);
    SIzeLayout->addWidget(InsertMatrixB);
    SIzeLayout->addStretch();
    MainLayout->addWidget(SizeMatrixB);

    // Кнопки для матрицы B
    QWidget *matrixBButtonsWidget = new QWidget();
    QHBoxLayout *matrixBButtonsLayout = new QHBoxLayout(matrixBButtonsWidget);
    QPushButton *transposeBButton = new QPushButton("Bᵀ");
    QPushButton *inverseBButton = new QPushButton("B⁻¹");
    QPushButton *multyplyConstantB = new QPushButton("* на c");
    QPushButton *divideConstantB = new QPushButton("/ на c");

    constantB = new QLineEdit();
    QDoubleValidator *validatorB = new QDoubleValidator(-1000.0, 1000.0, 2, constantB);
    constantB->setValidator(validatorB);
    constantB->setPlaceholderText("c");
    matrixBButtonsLayout->addWidget(constantB);

    matrixBButtonsLayout->addWidget(transposeBButton);
    matrixBButtonsLayout->addWidget(inverseBButton);
    matrixBButtonsLayout->addWidget(multyplyConstantB);
    matrixBButtonsLayout->addWidget(divideConstantB);
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
    QHBoxLayout* matrixc = new QHBoxLayout();
    QVBoxLayout* matrixCLayout = new QVBoxLayout(matrixCWidget);
    QLabel* matrixCLabel = new QLabel("Результирующая матрица");
    QPushButton *CopyMatrixC = new QPushButton("Скопировать");
    matrixc->setAlignment(Qt::AlignLeft);
    matrixCTable = new QTableWidget();
    matrixc->addWidget(matrixCLabel);
    matrixc->addWidget(CopyMatrixC);
    matrixCLayout->addLayout(matrixc);
    matrixCLayout->addWidget(matrixCTable);



    rowsCSpinBox = new QSpinBox();
    rowsCSpinBox->setValue(3);

    colsCSpinBox = new QSpinBox();
    colsCSpinBox->setValue(3);


    MainLayout->addWidget(SizeMatrixC);

    MainLayout->addWidget(matrixCWidget);

    connect(CreateMatrixA, &QPushButton::clicked, this, [this]() {
        matr.createMatrix(matrixATable, rowsASpinBox->value(), colsASpinBox->value());
    });
    connect(CreateMatrixB, &QPushButton::clicked, this, [this]() {
        matr.createMatrix(matrixBTable, rowsBSpinBox->value(), colsBSpinBox->value());
    });

    connect(summButton, &QPushButton::clicked, this, [this]() {

        int rowsA = matrixATable->rowCount();
        int colsA = matrixATable->columnCount();
        int rowsB = matrixBTable->rowCount();
        int colsB = matrixBTable->columnCount();

        rowsCSpinBox->setValue(oper.rows_getter(matrixATable));
        colsCSpinBox->setValue(oper.cols_getter(matrixBTable));

        if (rowsA != rowsB || colsA != colsB) {
            QMessageBox::warning(nullptr, "Ошибка", "Размеры матриц должны совпадать!");
            return;
        }

        matr.createMatrix(matrixCTable, rowsA, colsA);
        oper.addMatrices(matrixATable, matrixBTable, matrixCTable);


    });

    connect(raznButton, &QPushButton::clicked, this, [this](){

        int rowsA = matrixATable->rowCount();
        int colsA = matrixATable->columnCount();
        int rowsB = matrixBTable->rowCount();
        int colsB = matrixBTable->columnCount();

        rowsCSpinBox->setValue(oper.rows_getter(matrixATable));
        colsCSpinBox->setValue(oper.cols_getter(matrixBTable));

        if (rowsA != rowsB || colsA != colsB) {
            QMessageBox::warning(nullptr, "Ошибка", "Размеры матриц должны совпадать!");
            return;
        }

        matr.createMatrix(matrixCTable, rowsA, colsA);
        oper.subtractMatrices(matrixATable, matrixBTable, matrixCTable);



    });

    connect(multiplyButton, &QPushButton::clicked, this, [this](){

        int rowsA = matrixATable->rowCount();
        int colsA = matrixATable->columnCount();
        int rowsB = matrixBTable->rowCount();
        int colsB = matrixBTable->columnCount();

        rowsCSpinBox->setValue(oper.rows_getter(matrixATable));
        colsCSpinBox->setValue(oper.cols_getter(matrixBTable));

        if (colsA != rowsB) {
            QMessageBox::warning(nullptr, "Ошибка", "Кол-во строк матрицы A должно совпадать с кол-во столбцов матрицы B");
            return;
        }

        matr.createMatrix(matrixCTable, rowsA, colsB);
        oper.multyplyMatrices(matrixATable, matrixBTable, matrixCTable);


    });

    connect(transposeAButton, &QPushButton::clicked, this, [this]() {
        oper.transposeMatrix(matrixATable);
    });
    connect(transposeBButton, &QPushButton::clicked, this, [this]() {
        oper.transposeMatrix(matrixBTable);
    });

    connect(clearButton, &QPushButton::clicked, this, [this]() {
        clean.clearMatrices(matrixATable);
        clean.clearMatrices(matrixBTable);
        clean.clearMatrices(matrixCTable);

    });

    connect(randomButton, &QPushButton::clicked, this, [this]() {
        randomizer.randomizeMatrices(matrixATable);
        randomizer.randomizeMatrices(matrixBTable);

    });


    connect(sizeButton, &QPushButton::clicked, this, [this](){
        int size = razmerSpinBox->value();
        matr.create2Matrices(matrixATable, matrixBTable, size, size);
    });

    connect(inverseAButton, &QPushButton::clicked, this, [this]() {
        inverter.invertMatrix(matrixATable);
    });

    connect(inverseBButton, &QPushButton::clicked, this, [this]() {
        inverter.invertMatrix(matrixBTable);
    });

    connect(swapmatrixAB, &QPushButton::clicked, this, [this]() {

        QVector<QVector<double>> tempA = oper.settempA(oper.rows_getter(matrixATable), oper.cols_getter(matrixATable), matrixATable);
        QVector<QVector<double>> tempB = oper.settempB(oper.rows_getter(matrixBTable), oper.cols_getter(matrixBTable), matrixBTable);

        rowsASpinBox->setValue(oper.rows_getter(matrixBTable));
        colsASpinBox->setValue(oper.cols_getter(matrixBTable));
        rowsBSpinBox->setValue(oper.rows_getter(matrixATable));
        colsBSpinBox->setValue(oper.cols_getter(matrixATable));

        matr.createMatrix(matrixATable, matrixBTable->rowCount(), matrixBTable->columnCount());
        matr.createMatrix(matrixBTable, matrixATable->rowCount(), matrixATable->columnCount());

        oper.swapMatrices(matrixATable, matrixBTable, tempB, tempA);
    });

    connect(multyplyConstantA, &QPushButton::clicked, this, [this]() {
        bool ok;
        double constant = constantA->text().toDouble(&ok);
        if (!ok || constantA->text().isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите корректное число для константы A");
            return;
        }
        oper.multyplyconstant(matrixATable, constant);
    });

    connect(multyplyConstantB, &QPushButton::clicked, this, [this]() {
        bool ok;
        double constant = constantB->text().toDouble(&ok);
        if (!ok || constantB->text().isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите корректное число для константы B");
            return;
        }
        oper.multyplyconstant(matrixBTable, constant);
    });

    connect(divideConstantA, &QPushButton::clicked, this, [this]() {
        bool ok;
        double constant = constantA->text().toDouble(&ok);
        if (!ok || constantA->text().isEmpty() || constantA->text().toDouble() == 0) {
            QMessageBox::warning(this, "Ошибка", "Введите корректное число для константы A");
            return;
        }
        oper.divisionconstant(matrixATable, constant);
    });
    connect(divideConstantB, &QPushButton::clicked, this, [this]() {
        bool ok;
        double constant = constantB->text().toDouble(&ok);
        if (!ok || constantB->text().isEmpty() || constantB->text().toDouble() == 0) {
            QMessageBox::warning(this, "Ошибка", "Введите корректное число для константы B");
            return;
        }
        oper.divisionconstant(matrixBTable, constant);
    });


    connect(CopyMatrixA, &QPushButton::clicked, this, [this]() {
        copy.copy(matrixATable);
    });
    connect(CopyMatrixB, &QPushButton::clicked, this, [this]() {
        copy.copy(matrixBTable);
    });
    connect(CopyMatrixC, &QPushButton::clicked, this, [this]() {
        copy.copy(matrixCTable);
    });
    connect(copymatrices, &QPushButton::clicked, this, [this]() {
        copy.copyThreeMatricesToClipboard(matrixATable, matrixBTable, matrixCTable);
    });

    connect(InsertMatrixA, &QPushButton::clicked, this, [this]() {
        insert.insert(matrixATable);
    });
    connect(InsertMatrixB, &QPushButton::clicked, this, [this]() {
        insert.insert(matrixBTable);
    });
    connect(insertmatrices, &QPushButton::clicked, this, [this]() {
        insert.insertThreeMatrices(matrixATable, matrixBTable, matrixCTable);
    });

    matr.create3Matrices(matrixATable, matrixBTable, matrixCTable, 3, 3);

}
