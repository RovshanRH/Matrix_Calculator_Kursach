#include "matrix_calculator.h"
#include "qpainter.h"
#include "qsvgrenderer.h"
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

    // Initialize appIcon here which was missing
    appIcon = nullptr;

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

    QPushButton* help = new QPushButton(tr("Помощь"), this);

    connect(help, &QPushButton::clicked, this, [this]() {
        helpi.show();
    });

    change3SizeIcon = new QIcon(createColoredIcon(":/Icons/iconmonstr-screen-size-increase-filled.svg", iconColor));
    sizeButton = new QPushButton;
    sizeButton->setIcon(*change3SizeIcon);
    sizeButton->setToolTip("Задать Х размер квадратов А и В значением");

    QLabel *razmer = new QLabel("X :");
    razmerSpinBox = new QSpinBox;
    razmerSpinBox->setRange(1,10);
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

    hlayout->setAlignment(Qt::AlignLeft);
    hlayout->addWidget(sizeButton);
    hlayout->addWidget(razmer);
    hlayout->addWidget(razmerSpinBox);
    /*hlayout->addWidget(copymatrices);
    hlayout->addWidget(insertmatrices);
    hlayout->addWidget(swapmatrixAB)*/
    hlayout->addWidget(help);
    vlayout->addLayout(hlayout);

    auto lineA = new QFrame;
    lineA->setFrameShape(QFrame::HLine);
    lineA->setFrameShadow(QFrame::Sunken);
    vlayout->addWidget(lineA);

    MainLayout->addWidget(vlayoutWidget);

    // Матрица А
    QWidget* SizeMatrixA = new QWidget();
    QHBoxLayout* SizeLayoutA = new QHBoxLayout;

    QVBoxLayout *matrixALayout = new QVBoxLayout(SizeMatrixA);
    matrixATable = new QTableWidget();
    matrixATable->setToolTip("Матрица А");

    rowsASpinBox = new QSpinBox();
    // rowsASpinBox->setRange(1, 10);
    // rowsASpinBox->setValue(3);

    colsASpinBox = new QSpinBox();
    // colsASpinBox->setRange(1, 10);
    // colsASpinBox->setValue(3);

    changeSizeIcon = new QIcon(createColoredIcon(":/Icons/four-corners-arrows-line-icon.svg", iconColor));
    CreateMatrixA = new QPushButton;
    CreateMatrixA->setIcon(*changeSizeIcon);
    CreateMatrixA->setToolTip("Поменять размер");

    copyIcon = new QIcon(createColoredIcon(":/Icons/copyIcon.svg", iconColor));
    CopyMatrixA = new QPushButton();
    CopyMatrixA->setIcon(*copyIcon);
    CopyMatrixA->setToolTip("Скопировать матрицу");

    insertIcon = new QIcon(createColoredIcon(":/Icons/insertIcon.svg", iconColor));
    InsertMatrixA = new QPushButton();
    InsertMatrixA->setIcon(*insertIcon);
    InsertMatrixA->setToolTip("Вставить из буфер обмена");

    QLabel *RangALabel = new QLabel("Ранг А: ");
    QLabel *RangeAValue = new QLabel(QString::number(0));
    QPushButton *RangAButton = new QPushButton("Ранг");
    RangAButton->setToolTip("Найти ранг матрицы");

    // Кнопки для матрицы А
    QWidget *matrixAButtonsWidget = new QWidget();
    QHBoxLayout *matrixAButtonsLayout = new QHBoxLayout(matrixAButtonsWidget);

    transposeAIcon = new QIcon(createColoredIcon(":/Icons/A-transpose.svg", iconColor));
    transposeAButton = new QPushButton;
    transposeAButton->setIcon(*transposeAIcon);
    transposeAButton->setToolTip("Транспонирование");
    // transposeAButton->setIconSize(QSize(50, 50));

    inverseAIcon = new QIcon(createColoredIcon(":/Icons/A-inverse.svg", iconColor));
    inverseAButton = new QPushButton;
    inverseAButton->setIcon(*inverseAIcon);
    inverseAButton->setToolTip("Обратная матрица");

    AmultyplybyC = new QIcon(createColoredIcon(":/Icons/multiplyC.svg", iconColor));
    multyplyConstantA = new QPushButton;
    multyplyConstantA->setIcon(*AmultyplybyC);
    multyplyConstantA->setToolTip("Умножить на константу");

    AsubstractbyC = new QIcon(createColoredIcon(":/Icons/divC.svg", iconColor));
    divideConstantA = new QPushButton;
    divideConstantA->setIcon(*AsubstractbyC);
    divideConstantA->setToolTip("Делить на константу");

    constantA = new QLineEdit();
    QDoubleValidator *validatorA = new QDoubleValidator(-1000.0, 1000.0, 2, constantA);
    constantA->setValidator(validatorA);
    constantA->setPlaceholderText("const");

    qDebug() << "setup A start";

    setupMatrix(
        MainLayout,
        MatricesLayout,
        matricesWidget,
        SizeMatrixA,
        SizeLayoutA,
        matrixALayout,
        matrixATable,
        rowsASpinBox,
        colsASpinBox,
        CreateMatrixA,
        transposeAButton,
        inverseAButton,
        multyplyConstantA,
        divideConstantA,
        constantA,
        matrixAButtonsWidget,
        matrixAButtonsLayout,
        RangALabel,
        RangeAValue,
        RangAButton,
        "матрица А"
        );

    qDebug() << "setup A end";

    // Матрица B
    QWidget* SizeMatrixB = new QWidget();
    QHBoxLayout* SizeLayoutB = new QHBoxLayout;

    QVBoxLayout *matrixBLayout = new QVBoxLayout(SizeMatrixB);
    matrixBTable = new QTableWidget();
    matrixBTable->setToolTip("Матрица В");

    rowsBSpinBox = new QSpinBox();
    // rowsBSpinBox->setRange(1, 10);
    // rowsBSpinBox->setValue(3);

    colsBSpinBox = new QSpinBox();
    // colsBSpinBox->setRange(1, 10);
    // colsBSpinBox->setValue(3);

    CreateMatrixB = new QPushButton;
    CreateMatrixB->setIcon(*changeSizeIcon);
    CreateMatrixB->setToolTip("Поменять размер");

    // Initialize these buttons which were missing
    CopyMatrixB = new QPushButton();
    CopyMatrixB->setIcon(*copyIcon);
    CopyMatrixB->setToolTip("Скопировать матрицу");

    InsertMatrixB = new QPushButton();
    InsertMatrixB->setIcon(*insertIcon);
    InsertMatrixB->setToolTip("Вставить из буфер обмена");

    QLabel *RangBLabel = new QLabel("Ранг В: ");
    QLabel *RangeBValue = new QLabel(QString::number(0));
    QPushButton* RangBButton = new QPushButton("Ранг");
    RangBButton->setToolTip("Найти ранг матрицы");

    // Кнопки для матрицы B
    QWidget *matrixBButtonsWidget = new QWidget();
    QHBoxLayout *matrixBButtonsLayout = new QHBoxLayout(matrixBButtonsWidget);

    transposeBIcon = new QIcon(createColoredIcon(":/Icons/B-transpose.svg", iconColor));
    transposeBButton = new QPushButton;
    transposeBButton->setIcon(*transposeBIcon);
    transposeBButton->setToolTip("Транспонирование");

    inverseBIcon = new QIcon(createColoredIcon(":/Icons/B-inverse.svg", iconColor));
    inverseBButton = new QPushButton;
    inverseBButton->setIcon(*inverseBIcon);
    inverseBButton->setToolTip("Обратная матрица");

    BmultyplybyC = new QIcon(createColoredIcon(":/Icons/multiplyC.svg", iconColor));
    multyplyConstantB = new QPushButton;
    multyplyConstantB->setIcon(*BmultyplybyC);
    multyplyConstantB->setToolTip("УМножить на константу");

    // Fix: Changed icon path to the correct one for division
    BsubstractbyC = new QIcon(createColoredIcon(":/Icons/divC.svg", iconColor));
    divideConstantB = new QPushButton;
    divideConstantB->setIcon(*BsubstractbyC);
    divideConstantB->setToolTip("Делить на константу");

    constantB = new QLineEdit();
    QDoubleValidator *validatorB = new QDoubleValidator(-1000.0, 1000.0, 2, constantB);
    constantB->setValidator(validatorB);
    constantB->setPlaceholderText("const");

    qDebug() << "Setup B start";

    setupMatrix(
        MainLayout,
        MatricesLayout,
        matricesWidget,
        SizeMatrixB,
        SizeLayoutB,
        matrixBLayout,
        matrixBTable,
        rowsBSpinBox,
        colsBSpinBox,
        CreateMatrixB,
        transposeBButton,
        inverseBButton,
        multyplyConstantB,
        divideConstantB,
        constantB,
        matrixBButtonsWidget,
        matrixBButtonsLayout,
        RangBLabel,
        RangeBValue,
        RangBButton,
        "матрица В"
        );

    qDebug() << "Setup B end";

    // операции над матрицами
    QWidget* operationsWidget = new QWidget();
    QHBoxLayout* operationsLayout = new QHBoxLayout(operationsWidget);
    operationsLayout->setSpacing(0);

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

    operationsLayout->addWidget(summButton);
    operationsLayout->addWidget(raznButton);
    operationsLayout->addWidget(multiplyButton);
    operationsLayout->addWidget(clearButton);
    operationsLayout->addWidget(randomButton);
    operationsLayout->addStretch();
    MainLayout->addWidget(operationsWidget);

    // Результирующая матрица C
    QWidget* matrixCWidget = new QWidget();
    QVBoxLayout* matrixCLayout = new QVBoxLayout(matrixCWidget);

    // Add CopyMatrixC button which was commented out
    CopyMatrixC = new QPushButton;
    CopyMatrixC->setIcon(*copyIcon);
    CopyMatrixC->setToolTip("Скопировать матрицу");

    QHBoxLayout* matrixc = new QHBoxLayout();
    matrixc->setAlignment(Qt::AlignLeft);
    // matrixc->addWidget(CopyMatrixC);
    matrixCLayout->addLayout(matrixc);

    matrixCTable = new QTableWidget();
    matrixCLayout->addWidget(matrixCTable);

    matrixCTable->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(matrixCTable, &QTableWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        QMenu *contextMenuC = new QMenu("Меню выбора", this);

        QAction *copyAction = new QAction(tr("Скопировать"), this);
        QAction *pasteAction = new QAction(tr("Вставить"), this);
        QAction *clearAction = new QAction(tr("Очистить"), this);

        contextMenuC->addAction(copyAction);
        contextMenuC->addAction(pasteAction);
        contextMenuC->addAction(clearAction);

        connect(copyAction, &QAction::triggered, this, [this]() {
            copy.copy(matrixCTable);
        });

        connect(pasteAction, &QAction::triggered, this, [this]() {
            insert.insert(matrixCTable);
        });

        connect(clearAction, &QAction::triggered, this, [this]() {
            clean.clearMatrices(matrixCTable);
        });

        contextMenuC->exec(matrixCTable->mapToGlobal(pos));
    });

    MainLayout->addWidget(matrixCWidget);

    qDebug() << "end";

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

    CentralWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(CentralWidget, &QTableWidget::customContextMenuRequested, this, [this, CentralWidget](const QPoint &pos) {
        QMenu *menuBar = new QMenu(tr("Режим выбора"), this);

        QAction *copy3Action = new QAction(tr("Скопировать 3 матрицы"), this);
        QAction *paste3Action = new QAction(tr("Вставить 3 матрицы"), this);
        QAction *cleareAllAction = new QAction(tr("Очистить матрицы"), this);
        QAction *swapAction = new QAction(tr("Поменять матрицы А и В местами"), this);

        menuBar->addAction(copy3Action);
        menuBar->addAction(paste3Action);
        menuBar->addAction(cleareAllAction);
        menuBar->addAction(swapAction);

        connect(copy3Action, &QAction::triggered, this, [this]() {
            copy.copyThreeMatricesToClipboard(matrixATable, matrixBTable, matrixCTable);
        });
        connect(paste3Action, &QAction::triggered, this, [this]() {
            insert.insertThreeMatrices(matrixATable, matrixBTable, matrixCTable);
        });
        connect(cleareAllAction, &QAction::triggered, this, [this]() {
            clean.clearMatrices(matrixATable);
            clean.clearMatrices(matrixBTable);
            clean.clearMatrices(matrixCTable);
        });
        connect(swapAction, &QAction::triggered, this, [this]() {
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

        menuBar->exec(CentralWidget->mapToGlobal(pos));
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
        // Check if the pointer is not null before deleting
        if (qicons[i]) {
            delete qicons[i];
        }
    }
}

// Функция для определения темы
bool Matrix_Calculator::isDarkTheme() {
    QPalette palette = QApplication::palette();
    return palette.color(QPalette::Window).lightness() < 128;
}

// Функция для изменения цвета SVG-иконки
QIcon Matrix_Calculator::createColoredIcon(const QString &iconPath, const QColor &color) {

    QSvgRenderer renderer(iconPath);
    if (!renderer.isValid()) {
        qWarning() << "Invalid SVG file:" << iconPath;
        return QIcon(); // Возвращаем пустую иконку, если SVG некорректен
    }

    // Создаем изображение с нужным размером
    QImage image(64, 64, QImage::Format_ARGB32);
    image.fill(Qt::transparent); // Прозрачный фон

    // Рендерим SVG
    QPainter painter(&image);

    painter.setRenderHint(QPainter::Antialiasing, true);

    renderer.render(&painter, QRectF(0, 0, 64, 64)); // Убедитесь, что SVG масштабируется корректно

    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(image.rect(), color);

    // Применяем цвет ко всем непрозрачным пикселям
    for (int x = 0; x < image.width(); ++x) {
        for (int y = 0; y < image.height(); ++y) {
            QColor pixel = image.pixelColor(x, y);
            if (pixel.alpha() > 0) { // Если пиксель не полностью прозрачный
                // Сохраняем альфа-канал, применяем новый цвет
                image.setPixelColor(x, y, QColor(color.red(), color.green(), color.blue(), pixel.alpha()));
            }
        }
    }

    QImage scaledImage = image.scaled(64, 64, Qt::KeepAspectRatio, Qt::FastTransformation);
    return QIcon(QPixmap::fromImage(scaledImage));

}

void Matrix_Calculator::updateIcons(QIcon *icon, QPushButton *button, const QString &iconPath) {
    QColor iconColor = isDarkTheme() ? Qt::white : Qt::black;

    if (!icon || !button) {
        qWarning() << "Warning: Invalid icon or button for iconPath" << iconPath;
        return;
    }

    *icon = createColoredIcon(iconPath, iconColor);
    button->setIcon(*icon);
    button->setIconSize(QSize(128, 128));
}

void Matrix_Calculator::onPaletteChanged() {
    QColor iconColor = isDarkTheme() ? Qt::white : Qt::black;

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

    // Обновляем проблемные иконки
    updateIcons(transposeAIcon, transposeAButton, ":/Icons/A-transpose.svg");
    updateIcons(inverseAIcon, inverseAButton, ":/Icons/A-inverse.svg");
    updateIcons(transposeBIcon, transposeBButton, ":/Icons/B-transpose.svg");
    updateIcons(inverseBIcon, inverseBButton, ":/Icons/B-inverse.svg");
    updateIcons(AmultyplybyC, multyplyConstantA, ":/Icons/multiplyC.svg");
    updateIcons(AsubstractbyC, divideConstantA, ":/Icons/divC.svg");
    updateIcons(BmultyplybyC, multyplyConstantB, ":/Icons/multiplyC.svg");
    updateIcons(BsubstractbyC, divideConstantB, ":/Icons/divC.svg");
}

void Matrix_Calculator::setupMatrix(
    QVBoxLayout *&MainLayout,
    QHBoxLayout *&MatricesLayout,
    QWidget *&MatricesWidget,
    QWidget *&SizeWidget,
    QHBoxLayout *&SizeLayout,
    QVBoxLayout *&MatrixLayout,
    QTableWidget*& MatrixTable,
    QSpinBox*& rowsSpinBox,
    QSpinBox*& colsSpinBox,
    QPushButton*& CreateMatrix,
    QPushButton*& transposeMatrix,
    QPushButton*& inverseMatrix,
    QPushButton*& multiplyByC,
    QPushButton*& divisionByC,
    QLineEdit*& constant,
    QWidget *&matrixButtonsWidget,
    QHBoxLayout *&matrixButtonsLayout,
    QLabel *Rangtext, QLabel *&Rangvalue, QPushButton*& RangButton,
    const std::string& name)
{
    rowsSpinBox = new QSpinBox();
    colsSpinBox = new QSpinBox();

    MatrixTable->setToolTip(QString::fromStdString(name));
    MatrixTable->setContextMenuPolicy(Qt::CustomContextMenu);

    // Connect the custom context menu signal
    connect(MatrixTable, &QTableWidget::customContextMenuRequested, this, [this, MatrixTable](const QPoint &pos) {

        QMenu contextMenu(tr("Меню выбора"), this);

        QAction *copyAction = new QAction(tr("Скопировать"), this);
        QAction *pasteAction = new QAction(tr("Вставить"), this);
        QAction *clearAction = new QAction(tr("Очистить"), this);
        QAction *addOneMatrixAction = new QAction(tr("Вставить единичную матрицу"), this);
        QAction *addUpTriangleAction = new QAction(tr("Вставить верхнюю треугольную матрицу"), this);
        QAction *addDownTriangleAction = new QAction(tr("Вставить нижнюю треугольную матрицу"), this);

        contextMenu.addAction(copyAction);
        contextMenu.addAction(pasteAction);
        contextMenu.addAction(clearAction);
        contextMenu.addSeparator();
        contextMenu.addAction(addOneMatrixAction);
        contextMenu.addAction(addUpTriangleAction);
        contextMenu.addAction(addDownTriangleAction);

        connect(copyAction, &QAction::triggered, this, [this, MatrixTable]() {
            copy.copy(MatrixTable);
        });

        connect(pasteAction, &QAction::triggered, this, [this, MatrixTable]() {
            insert.insert(MatrixTable);
        });

        connect(clearAction, &QAction::triggered, this, [this, MatrixTable]() {
            clean.clearMatrices(MatrixTable);
        });

        connect(addOneMatrixAction, &QAction::triggered, this, [this, MatrixTable]() {
            matr.BasicOneMatrix(MatrixTable, MatrixTable->rowCount(), MatrixTable->columnCount());
        });

        connect(addUpTriangleAction, &QAction::triggered, this, [this, MatrixTable]() {
            matr.BasicUpTriangleMatrix(MatrixTable, MatrixTable->rowCount(), MatrixTable->columnCount());
        });
        connect(addDownTriangleAction, &QAction::triggered, this, [this, MatrixTable]() {
            matr.BasicDownTriangleMatrix(MatrixTable, MatrixTable->rowCount(), MatrixTable->columnCount());
        });

        contextMenu.exec(MatrixTable->mapToGlobal(pos));
    });

    rowsSpinBox->setRange(1, 10);
    rowsSpinBox->setValue(3);

    colsSpinBox->setRange(1, 10);
    colsSpinBox->setValue(3);

    SizeLayout->addWidget(rowsSpinBox);
    SizeLayout->addWidget(colsSpinBox);
    SizeLayout->addWidget(CreateMatrix);
    SizeLayout->setAlignment(Qt::AlignLeft);

    MatrixLayout->addLayout(SizeLayout);
    MatrixLayout->addWidget(MatrixTable);  // FIXED: Was using matrixATable instead of MatrixTable

    connect(RangButton, &QPushButton::clicked, this, [this, MatrixTable, Rangvalue]() {
        Rangvalue->setText(QString::number(oper.FindRang(MatrixTable)));
    });

    matrixButtonsLayout->addWidget(transposeMatrix);
    matrixButtonsLayout->addWidget(inverseMatrix);
    matrixButtonsLayout->addWidget(multiplyByC);
    matrixButtonsLayout->addWidget(divisionByC);
    matrixButtonsLayout->addWidget(constant);
    matrixButtonsLayout->addWidget(Rangtext);
    matrixButtonsLayout->addWidget(Rangvalue);
    matrixButtonsLayout->addWidget(RangButton);
    matrixButtonsLayout->addStretch();
    MatrixLayout->addWidget(matrixButtonsWidget);

    MatricesLayout->addWidget(SizeWidget);
    MainLayout->addWidget(MatricesWidget);

    qDebug() << "LOL";
};


