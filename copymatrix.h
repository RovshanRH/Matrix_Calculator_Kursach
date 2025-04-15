#ifndef COPYMATRIX_H
#define COPYMATRIX_H

#include <QObject>
#include <QApplication>
#include <QTableWidget>
#include <QClipboard>
#include <QStringList>
#include <vector>

class copymatrix : public QObject
{
    Q_OBJECT
public:
    explicit copymatrix(QObject *parent = nullptr);
    void copy(QTableWidget *matrix);
    void copyThreeMatricesToClipboard(QTableWidget* table1, QTableWidget* table2, QTableWidget* table3);

signals:

};

#endif // COPYMATRIX_H
