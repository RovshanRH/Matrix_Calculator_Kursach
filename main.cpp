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

        QWidget *razmerButtonWidget = new QWidget();
        QHBoxLayout *razmerButtonLayout = new QHBoxLayout(razmerButtonWidget);

        QPushButton* sizeButton = new QPushButton("Установить одинаковый размер X для матриц");
        QLabel *razmer = new QLabel("X :");
        razmerSpinBox = new QSpinBox();
        razmerSpinBox->setRange(1,10);
        razmerSpinBox->setValue(3);
        sizeButton->setFixedSize(500, 30);
        razmerButtonLayout->setAlignment(Qt::AlignHCenter);
        razmerButtonLayout->addWidget(sizeButton);
        razmerButtonLayout->addWidget(razmer);
        razmerButtonLayout->addWidget(razmerSpinBox);
        // razmerButtonLayout->addStretch();
        // sizeButtonLayout->addWidget(razmer);
        // sizeButtonLayout->addWidget(razmerSpinBox);
        // sizeButtonLayout->addStretch();

        MainLayout->addWidget(vlayoutWidget);
        MainLayout->addWidget(razmerButtonWidget);

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
        rowsASpinBox->setRange(1, 10);
        rowsASpinBox->setValue(3);

        // Столбцы
        QLabel *StolbciALabel = new QLabel("Столбцы A: ");
        colsASpinBox = new QSpinBox();
        colsASpinBox->setRange(1, 10);
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
        QLabel* matrixCLabel = new QLabel("Результирующая матрица:");
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



        createMatrices();

    }
private slots:
    void createMatrices() {
        createMatrixA();
        createMatrixB();
        createMatrixC();
    }
    void createMatricesAB() {
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
    void clearMatrixA() {
        clearMatrices(matrixATable);
    }
    void clearMatrixB() {
        clearMatrices(matrixBTable);
    }
    void clearMatrixC() {
        clearMatrices(matrixCTable);
    }
    void addMatrices()
    {
        int rowsA = matrixATable->rowCount();
        int colsA = matrixATable->columnCount();
        int rowsB = matrixBTable->rowCount();
        int colsB = matrixBTable->columnCount();

        if (rowsA != rowsB || colsA != colsB) {
            QMessageBox::warning(this, "Ошибка", "Размеры матриц должны совпадать!");
            return;
        }

        rowsCSpinBox->setValue(rowsA);
        colsCSpinBox->setValue(colsB);
        createMatrixC();

        for (int i {}; i < rowsA; i++) {
            for (int j {}; j < colsA; j++) {
                double valueA = matrixATable->item(i, j)->text().toDouble();
                double valueB = matrixBTable->item(i, j)->text().toDouble();
                double result = valueA + valueB;
                matrixCTable->item(i, j)->setText(QString::number(result));
            }
        }
    }
    void subtractMatrices()
    {
        int rowsA = matrixATable->rowCount();
        int colsA = matrixATable->columnCount();
        int rowsB = matrixBTable->rowCount();
        int colsB = matrixBTable->columnCount();

        if (rowsA != rowsB || colsA != colsB) {
            QMessageBox::warning(this, "Ошибка", "Размеры матриц должны совпадать!");
            return;
        }

        rowsCSpinBox->setValue(rowsA);
        colsCSpinBox->setValue(colsB);
        createMatrixC();

        for (int i {}; i < rowsA; i++) {
            for (int j {}; j < colsA; j++) {
                double valueA = matrixATable->item(i, j)->text().toDouble();
                double valueB = matrixBTable->item(i, j)->text().toDouble();
                double result = valueA - valueB;
                matrixCTable->item(i, j)->setText(QString::number(result));
            }
        }
    }

    void multyplyMatrices()
    {
        int rowsA = matrixATable->rowCount();
        int colsA = matrixATable->columnCount();
        int rowsB = matrixBTable->rowCount();
        int colsB = matrixBTable->columnCount();

        if (colsA != rowsB) {
            QMessageBox::warning(this, "Ошибка", "Кол-во строк матрицы A должно совпадать с кол-во столбцов матрицы B");
            return;
        }

        rowsCSpinBox->setValue(rowsA);
        colsCSpinBox->setValue(colsB);
        createMatrixC();

        for (int i {}; i < rowsA; i++) {
            for (int j {}; j < colsB; j++) {
                double result = 0;
                for (int x{}; x < colsA; x++) {
                    double valueA = matrixATable->item(i, x)->text().toDouble();
                    double valueB = matrixBTable->item(x, j)->text().toDouble();
                    result = result + (valueA*valueB);
                }
                matrixCTable->item(i, j)->setText(QString::number(result));
            }
        }
    }



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
    QVector<QVector<double>> getMatrixFromTable(QTableWidget *table)
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

    void setMatrixToTable(QTableWidget *table, const QVector<QVector<double>> &matrix)
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

    double determinant(const QVector<QVector<double>> &matrix)
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

    QVector<QVector<double>> inverseMatrix(const QVector<QVector<double>> &matrix)
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

    void invertMatrix(QTableWidget *table)
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

    void invertMatrixA()
    {
        invertMatrix(matrixATable);
    }

    void invertMatrixB()
    {
        invertMatrix(matrixBTable);
    }
private:
    QSpinBox *rowsASpinBox;
    QSpinBox *colsASpinBox;
    QSpinBox *rowsBSpinBox;
    QSpinBox *colsBSpinBox;
    QSpinBox *rowsCSpinBox;
    QSpinBox *colsCSpinBox;
    QSpinBox *razmerSpinBox;
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
