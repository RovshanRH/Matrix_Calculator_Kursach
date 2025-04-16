#include <QApplication>
#include <QIcon>
#include "matrix_calculator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Matrix_Calculator calc;
    calc.setWindowIcon(QIcon(":/Icons/Icon.png"));
    app.setOrganizationName("Rovian");              // имя компании
    app.setOrganizationDomain("https://github.com/RovshanRH");       // домен компании
    app.setApplicationName("Matrix Calculator");     // имя приложения
    app.setApplicationVersion("1.0.0");             // версия приложения
    calc.show();
    return app.exec();
}
