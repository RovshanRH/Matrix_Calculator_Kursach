#include "randomizer.h"
#include <random>

Randomizer::Randomizer(QObject *parent) : QObject(parent) {}

void Randomizer::randomizeMatrices(QTableWidget *matrix) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> number(-100, 100);

    int rows = matrix->rowCount();
    int cols = matrix->columnCount();

    for (int i{}; i < rows; i++) {
        for (int j{}; j < cols; j++) {
            matrix->item(i, j)->setText(QString::number(number(gen)));
        }
    }
}

void Randomizer::randomizeMatrixA() {}

void Randomizer::randomizeMatrixB() {}
