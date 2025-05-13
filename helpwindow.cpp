#include "helpwindow.h"
#include "qapplication.h"
#include <QFile>
#include <QTextStream>

HelpWindow::HelpWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Помощь");
    setMinimumSize(900, 680);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    textBrowser = new QTextBrowser(this);
    mainLayout->addWidget(textBrowser);

    loadHtmlFile(":/Icons/help.html");
}

HelpWindow::~HelpWindow() {}

void HelpWindow::loadHtmlFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        textBrowser->setPlainText("Ошибка: Не удалось открыть HTML-файл.");
        return;
    }

    // connect(qApp, &QApplication::paletteChanged, this, &HelpWindow::ChangeColorTheme);

    QTextStream in(&file);
    textBrowser->setHtml(in.readAll());
    file.close();
}

bool isDarkTheme() {
    QPalette palette = QApplication::palette();
    return palette.color(QPalette::Window).lightness() < 128;
}

void HelpWindow::ChangeColorTheme() {
    bool dark = isDarkTheme();
    QPalette newPalette = QPalette();
    if (!dark) {
        newPalette.setColor(QPalette::Window, QColor(255, 255, 255)); // Яркий белый фон
        newPalette.setColor(QPalette::Text, Qt::black);
    } else {
        newPalette.setColor(QPalette::Window, QColor(0, 0, 0)); // Яркий белый фон
        newPalette.setColor(QPalette::Text, Qt::white);
    }
}
