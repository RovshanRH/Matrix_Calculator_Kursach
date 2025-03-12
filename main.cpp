#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QIcon>
#include <QVector>
#include <QFrame>
#include <cmath>
#include <random>
using namespace std;

class Matrix_Calculator : public QMainWindow {
public:
    Matrix_Calculator(QWidget *parent = nullptr) : QMainWindow(parent)
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

        hlayout->addWidget(new QLabel("Калькулятор матриц"));
        QLabel *version = new QLabel("v1.0.0");
        version->setAlignment(Qt::AlignRight);
        hlayout->addWidget(version);
        vlayout->addLayout(hlayout);
        auto lineA = new QFrame;
        lineA->setFrameShape(QFrame::HLine);
        lineA->setFrameShadow(QFrame::Sunken);
        vlayout->addWidget(lineA);
        vlayout->addStretch();
        MainLayout->addWidget(vlayoutWidget);

        // Матрица А
        QWidget* SizeMatrixA = new QWidget();
        QHBoxLayout* SizeLayoutA = new QHBoxLayout(SizeMatrixA);

        QWidget *matrixAWidget = new QWidget();
        QVBoxLayout *matrixALayout = new QVBoxLayout(matrixAWidget);
        QLabel *matrixALabel = new QLabel("Матрица A:");
        matrixATable = new QTableWidget();
        matrixALayout->addWidget(matrixALabel);
        matrixALayout->addWidget(matrixATable);

        // Кнопки для настройки размера матрицы А
        // Строки
        QLabel *StrokiALabel = new QLabel("Строки A: ");
        rowsASpinBox = new QSpinBox();
        rowsASpinBox->setRange(0, 5);
        rowsASpinBox->setValue(3);

        // Столбцы
        QLabel *StolbciALabel = new QLabel("Столбцы A: ");
        colsASpinBox = new QSpinBox();
        colsASpinBox->setRange(0, 5);
        colsASpinBox->setValue(3);

        QPushButton *CreateMatrixA = new QPushButton("Поменять размер");

        SizeLayoutA->addWidget(StrokiALabel);
        SizeLayoutA->addWidget(rowsASpinBox);
        SizeLayoutA->addWidget(StolbciALabel);
        SizeLayoutA->addWidget(colsASpinBox);
        SizeLayoutA->addWidget(CreateMatrixA);
        SizeLayoutA->addStretch();
        MainLayout->addWidget(SizeMatrixA);

        // Кнопки для матрицы А
        QWidget *matrixAButtonsWidget = new QWidget();
        QHBoxLayout *matrixAButtonsLayout = new QHBoxLayout(matrixAButtonsWidget);
        QPushButton *transposeAButton = new QPushButton("Транспонировать A");
        QPushButton *inverseAButton = new QPushButton("Обратная A⁻¹");
        matrixAButtonsLayout->addWidget(transposeAButton);
        matrixAButtonsLayout->addWidget(inverseAButton);
        matrixAButtonsLayout->addStretch();
        matrixALayout->addWidget(matrixAButtonsWidget);

        // Матрица B
        QWidget* SizeMatrixB = new QWidget();
        // QHBoxLayout* SizeLayoutB = new QHBoxLayout(SizeMatrixB);

        QWidget *matrixBWidget = new QWidget();
        QVBoxLayout *matrixBLayout = new QVBoxLayout(matrixBWidget);
        QLabel *matrixBLabel = new QLabel("Матрица B:");
        matrixBTable = new QTableWidget();
        matrixBLayout->addWidget(matrixBLabel);
        matrixBLayout->addWidget(matrixBTable);

        // Кнопки для настройки размера матрицы B
        // Строки
        QLabel *StrokiBLabel = new QLabel("Строки B: ");
        rowsBSpinBox = new QSpinBox();
        rowsBSpinBox->setRange(0, 5);
        rowsBSpinBox->setValue(3);

