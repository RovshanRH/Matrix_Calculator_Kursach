#ifndef CLEANER_H
#define CLEANER_H

#include <QObject>
#include <QTableWidget>

class Cleaner : public QObject
{
    Q_OBJECT
public:
    explicit Cleaner(QObject *parent = nullptr);
public slots:
    void clearMatrices(QTableWidget* matrix);
    void clearMatrixA();
    void clearMatrixB();
    void clearMatrixC();
};

#endif // CLEANER_H
