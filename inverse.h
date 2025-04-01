#ifndef INVERSE_H
#define INVERSE_H

#include <QObject>
#include <QMessageBox>
#include <QTableWidget>


class inverse : public QObject
{
    Q_OBJECT
public:
    inverse(QObject *parent = nullptr);
public slots:
    void invertMatrix(QTableWidget *table);
};

#endif // INVERSE_H
