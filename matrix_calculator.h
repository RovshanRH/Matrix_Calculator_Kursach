#ifndef MATRIX_CALCULATOR_H
#define MATRIX_CALCULATOR_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSpinBox>
#include <QVector>
#include <QMenu>
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
#include "cleaner.h"
#include "inverse.h"
#include "operations.h"
#include "randomizer.h"
#include "copymatrix.h"
#include "insertmatrix.h"
#include "matrix.h"

class Matrix_Calculator : public QMainWindow {
    Q_OBJECT
public:
    Matrix_Calculator(QWidget* parent = nullptr);
    ~Matrix_Calculator();

private:
    bool isDarkTheme();
    QIcon createColoredIcon(const QString &iconPath, const QColor &color);
    void updateIcons(QIcon *icon, QPushButton *button, const QString &iconPath);

    QSpinBox *rowsASpinBox;
    QSpinBox *colsASpinBox;
    QSpinBox *rowsBSpinBox;
    QSpinBox *colsBSpinBox;
    QSpinBox *rowsCSpinBox;
    QSpinBox *colsCSpinBox;
    QSpinBox *razmerSpinBox;
    QLineEdit *constantA;
    QLineEdit *constantB;
    QTableWidget *matrixATable;
    QTableWidget *matrixBTable;
    QTableWidget *matrixCTable;
    matrix matr;
    Cleaner clean;
    Randomizer randomizer;
    inverse inverter;
    Operations oper;
    copymatrix copy;
    insertmatrix insert;
    QIcon *appIcon;
    QIcon *copyIcon;
    QIcon *insertIcon;
    QIcon *changeSizeIcon;
    QIcon *change3SizeIcon;
    QIcon *copy3Icon;
    QIcon *insert3Icon;
    QIcon *cleanIcon;
    QIcon *randomizeIcon;
    QIcon *swapIcon;
    QIcon *transposeAIcon, *transposeBIcon, *inverseAIcon, *inverseBIcon, *AmultyplybyC, *AsubstractbyC, *BmultyplybyC, *BsubstractbyC;
    QIcon *multiply, *summarize, *substract;
    QPushButton *CopyMatrixA, * InsertMatrixA, * CopyMatrixB, * InsertMatrixB, * CopyMatrixC,  * sizeButton, * copymatrices, * insertmatrices, * swapmatrixAB, * CreateMatrixA, * CreateMatrixB,
        * summButton, * raznButton, * multiplyButton, * clearButton, * randomButton, * transposeAButton, * inverseAButton, * multyplyConstantA, * divideConstantA, * transposeBButton, * inverseBButton,
        * multyplyConstantB, * divideConstantB;
private slots:
    void onPaletteChanged();
};

#endif // MATRIX_CALCULATOR_H
