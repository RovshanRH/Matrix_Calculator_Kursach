#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <QObject>
#include <QTableWidget>

class Randomizer : public QObject {
    Q_OBJECT
public:
    explicit Randomizer(QObject *parent = nullptr);

public slots:
    void randomizeMatrices(QTableWidget *matrix);
    void randomizeMatrixA();
    void randomizeMatrixB();
};

#endif // RANDOMIZER_H
