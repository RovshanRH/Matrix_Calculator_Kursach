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

    QColor iconColor = isDarkTheme() ? Qt::white : Qt::black;
    connect(qApp, &QApplication::paletteChanged, this, &Matrix_Calculator::onPaletteChanged);

    // макет матриц
    QWidget *matricesWidget = new QWidget();
    QHBoxLayout *MatricesLayout = new QHBoxLayout(matricesWidget);

    // Название продкута и линия
    QWidget *vlayoutWidget = new QWidget;
    QHBoxLayout *hlayout = new QHBoxLayout();
    QVBoxLayout *vlayout = new QVBoxLayout(vlayoutWidget);

    QLabel *iconlabel = new QLabel();
    iconlabel->setAlignment(Qt::AlignLeft);
    appIcon = new QIcon(":/Icons/Icon.png");
    iconlabel->setPixmap(appIcon->pixmap(50, 50));
    hlayout->addWidget(iconlabel);

    QLabel *labeltext = new QLabel("Калькулятор матриц");
    QFont font = labeltext->font();
    font.setPointSize(20);
    labeltext->setFont(font);
    hlayout->addWidget(labeltext);
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

    change3SizeIcon = new QIcon(createColoredIcon(":/Icons/iconmonstr-screen-size-increase-filled.svg", iconColor));
    sizeButton = new QPushButton;
    sizeButton->setIcon(*change3SizeIcon);

    QLabel *razmer = new QLabel("X :");
    razmerSpinBox = new QSpinBox();
    razmerSpinBox->setRange(1,100);
    razmerSpinBox->setValue(3);

    copy3Icon = new QIcon(createColoredIcon(":/Icons/iconmonstr-copy-lined-nigga_3.svg", iconColor));
    copymatrices = new QPushButton;
    copymatrices->setIcon(*copy3Icon);

    insert3Icon = new QIcon(createColoredIcon(":/Icons/iconmonstr-paste-clipboard-filled_3.svg", iconColor));
    insertmatrices = new QPushButton;
    insertmatrices->setIcon(*insert3Icon);

    // sizeButton->setFixedSize(320, 30);
    razmerHButtonLayout->setAlignment(Qt::AlignHCenter);
    razmerHButtonLayout->addWidget(sizeButton);
    razmerHButtonLayout->addWidget(razmer);
    razmerHButtonLayout->addWidget(razmerSpinBox);
    razmerHButtonLayout->addWidget(copymatrices);
    razmerHButtonLayout->addWidget(insertmatrices);
    razmerVLayout->addLayout(razmerHButtonLayout);

    swapIcon = new QIcon(createColoredIcon(":/Icons/arrow-goes-left-right-icon.svg", iconColor));
    swapmatrixAB = new QPushButton;
    swapmatrixAB->setIcon(*swapIcon);

    // swapmatrixAB->setFixedSize(650, 30);
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

    changeSizeIcon = new QIcon(createColoredIcon(":/Icons/four-corners-arrows-line-icon.svg", iconColor));
    CreateMatrixA = new QPushButton;
    CreateMatrixA->setIcon(*changeSizeIcon);

    copyIcon = new QIcon(createColoredIcon(":/Icons/copyIcon.svg", iconColor));
    CopyMatrixA = new QPushButton(); // Use member variable
    CopyMatrixA->setIcon(*copyIcon);

    insertIcon = new QIcon(createColoredIcon(":/Icons/insertIcon.svg", iconColor));
    InsertMatrixA = new QPushButton();
    InsertMatrixA->setIcon(*insertIcon);

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

    CreateMatrixB = new QPushButton;
    CreateMatrixB->setIcon(*changeSizeIcon);

    // QPushButton *CopyMatrixB = new QPushButton("Скопировать");
    // QPushButton *InsertMatrixB = new QPushButton("Вставить");

    CopyMatrixB = new QPushButton();
    CopyMatrixB->setIcon(*copyIcon);
    InsertMatrixB = new QPushButton();
    InsertMatrixB->setIcon(*insertIcon);

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


    multiply = new QIcon(createColoredIcon(":/Icons/mathematics-sign-multiplied-round-icon.svg", iconColor));
    summarize = new QIcon(createColoredIcon(":/Icons/plus-round-icon.svg", iconColor));
    substract = new QIcon(createColoredIcon(":/Icons/minus-round-icon.svg", iconColor));
    cleanIcon = new QIcon(createColoredIcon(":/Icons/broom-cleaning-icon.svg", iconColor));
    randomizeIcon = new QIcon(createColoredIcon(":/Icons/RAND.svg", iconColor));

    summButton = new QPushButton;
    summButton->setIcon(*summarize);
    summButton->setToolTip("SOSAT'");

    raznButton = new QPushButton;
    raznButton->setIcon(*substract);

    multiplyButton = new QPushButton;
    multiplyButton->setIcon(*multiply);

    clearButton = new QPushButton;
    clearButton->setIcon(*cleanIcon);

    randomButton = new QPushButton;
    randomButton->setIcon(*randomizeIcon);


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

    CopyMatrixC = new QPushButton;
    CopyMatrixC->setIcon(*copyIcon);

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

