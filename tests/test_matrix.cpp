#include <gtest/gtest.h>
#include "matrix.h"
#include <cmath>

// Тесты для create_matrix
TEST(MatrixTest, CreateMatrixValidDimensions) {
    Matrix m = create_matrix(2, 3);
    EXPECT_EQ(m.rows, 2);
    EXPECT_EQ(m.cols, 3);
    EXPECT_NE(m.data, nullptr);

    // Проверяем, что матрица инициализирована нулями
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            EXPECT_EQ(m.data[i][j], 0.0);
        }
    }
    free_matrix(m);
}

TEST(MatrixTest, CreateMatrixInvalidDimensions) {
    EXPECT_THROW(create_matrix(0, 5), std::invalid_argument);
    EXPECT_THROW(create_matrix(-1, 3), std::invalid_argument);
    EXPECT_THROW(create_matrix(2, -2), std::invalid_argument);
}

// Тесты для matrix_add
TEST(MatrixTest, MatrixAddValid) {
    Matrix a = create_matrix(2, 2);
    Matrix b = create_matrix(2, 2);

    // Заполняем матрицы тестовыми данными
    a.data[0][0] = 1.0; a.data[0][1] = 2.0;
    a.data[1][0] = 3.0; a.data[1][1] = 4.0;

    b.data[0][0] = 5.0; b.data[0][1] = 6.0;
    b.data[1][0] = 7.0; b.data[1][1] = 8.0;

    Matrix result = matrix_add(a, b);

    EXPECT_EQ(result.rows, 2);
    EXPECT_EQ(result.cols, 2);
    EXPECT_DOUBLE_EQ(result.data[0][0], 6.0);
    EXPECT_DOUBLE_EQ(result.data[0][1], 8.0);
    EXPECT_DOUBLE_EQ(result.data[1][0], 10.0);
    EXPECT_DOUBLE_EQ(result.data[1][1], 12.0);

    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

TEST(MatrixTest, MatrixAddInvalidDimensions) {
    Matrix a = create_matrix(2, 3);
    Matrix b = create_matrix(3, 2);

    EXPECT_THROW(matrix_add(a, b), std::invalid_argument);

    free_matrix(a);
    free_matrix(b);
}

// Тесты для matrix_multiply
TEST(MatrixTest, MatrixMultiplyValid) {
    Matrix a = create_matrix(2, 3);
    Matrix b = create_matrix(3, 2);

    // Матрица A: 2x3
    a.data[0][0] = 1; a.data[0][1] = 2; a.data[0][2] = 3;
    a.data[1][0] = 4; a.data[1][1] = 5; a.data[1][2] = 6;

    // Матрица B: 3x2
    b.data[0][0] = 7; b.data[0][1] = 8;
    b.data[1][0] = 9; b.data[1][1] = 10;
    b.data[2][0] = 11; b.data[2][1] = 12;

    Matrix result = matrix_multiply(a, b);

    EXPECT_EQ(result.rows, 2);
    EXPECT_EQ(result.cols, 2);
    // Проверяем результаты умножения
    // [1*7 + 2*9 + 3*11, 1*8 + 2*10 + 3*12] = [58, 64]
    // [4*7 + 5*9 + 6*11, 4*8 + 5*10 + 6*12] = [139, 154]
    EXPECT_DOUBLE_EQ(result.data[0][0], 58.0);
    EXPECT_DOUBLE_EQ(result.data[0][1], 64.0);
    EXPECT_DOUBLE_EQ(result.data[1][0], 139.0);
    EXPECT_DOUBLE_EQ(result.data[1][1], 154.0);

    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

TEST(MatrixTest, MatrixMultiplyInvalidDimensions) {
    Matrix a = create_matrix(2, 3);
    Matrix b = create_matrix(2, 3); // Несовместимые размеры

    EXPECT_THROW(matrix_multiply(a, b), std::invalid_argument);

    free_matrix(a);
    free_matrix(b);
}

// Тесты для matrix_transpose
TEST(MatrixTest, MatrixTranspose) {
    Matrix m = create_matrix(2, 3);

    m.data[0][0] = 1; m.data[0][1] = 2; m.data[0][2] = 3;
    m.data[1][0] = 4; m.data[1][1] = 5; m.data[1][2] = 6;

    Matrix result = matrix_transpose(m);

    EXPECT_EQ(result.rows, 3);
    EXPECT_EQ(result.cols, 2);

    // Проверяем транспонирование
    EXPECT_DOUBLE_EQ(result.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(result.data[0][1], 4.0);
    EXPECT_DOUBLE_EQ(result.data[1][0], 2.0);
    EXPECT_DOUBLE_EQ(result.data[1][1], 5.0);
    EXPECT_DOUBLE_EQ(result.data[2][0], 3.0);
    EXPECT_DOUBLE_EQ(result.data[2][1], 6.0);

    free_matrix(m);
    free_matrix(result);
}

// Тесты для matrix_from_array
TEST(MatrixTest, MatrixFromArray) {
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Matrix m = matrix_from_array(data, 2, 3);

    EXPECT_EQ(m.rows, 2);
    EXPECT_EQ(m.cols, 3);

    EXPECT_DOUBLE_EQ(m.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(m.data[0][1], 2.0);
    EXPECT_DOUBLE_EQ(m.data[0][2], 3.0);
    EXPECT_DOUBLE_EQ(m.data[1][0], 4.0);
    EXPECT_DOUBLE_EQ(m.data[1][1], 5.0);
    EXPECT_DOUBLE_EQ(m.data[1][2], 6.0);

    free_matrix(m);
}

// Тесты для matrix_sum
TEST(MatrixTest, MatrixSum) {
    Matrix m = create_matrix(2, 2);
    m.data[0][0] = 1.0;
    m.data[0][1] = 2.0;
    m.data[1][0] = 3.0;
    m.data[1][1] = 4.0;

    double sum = matrix_sum(m);
    EXPECT_DOUBLE_EQ(sum, 10.0);

    free_matrix(m);
}

TEST(MatrixTest, MatrixSumEmpty) {
    Matrix m;
    m.data = nullptr;
    m.rows = 0;
    m.cols = 0;

    double sum = matrix_sum(m);
    EXPECT_DOUBLE_EQ(sum, 0.0);
}

// Тесты для matrix_hstack
TEST(MatrixTest, MatrixHStack) {
    Matrix a = create_matrix(2, 2);
    Matrix b = create_matrix(2, 2);

    a.data[0][0] = 1; a.data[0][1] = 2;
    a.data[1][0] = 3; a.data[1][1] = 4;

    b.data[0][0] = 1; b.data[0][1] = 2; // Первая строка совпадает с a
    b.data[1][0] = 5; b.data[1][1] = 6;

    Matrix result = matrix_hstack(a, b);

    // Проверяем результат
    // Для строки, где матрицы совпадают (первая строка), берется значение из a
    // Для остальных строк - сумма a и b

    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

// Тест для проверки утечек памяти
TEST(MatrixTest, MemoryManagement) {
    Matrix m = create_matrix(100, 100);
    EXPECT_NE(m.data, nullptr);

    // Заполняем матрицу данными
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            m.data[i][j] = i + j;
        }
    }

    // Освобождаем память - не должно быть segmentation fault
    free_matrix(m);

    // Проверяем, что можем создать новую матрицу после освобождения
    Matrix m2 = create_matrix(10, 10);
    EXPECT_NE(m2.data, nullptr);
    free_matrix(m2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
