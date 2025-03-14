#include <QApplication>
#include <QIcon>
#include "matrix_calculator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Matrix_Calculator calc;
    calc.setWindowIcon(QIcon(":/Icons/Icon.png"));
    calc.show();
    return app.exec();
}
