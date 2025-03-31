#include "stabilizingcsize.h"
#include "matrix_calculator.h"

stabilizingCsize::stabilizingCsize(QWidget *parent) : Matrix_Calculator(parent) {}

void stabilizingCsize::stabilizeSum(int rows, int cols) {

    // rowsCSpinBox->setValue(rows);
    // colsCSpinBox->setValue(cols);
    set_CSpinBox(rows, cols);
    createMatrixC();

    for (int i {}; i < rows; i++) {
        for (int j {}; j < cols; j++) {
            double valueA = set_double_value_A(i, j);
            double valueB = set_double_value_B(i, j);
            double result = valueA + valueB;
            // matrixCTable->item(i, j)->setText(QString::number(result));
            set_text_value_C(i, j, result);
        }
    }
}
void stabilizingCsize::stabilizeSub(int rows, int cols) {

    set_CSpinBox(rows, cols);
    createMatrixC();

    for (int i {}; i < rows; i++) {
        for (int j {}; j < cols; j++) {
            double valueA = set_double_value_A(i, j);
            double valueB = set_double_value_B(i, j);
            double result = valueA - valueB;
            set_text_value_C(i, j, result);
        }
    }
}

void stabilizingCsize::stabilizeUmno(int rows, int cols) {
    set_CSpinBox(rows, cols);
    createMatrixC();

    for (int i {}; i < rows; i++) {
        for (int j {}; j < cols; j++) {
            double result = 0;
            for (int x{}; x < cols; x++) {
                double valueA = set_double_value_A(i, j);
                double valueB = set_double_value_B(i, j);
                result = result + (valueA*valueB);
            }
             set_text_value_C(i, j, result);
        }
    }
}
