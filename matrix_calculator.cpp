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
    MainLayout->setSpacing(0);
    // MainLayout->setContentsMargins(0,0,0,0);

    QColor iconColor = isDarkTheme() ? Qt::white : Qt::black;
    connect(qApp, &QApplication::paletteChanged, this, &Matrix_Calculator::onPaletteChanged);

    // макет матриц
    QWidget *matricesWidget = new QWidget();
    QHBoxLayout *MatricesLayout = new QHBoxLayout(matricesWidget);

    // Название продкута и линия
    QWidget *vlayoutWidget = new QWidget;
    QHBoxLayout *hlayout = new QHBoxLayout();
    QVBoxLayout *vlayout = new QVBoxLayout(vlayoutWidget);
    // vlayout->setSpacing(0);
    vlayout->setContentsMargins(0,0,0,0);

    // QLabel *iconlabel = new QLabel();
    // iconlabel->setAlignment(Qt::AlignLeft);
    // appIcon = new QIcon(":/Icons/Icon.png");
    // iconlabel->setPixmap(appIcon->pixmap(50, 50));
    // hlayout->addWidget(iconlabel);

    // QLabel *labeltext = new QLabel("Калькулятор матриц");
    // QFont font = labeltext->font();
    // font.setPointSize(20);
    // labeltext->setFont(font);
    // hlayout->addWidget(labeltext);
    // hlayout->addStretch();
    // vlayout->addLayout(hlayout);


    // QWidget *razmerButtonWidget = new QWidget();
    // QHBoxLayout *razmerHButtonLayout = new QHBoxLayout();
    // QVBoxLayout *razmerVLayout = new QVBoxLayout(razmerButtonWidget);

    change3SizeIcon = new QIcon(createColoredIcon(":/Icons/iconmonstr-screen-size-increase-filled.svg", iconColor));
    sizeButton = new QPushButton;
    sizeButton->setIcon(*change3SizeIcon);
    sizeButton->setToolTip("Задать Х размер квадратов А и В значением");

    QLabel *razmer = new QLabel("X :");
    razmerSpinBox = new QSpinBox();
    razmerSpinBox->setRange(1,100);
    razmerSpinBox->setValue(3);
    razmerSpinBox->setToolTip("Задать значение Х");

    copy3Icon = new QIcon(createColoredIcon(":/Icons/iconmonstr-copy-lined-nigga_3.svg", iconColor));
    copymatrices = new QPushButton;
    copymatrices->setIcon(*copy3Icon);
    copymatrices->setToolTip("Скопировать значения 3 матриц");

    insert3Icon = new QIcon(createColoredIcon(":/Icons/iconmonstr-paste-clipboard-filled_3.svg", iconColor));
    insertmatrices = new QPushButton;
    insertmatrices->setIcon(*insert3Icon);
    insertmatrices->setToolTip("Вставить из буфер обменя 3 матрицы");

    swapIcon = new QIcon(createColoredIcon(":/Icons/arrow-goes-left-right-icon.svg", iconColor));
    swapmatrixAB = new QPushButton;
    swapmatrixAB->setIcon(*swapIcon);
    swapmatrixAB->setToolTip("Поменять местами матрицы");

    // sizeButton->setFixedSize(320, 30);
    // razmerHButtonLayout->setAlignment(Qt::AlignHCenter);
    // razmerHButtonLayout->addWidget(sizeButton);
    // razmerHButtonLayout->addWidget(razmer);
    // razmerHButtonLayout->addWidget(razmerSpinBox);
    // razmerHButtonLayout->addWidget(copymatrices);
    // razmerHButtonLayout->addWidget(insertmatrices);
    // razmerVLayout->addLayout(razmerHButtonLayout);
    hlayout->setAlignment(Qt::AlignLeft);
    hlayout->addWidget(sizeButton);
    hlayout->addWidget(razmer);
    hlayout->addWidget(razmerSpinBox);
    hlayout->addWidget(copymatrices);
    hlayout->addWidget(insertmatrices);
    hlayout->addWidget(swapmatrixAB);
    vlayout->addLayout(hlayout);

    auto lineA = new QFrame;
    lineA->setFrameShape(QFrame::HLine);
    lineA->setFrameShadow(QFrame::Sunken);
    vlayout->addWidget(lineA);
    // vlayout->addStretch();


    // swapmatrixAB->setFixedSize(650, 30);
    // razmerVLayout->addWidget(swapmatrixAB, 0, Qt::AlignHCenter);
    // razmerVLayout->addStretch();

    // MainLayout->addWidget(vlayoutWidget);
    // MainLayout->addWidget(razmerButtonWidget);

    MainLayout->addWidget(vlayoutWidget);

    // Матрица А
    QWidget* SizeMatrixA = new QWidget();
    QHBoxLayout* SizeLayoutA = new QHBoxLayout;
    // SizeLayoutA->setSpacing(0);
    // SizeLayoutA->setContentsMargins(0,0,0,0);

    // QWidget *matrixAWidget = new QWidget();
    QVBoxLayout *matrixALayout = new QVBoxLayout(SizeMatrixA);
    // QLabel *matrixALabel = new QLabel("Матрица A");
    matrixATable = new QTableWidget();
    matrixATable->setToolTip("Матрица А");


    matrixATable->setContextMenuPolicy(Qt::CustomContextMenu);

    // Connect the custom context menu signal
    connect(matrixATable, &QTableWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        QMenu contextMenu(tr("Меню выбора"), this);

        QAction *copyAction = new QAction(tr("Скопировать"), this);
        QAction *pasteAction = new QAction(tr("Вставить"), this);
        QAction *clearAction = new QAction(tr("Очистить"), this);

        contextMenu.addAction(copyAction);
        contextMenu.addAction(pasteAction);
        contextMenu.addAction(clearAction);

        connect(copyAction, &QAction::triggered, this, [this]() {
            copy.copy(matrixATable);
        });

        connect(pasteAction, &QAction::triggered, this, [this]() {
            insert.insert(matrixATable);
        });

        connect(clearAction, &QAction::triggered, this, [this]() {
            clean.clearMatrices(matrixATable);
        });

        contextMenu.exec(matrixATable->mapToGlobal(pos));
    });

    // Кнопки для настройки размера матрицы А
    // Строки
    // QLabel *StrokiALabel = new QLabel("Строки A: ");
    rowsASpinBox = new QSpinBox();
    rowsASpinBox->setRange(1, 10);
    rowsASpinBox->setValue(3);
    rowsASpinBox->setToolTip("Строки А");

    // Столбцы
    // QLabel *StolbciALabel = new QLabel("Столбцы A: ");
    colsASpinBox = new QSpinBox();
    colsASpinBox->setRange(1, 10);
    colsASpinBox->setValue(3);
    colsASpinBox->setToolTip("Столбцы А");

    changeSizeIcon = new QIcon(createColoredIcon(":/Icons/four-corners-arrows-line-icon.svg", iconColor));
    CreateMatrixA = new QPushButton;
    CreateMatrixA->setIcon(*changeSizeIcon);
    CreateMatrixA->setToolTip("Поменять размер");

    copyIcon = new QIcon(createColoredIcon(":/Icons/copyIcon.svg", iconColor));
    CopyMatrixA = new QPushButton(); // Use member variable
    CopyMatrixA->setIcon(*copyIcon);
    CopyMatrixA->setToolTip("Скопировать матрицу");

    insertIcon = new QIcon(createColoredIcon(":/Icons/insertIcon.svg", iconColor));
    InsertMatrixA = new QPushButton();
    InsertMatrixA->setIcon(*insertIcon);
    InsertMatrixA->setToolTip("Вставить из буфер обмена");

    // SizeLayoutA->addWidget(matrixALabel);
    // SizeLayoutA->addWidget(StrokiALabel);
    SizeLayoutA->addWidget(rowsASpinBox);
    // SizeLayoutA->addWidget(StolbciALabel);
    SizeLayoutA->addWidget(colsASpinBox);
    SizeLayoutA->addWidget(CreateMatrixA);
    SizeLayoutA->addWidget(CopyMatrixA);
    SizeLayoutA->addWidget(InsertMatrixA);
    SizeLayoutA->setAlignment(Qt::AlignLeft);
    // SizeLayoutA->addStretch();

    matrixALayout->addLayout(SizeLayoutA);
    matrixALayout->addWidget(matrixATable);


    // MainLayout->addWidget(SizeMatrixA);

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
    constantA->setPlaceholderText("const");
    // matrixAButtonsLayout->addWidget(constantA);

    matrixAButtonsLayout->addWidget(transposeAButton);
    matrixAButtonsLayout->addWidget(inverseAButton);
    matrixAButtonsLayout->addWidget(multyplyConstantA);
    matrixAButtonsLayout->addWidget(divideConstantA);
    matrixAButtonsLayout->addWidget(constantA);
    matrixAButtonsLayout->addStretch();
    matrixALayout->addWidget(matrixAButtonsWidget);
    // matrixALayout->addLayout(matrixAButtonsLayout);

    // Матрица B
    QWidget* SizeMatrixB = new QWidget();
    QHBoxLayout* SizeLayoutB = new QHBoxLayout;

    // QWidget *matrixBWidget = new QWidget();
    QVBoxLayout *matrixBLayout = new QVBoxLayout(SizeMatrixB);
    // QLabel *matrixBLabel = new QLabel("Матрица B");
    matrixBTable = new QTableWidget();
    matrixBTable->setToolTip("Матрица В");
    // matrixBLayout->addWidget(matrixBLabel);

    matrixBTable->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(matrixBTable, &QTableWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        QMenu *contextMenuB = new QMenu("Меню выбора", this);

        QAction *copyAction = new QAction(tr("Скопировать"), this);
        QAction *pasteAction = new QAction(tr("Вставить"), this);
        QAction *clearAction = new QAction(tr("Очистить"), this);

        contextMenuB->addAction(copyAction);
        contextMenuB->addAction(pasteAction);
        contextMenuB->addAction(clearAction);

        connect(copyAction, &QAction::triggered, this, [this]() {
            copy.copy(matrixBTable);
        });

        connect(pasteAction, &QAction::triggered, this, [this]() {
            insert.insert(matrixBTable);
        });

        connect(clearAction, &QAction::triggered, this, [this]() {
            clean.clearMatrices(matrixBTable);
        });

        contextMenuB->exec(matrixBTable->mapToGlobal(pos));
    });


    // Кнопки для настройки размера матрицы B
    // Строки
    // QLabel *StrokiBLabel = new QLabel("Строки B: ");
    rowsBSpinBox = new QSpinBox();
    rowsBSpinBox->setRange(1, 10);
    rowsBSpinBox->setValue(3);
    rowsBSpinBox->setToolTip("Строки В");

    // Столбцы
    // QLabel *StolbciBLabel = new QLabel("Столбцы B: ");
    colsBSpinBox = new QSpinBox();
    colsBSpinBox->setRange(1, 10);
    colsBSpinBox->setValue(3);
    colsBSpinBox->setToolTip("Столбцы В");

    CreateMatrixB = new QPushButton;
    CreateMatrixB->setIcon(*changeSizeIcon);
    CreateMatrixB->setToolTip("Поменять размер");

    // QPushButton *CopyMatrixB = new QPushButton("Скопировать");
    // QPushButton *InsertMatrixB = new QPushButton("Вставить");

    CopyMatrixB = new QPushButton();
    CopyMatrixB->setIcon(*copyIcon);
    CopyMatrixB->setToolTip("Скопировать матрицу");
    InsertMatrixB = new QPushButton();
    InsertMatrixB->setIcon(*insertIcon);
    InsertMatrixB->setToolTip("Вставить из буфер обмена");


    // SizeLayoutB->addWidget(StrokiBLabel);
    SizeLayoutB->addWidget(rowsBSpinBox);
    // SizeLayoutB->addWidget(StolbciBLabel);
    SizeLayoutB->addWidget(colsBSpinBox);
    SizeLayoutB->addWidget(CreateMatrixB);
    SizeLayoutB->addWidget(CopyMatrixB);
    SizeLayoutB->addWidget(InsertMatrixB);
    SizeLayoutB->setAlignment(Qt::AlignLeft);
    // SizeLayoutB->addStretch();
    matrixBLayout->addLayout(SizeLayoutB);
    matrixBLayout->addWidget(matrixBTable);

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
    constantB->setPlaceholderText("const");
    matrixBButtonsLayout->addWidget(constantB);

    matrixBButtonsLayout->addWidget(transposeBButton);
    matrixBButtonsLayout->addWidget(inverseBButton);
    matrixBButtonsLayout->addWidget(multyplyConstantB);
    matrixBButtonsLayout->addWidget(divideConstantB);
    matrixBButtonsLayout->addWidget(constantB);
    matrixBButtonsLayout->addStretch();
    matrixBLayout->addWidget(matrixBButtonsWidget);

    MatricesLayout->addWidget(SizeMatrixA);
    MatricesLayout->addWidget(SizeMatrixB);
    MainLayout->addWidget(matricesWidget);

    // операции над матрицами
    QWidget* operationsWidget = new QWidget();
    QHBoxLayout* operationsLayout = new QHBoxLayout(operationsWidget);
    operationsLayout->setSpacing(0);

    // QLabel* operationsLabel = new QLabel("Операции: ");


    multiply = new QIcon(createColoredIcon(":/Icons/mathematics-sign-multiplied-round-icon.svg", iconColor));
    summarize = new QIcon(createColoredIcon(":/Icons/plus-round-icon.svg", iconColor));
    substract = new QIcon(createColoredIcon(":/Icons/minus-round-icon.svg", iconColor));
    cleanIcon = new QIcon(createColoredIcon(":/Icons/broom-cleaning-icon.svg", iconColor));
    randomizeIcon = new QIcon(createColoredIcon(":/Icons/RAND.svg", iconColor));

    summButton = new QPushButton;
    summButton->setIcon(*summarize);
    summButton->setToolTip("Операция суммы");

    raznButton = new QPushButton;
    raznButton->setIcon(*substract);
    raznButton->setToolTip("Операция разности");

    multiplyButton = new QPushButton;
    multiplyButton->setIcon(*multiply);
    multiplyButton->setToolTip("Операция произведения");

    clearButton = new QPushButton;
    clearButton->setIcon(*cleanIcon);
    clearButton->setToolTip("Очистить матрицы");

    randomButton = new QPushButton;
    randomButton->setIcon(*randomizeIcon);
    randomButton->setToolTip("Вставить случайные значения в матрицы А и В");


    // operationsLayout->addWidget(operationsLabel);
    operationsLayout->addWidget(summButton);
    operationsLayout->addWidget(raznButton);
    operationsLayout->addWidget(multiplyButton);
    operationsLayout->addWidget(clearButton);
    operationsLayout->addWidget(randomButton);
    operationsLayout->addStretch();
    MainLayout->addWidget(operationsWidget);

    // Результирующая матрица C
    // QWidget* SizeMatrixC = new QWidget();
    QWidget* matrixCWidget = new QWidget();
    QHBoxLayout* matrixc = new QHBoxLayout();
    QVBoxLayout* matrixCLayout = new QVBoxLayout(matrixCWidget);
    // QLabel* matrixCLabel = new QLabel("Результирующая матрица");

    CopyMatrixC = new QPushButton;
    CopyMatrixC->setIcon(*copyIcon);
    CopyMatrixC->setToolTip("Скопировать матрицу");

    matrixc->setAlignment(Qt::AlignLeft);
    matrixCTable = new QTableWidget();
    // matrixc->addWidget(matrixCLabel);
    matrixc->addWidget(CopyMatrixC);
    matrixCLayout->addLayout(matrixc);
    matrixCLayout->addWidget(matrixCTable);

    rowsCSpinBox = new QSpinBox();
    rowsCSpinBox->setValue(3);

    colsCSpinBox = new QSpinBox();
    colsCSpinBox->setValue(3);

    // MainLayout->addWidget(SizeMatrixC);

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
        // Сохраняем старые размеры до изменения матриц
        int oldRowsA = matrixATable->rowCount();
        int oldColsA = matrixATable->columnCount();
        int oldRowsB = matrixBTable->rowCount();
        int oldColsB = matrixBTable->columnCount();

        // Сохраняем данные матриц перед перестановкой
        QVector<QVector<double>> tempA = oper.settempA(oper.rows_getter(matrixATable), oper.cols_getter(matrixATable), matrixATable);
        QVector<QVector<double>> tempB = oper.settempB(oper.rows_getter(matrixBTable), oper.cols_getter(matrixBTable), matrixBTable);

        // Обновляем значения спин-боксов
        rowsASpinBox->setValue(oldRowsB);
        colsASpinBox->setValue(oldColsB);
        rowsBSpinBox->setValue(oldRowsA);
        colsBSpinBox->setValue(oldColsA);

        // Создаём матрицы с правильными размерами
        matr.createMatrix(matrixATable, oldRowsB, oldColsB);
        matr.createMatrix(matrixBTable, oldRowsA, oldColsA);

        // Меняем значения местами
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