        // Столбцы
        QLabel *StolbciBLabel = new QLabel("Столбцы B: ");
        colsBSpinBox = new QSpinBox();
        colsBSpinBox->setRange(0, 5);
        colsBSpinBox->setValue(3);

        QPushButton *CreateMatrixB = new QPushButton("Поменять размер");

        SizeLayoutA->addWidget(StrokiBLabel);
        SizeLayoutA->addWidget(rowsBSpinBox);
        SizeLayoutA->addWidget(StolbciBLabel);
        SizeLayoutA->addWidget(colsBSpinBox);
        SizeLayoutA->addWidget(CreateMatrixB);
        SizeLayoutA->addStretch();
        MainLayout->addWidget(SizeMatrixB);

        // Кнопки для матрицы B
        QWidget *matrixBButtonsWidget = new QWidget();
        QHBoxLayout *matrixBButtonsLayout = new QHBoxLayout(matrixBButtonsWidget);
        QPushButton *transposeBButton = new QPushButton("Транспонировать B");
        QPushButton *inverseBButton = new QPushButton("Обратная B⁻¹");
        matrixBButtonsLayout->addWidget(transposeBButton);
        matrixBButtonsLayout->addWidget(inverseBButton);
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
        QPushButton* randomButton = new QPushButton("Добавить рандомные числа в матрицы A B");

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
        QHBoxLayout* SizeLayoutC = new QHBoxLayout(SizeMatrixC);

        QWidget* matrixCWidget = new QWidget();
        QVBoxLayout* matrixCLayout = new QVBoxLayout(matrixCWidget);
        QLabel* matrixCLabel = new QLabel("Матрица С:");
        matrixCTable = new QTableWidget();
        matrixCLayout->addWidget(matrixCLabel);
        matrixCLayout->addWidget(matrixCTable);

        // Кнопки для настройки размера матрицы С
        // Строки
        QLabel *StrokiCLabel = new QLabel("Строки С: ");
        rowsCSpinBox = new QSpinBox();
        rowsCSpinBox->setRange(1, 5);
        rowsCSpinBox->setValue(3);

        // Столбцы
        QLabel *StolbciCLabel = new QLabel("Столбцы С: ");
        colsCSpinBox = new QSpinBox();
        colsCSpinBox->setRange(1, 5);
        colsCSpinBox->setValue(3);

        QPushButton *CreateMatrixC = new QPushButton("Поменять размер");

        SizeLayoutC->addWidget(StrokiCLabel);
        SizeLayoutC->addWidget(rowsCSpinBox);
        SizeLayoutC->addWidget(StolbciCLabel);
        SizeLayoutC->addWidget(colsCSpinBox);
        SizeLayoutC->addWidget(CreateMatrixC);
        SizeLayoutC->addStretch();
        MainLayout->addWidget(SizeMatrixC);

        MainLayout->addWidget(matrixCWidget);



        // соединение сигналов и слотов
        //...
        connect(CreateMatrixA, &QPushButton::clicked, this, &Matrix_Calculator::createMatrixA);
        connect(CreateMatrixB, &QPushButton::clicked, this, &Matrix_Calculator::createMatrixB);
        connect(CreateMatrixC, &QPushButton::clicked, this, &Matrix_Calculator::createMatrixC);
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
        // connect(inverseAButton, &QPushButton::clicked, this, &Matrix_Calculator::invertMatrixA);
        // connect(inverseBButton, &QPushButton::clicked, this, &Matrix_Calculator::invertMatrixB);



        createMatrices();

    }
