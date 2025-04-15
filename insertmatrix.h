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
};

#endif // INSERTMATRIX_H
