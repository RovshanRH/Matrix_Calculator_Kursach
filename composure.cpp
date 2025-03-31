#include "composure.h"
#include <QMainWindow>
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

composure::composure(QWidget *parent) : QMainWindow(parent) {
    QWidget *headerWidget = new QWidget();
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
}
