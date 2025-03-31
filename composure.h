// composure.h
#ifndef COMPOSURE_H
#define COMPOSURE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QIcon>
#include <QFont>

class Composure {
public:
    static QWidget* createHeaderWidget() {
        // Create widget for the header section
        QWidget *headerWidget;
        QHBoxLayout *headerHLayout = new QHBoxLayout();
        QVBoxLayout *headerVLayout = new QVBoxLayout(headerWidget);

        // Icon label
        QLabel *iconLabel = new QLabel();
        iconLabel->setAlignment(Qt::AlignLeft);
        QIcon *icon = new QIcon(":/Icons/Icon.png");
        iconLabel->setPixmap(icon->pixmap(50, 50));
        headerHLayout->addWidget(iconLabel);

        // Title label
        QLabel *titleLabel = new QLabel("Калькулятор матриц");
        QFont font = titleLabel->font();
        font.setPointSize(20);
        titleLabel->setFont(font);
        headerHLayout->addWidget(titleLabel);

        // Version label
        QLabel *versionLabel = new QLabel("v1.0.0");
        headerHLayout->addWidget(versionLabel);
        headerHLayout->addStretch();

        // Add horizontal layout to vertical layout
        headerVLayout->addLayout(headerHLayout);

        // Add horizontal line
        auto horizontalLine = new QFrame;
        horizontalLine->setFrameShape(QFrame::HLine);
        horizontalLine->setFrameShadow(QFrame::Sunken);
        headerVLayout->addWidget(horizontalLine);
        headerVLayout->addStretch();

        return headerWidget;
    }
};

#endif // COMPOSURE_H
