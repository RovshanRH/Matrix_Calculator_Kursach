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
#include <QTranslator>
#include <QSettings>
#include <cmath>
#include "cleaner.h"
#include "helpwindow.h"
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
    void setupMatrix(
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
        QLabel* Rangtext,
        QLabel *&Rangvalue, QPushButton *&RangButton,
        const std::string& name);

private:
    bool isDarkTheme();
    QIcon createColoredIcon(const QString &iconPath, const QColor &color);
    void updateIcons(QIcon *icon, QPushButton *button, const QString &iconPath);

    bool changePaletteAndTextValue = false;
    QPalette newPalette;

    QSpinBox *rowsASpinBox;
    QSpinBox *colsASpinBox;
    QSpinBox *rowsBSpinBox;
    QSpinBox *colsBSpinBox;
    // QSpinBox *rowsCSpinBox;
    // QSpinBox *colsCSpinBox;
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
    HelpWindow helpi;
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
    QIcon *glassesIcon;
    QIcon *transposeAIcon, *transposeBIcon, *inverseAIcon, *inverseBIcon, *AmultyplybyC, *AsubstractbyC, *BmultyplybyC, *BsubstractbyC;
    QIcon *multiply, *summarize, *substract;
    QPushButton *CopyMatrixA, * InsertMatrixA, * CopyMatrixB, * InsertMatrixB, * CopyMatrixC,  * sizeButton, * copymatrices, * insertmatrices, * swapmatrixAB, * CreateMatrixA, * CreateMatrixB,
        * summButton, * raznButton, * multiplyButton, * clearButton, * randomButton, * transposeAButton, * inverseAButton, * multyplyConstantA, * divideConstantA, * transposeBButton, * inverseBButton,
        * multyplyConstantB, * divideConstantB, *glassesButton;

    QTranslator translator;
    QPushButton *changeLang;
    QIcon* changeLangIcon;
    void loadlanguage(const QString &language);
    void updateUITexts();
    void retranslateUi();

    QPushButton *help;
    QLabel *RangBLabel;
    QLabel *RangeBValue;
    QPushButton* RangBButton;
    QLabel *RangALabel;
    QLabel *RangeAValue;
    QPushButton* RangAButton;


private slots:
    void onPaletteChanged();
    // void changeLanguage(const QString &language);
    void changePaletteAndText();


};

#endif // MATRIX_CALCULATOR_H