Matrix_Calculator::~Matrix_Calculator()
{
    vector<QIcon*> qicons {
        appIcon,
        copyIcon,
        insertIcon,
        changeSizeIcon,
        change3SizeIcon,
        copy3Icon,
        insert3Icon,
        cleanIcon,
        randomizeIcon,
        swapIcon,
        transposeAIcon,
        transposeBIcon,
        inverseAIcon,
        inverseBIcon,
        AmultyplybyC,
        AsubstractbyC,
        BmultyplybyC,
        BsubstractbyC,
        multiply,
        summarize,
        substract
    };

    const int arraySize = qicons.size();

    for (int i = 0; i < arraySize; i++) {
        delete qicons[i];
    }

    QList<QValidator*> validators = findChildren<QValidator*>();
    for (QValidator* validator : std::as_const(validators)) {
        if (!validator->parent()) {
            delete validator;
        }
    }
}
#include <QPalette>
#include <QSvgRenderer>
#include <QPainter>

// Функция для определения темы
bool Matrix_Calculator::isDarkTheme() {
    QPalette palette = QApplication::palette();
    return palette.color(QPalette::Window).lightness() < 128;
}

// Функция для изменения цвета SVG-иконки
QIcon Matrix_Calculator::createColoredIcon(const QString &iconPath, const QColor &color) {
    QSvgRenderer renderer(iconPath);
    QImage image(32, 32, QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    renderer.render(&painter);

    // Применяем цветовой фильтр
    for (int x = 0; x < image.width(); ++x) {
        for (int y = 0; y < image.height(); ++y) {
            QColor pixel = image.pixelColor(x, y);
            if (pixel.alpha() > 0) {
                image.setPixelColor(x, y, color);
            }
        }
    }

    return QIcon(QPixmap::fromImage(image));
}

void Matrix_Calculator::updateIcons(QIcon *icon, QPushButton *button, const QString &iconPath) {
    QColor iconColor = isDarkTheme() ? Qt::white : Qt::black;

    if (icon && button) {
        *icon = createColoredIcon(iconPath, iconColor);
        button->setIcon(*icon);
    }
}

void Matrix_Calculator::onPaletteChanged() {
    updateIcons(copyIcon, CopyMatrixA, ":/Icons/copyIcon.svg");
    updateIcons(insertIcon, InsertMatrixA, ":/Icons/insertIcon.svg");
    updateIcons(copyIcon, CopyMatrixB, ":/Icons/copyIcon.svg");
    updateIcons(insertIcon, InsertMatrixB, ":/Icons/insertIcon.svg");
    updateIcons(copyIcon, CopyMatrixC, ":/Icons/copyIcon.svg");
    updateIcons(change3SizeIcon, sizeButton, ":/Icons/iconmonstr-screen-size-increase-filled.svg");
    updateIcons(copy3Icon, copymatrices, ":/Icons/iconmonstr-copy-lined-nigga_3.svg");
    updateIcons(insert3Icon, insertmatrices, ":/Icons/iconmonstr-paste-clipboard-filled_3.svg");
    updateIcons(swapIcon, swapmatrixAB, ":/Icons/arrow-goes-left-right-icon.svg");
    updateIcons(changeSizeIcon, CreateMatrixA, ":/Icons/four-corners-arrows-line-icon.svg");
    updateIcons(changeSizeIcon, CreateMatrixB, ":/Icons/four-corners-arrows-line-icon.svg");
    updateIcons(multiply, multiplyButton, ":/Icons/mathematics-sign-multiplied-round-icon.svg");
    updateIcons(summarize, summButton, ":/Icons/plus-round-icon.svg");
    updateIcons(substract, raznButton, ":/Icons/minus-round-icon.svg");
    updateIcons(cleanIcon, clearButton, ":/Icons/broom-cleaning-icon.svg");
    updateIcons(randomizeIcon, randomButton, ":/Icons/RAND.svg");
}