private slots:
    void createMatrices() {
        createMatrixA();
        createMatrixB();
        createMatrixC();
    }
    void createMatrixA()
    {
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

    void clearMatrices(QTableWidget* matrix) {
        int rows = matrix->rowCount();
        int cols = matrix->columnCount();

        for (int i{}; i < rows; i++) {
            for (int j{}; j < cols; j++) {
                matrix->item(i, j)->setText(QString::number(0));
            }
        }
    }
    void clearMatrixA() {
        clearMatrices(matrixATable);
    }
    void clearMatrixB() {
        clearMatrices(matrixBTable);
    }
    void clearMatrixC() {
        clearMatrices(matrixCTable);
    }

    void createMatrixB()
    {
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
    void createMatrixC()
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
    void addMatrices()
    {
        int rows = matrixATable->rowCount();
        int cols = matrixATable->columnCount();

        if (rows != matrixBTable->rowCount() || cols != matrixBTable->columnCount()) {
            QMessageBox::warning(this, "Ошибка", "Размеры матриц должны совпадать!");
            return;
        }
        for (int i {}; i < rows; i++) {
            for (int j {}; j < cols; j++) {
                double valueA = matrixATable->item(i, j)->text().toDouble();
                double valueB = matrixBTable->item(i, j)->text().toDouble();
                double result = valueA + valueB;
                matrixCTable->item(i, j)->setText(QString::number(result));
            }
        }
    }
    void subtractMatrices()
    {
        int rows = matrixATable->rowCount();
        int cols = matrixATable->columnCount();

        if (rows != matrixBTable->rowCount() || cols != matrixBTable->columnCount()) {
            QMessageBox::warning(this, "Ошибка", "Размеры матриц должны совпадать!");
            return;
        }
        for (int i {}; i < rows; i++) {
            for (int j {}; j < cols; j++) {
                double valueA = matrixATable->item(i, j)->text().toDouble();
                double valueB = matrixBTable->item(i, j)->text().toDouble();
                double result = valueA - valueB;
                matrixCTable->item(i, j)->setText(QString::number(result));
            }
        }
    }

    void multyplyMatrices()
    {
        int rows = matrixATable->rowCount();
        int cols = matrixATable->columnCount();

        if (rows != matrixBTable->columnCount() || cols != matrixBTable->rowCount()) {
            QMessageBox::warning(this, "Ошибка", "Размеры матриц должны совпадать!");
            return;
        }
        for (int i {}; i < rows; i++) {
            for (int j {}; j < cols; j++) {
                // double valueA = matrixATable->item(i, j)->text().toDouble();
                // double valueB = matrixBTable->item(i, j)->text().toDouble();
                // double result = valueA*valueB;
                // matrixCTable->item(i, j)->setText(QString::number(result));
                double valueA1 = matrixATable->item(i, j)->text().toDouble();
                double valueA2 = matrixATable->item(i, j)->text().toDouble();
                double valueB1 = matrixBTable->item(j, i)->text().toDouble();
                double valueB2 = matrixBTable->item(j, i)->text().toDouble();
                double result = valueA1*valueB1 + valueA2*valueB2;
                matrixCTable->item(i, j)->setText(QString::number(result));
            }
        }
    }

    // добавить функцию для обратной матрицы

    void transposeMatrix(QTableWidget *matrix)
    {
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
    void transposeMatrixA() {
        transposeMatrix(matrixATable);
    }
    void transposeMatrixB() {
        transposeMatrix(matrixBTable);
    }
    void randomizeMatrices(QTableWidget *matrix) {
        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<> number(0, 100);

        int rows = matrix->rowCount();
        int cols = matrix->columnCount();

        for (int i{}; i < rows; i++) {
            for (int j{}; j < cols; j++) {
                matrix->item(i, j)->setText(QString::number(number(gen)));
            }
        }
    }
    void randomizeMatrixA() {
        randomizeMatrices(matrixATable);
    }
    void randomizeMatrixB() {
        randomizeMatrices(matrixBTable);
    }
private:
    QSpinBox *rowsASpinBox;
    QSpinBox *colsASpinBox;
    QSpinBox *rowsBSpinBox;
    QSpinBox *colsBSpinBox;
    QSpinBox *rowsCSpinBox;
    QSpinBox *colsCSpinBox;
    QTableWidget *matrixATable;
    QTableWidget *matrixBTable;
    QTableWidget *matrixCTable;
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Matrix_Calculator calc;
    calc.setWindowIcon(QIcon(":/Icons/Icon.png"));
    calc.show();
    return app.exec();
}
