#include "helpwindow.h"
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

    QTextStream in(&file);
    textBrowser->setHtml(in.readAll());
    file.close();
}

// void HelpWindow::loadHelpRus() {
//     loadHtmlFile(":/Icons/help.html");
// }
// void HelpWindow::loadHelpEng() {
//     loadHtmlFile(":/Icons/help_en.html");
// }
// void HelpWindow::loadHelpFra() {
//     loadHtmlFile(":/Icons/help_fr.html");
// }
