#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QVBoxLayout>

class HelpWindow : public QMainWindow
{
    Q_OBJECT
public:
    HelpWindow(QWidget* parent = nullptr);
    ~HelpWindow();
    void loadHtmlFile(const QString &filePath);

private:
    QTextBrowser *textBrowser;
};

#endif // HELPWINDOW_H
