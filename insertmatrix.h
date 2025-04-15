#ifndef INSERTMATRIX_H
#define INSERTMATRIX_H

#include <QObject>
#include <QApplication>
#include <QTableWidget>
#include <QClipboard>
#include <QStringList>

class insertmatrix : public QObject
{
    Q_OBJECT
public:
    insertmatrix(QObject *parent = nullptr);
public slots:
    void insert(QTableWidget* matrix);
    void insertThreeMatrices(QTableWidget *table1, QTableWidget *table2, QTableWidget *table3);
};

#endif // INSERTMATRIX_H
