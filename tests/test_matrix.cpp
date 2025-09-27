#include <gtest/gtest.h>
#include "matrix.h"

// Тесты создания и освобождения матрицы
TEST(MatrixTest, CreateAndFree) {
    Matrix m = create_matrix(2, 2);
    EXPECT_EQ(m.rows, 2);
    EXPECT_EQ(m.cols, 2);
    EXPECT_NE(m.data, nullptr);
    free_matrix(m);
}

TEST(MatrixTest, InvalidSize) {
    EXPECT_THROW(create_matrix(-1, 2), std::invalid_argument);
    EXPECT_THROW(create_matrix(2, -1), std::invalid_argument);
    EXPECT_THROW(create_matrix(0, 2), std::invalid_argument);
    EXPECT_THROW(create_matrix(2, 0), std::invalid_argument);
}

TEST(MatrixTest, CreateLargeMatrix) {
    Matrix m = create_matrix(100, 100);
    EXPECT_EQ(m.rows, 100);
    EXPECT_EQ(m.cols, 100);
    EXPECT_NE(m.data, nullptr);
    free_matrix(m);
}

// Тесты сложения матриц
TEST(MatrixTest, MatrixAddition) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_add(A, B);
    EXPECT_EQ(C.rows, 2);
    EXPECT_EQ(C.cols, 2);
    EXPECT_EQ(C.data[0][0], 6);
    EXPECT_EQ(C.data[0][1], 8);
    EXPECT_EQ(C.data[1][0], 10);
    EXPECT_EQ(C.data[1][1], 12);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

TEST(MatrixTest, MatrixAdditionInvalidSize) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(3, 3);

    EXPECT_THROW(matrix_add(A, B), std::invalid_argument);

    free_matrix(A);
    free_matrix(B);
}

TEST(MatrixTest, MatrixAdditionCommutative) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C1 = matrix_add(A, B);
    Matrix C2 = matrix_add(B, A);

    EXPECT_EQ(C1.data[0][0], C2.data[0][0]);
    EXPECT_EQ(C1.data[0][1], C2.data[0][1]);
    EXPECT_EQ(C1.data[1][0], C2.data[1][0]);
    EXPECT_EQ(C1.data[1][1], C2.data[1][1]);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C1);
    free_matrix(C2);
}

// Тесты умножения матриц
TEST(MatrixTest, MatrixMultiplication) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_multiply(A, B);
    EXPECT_EQ(C.rows, 2);
    EXPECT_EQ(C.cols, 2);
    EXPECT_EQ(C.data[0][0], 19);
    EXPECT_EQ(C.data[0][1], 22);
    EXPECT_EQ(C.data[1][0], 43);
    EXPECT_EQ(C.data[1][1], 50);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

TEST(MatrixTest, MatrixMultiplicationInvalidSize) {
    Matrix A = create_matrix(2, 3);
    Matrix B = create_matrix(2, 2);

    EXPECT_THROW(matrix_multiply(A, B), std::invalid_argument);

    free_matrix(A);
    free_matrix(B);
}

TEST(MatrixTest, MatrixMultiplicationIdentity) {
    Matrix A = create_matrix(2, 2);
    Matrix I = create_matrix(2, 2); // Identity matrix

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    I.data[0][0] = 1; I.data[0][1] = 0;
    I.data[1][0] = 0; I.data[1][1] = 1;

    Matrix C = matrix_multiply(A, I);
    EXPECT_EQ(C.data[0][0], A.data[0][0]);
    EXPECT_EQ(C.data[0][1], A.data[0][1]);
    EXPECT_EQ(C.data[1][0], A.data[1][0]);
    EXPECT_EQ(C.data[1][1], A.data[1][1]);

    free_matrix(A);
    free_matrix(I);
    free_matrix(C);
}

// Тесты транспонирования матрицы
TEST(MatrixTest, MatrixTranspose) {
    Matrix A = create_matrix(2, 3);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;

    Matrix B = matrix_transpose(A);
    EXPECT_EQ(B.rows, 3);
    EXPECT_EQ(B.cols, 2);
    EXPECT_EQ(B.data[0][0], 1);
    EXPECT_EQ(B.data[0][1], 4);
    EXPECT_EQ(B.data[1][0], 2);
    EXPECT_EQ(B.data[1][1], 5);
    EXPECT_EQ(B.data[2][0], 3);
    EXPECT_EQ(B.data[2][1], 6);

    free_matrix(A);
    free_matrix(B);
}

TEST(MatrixTest, MatrixTransposeSquare) {
    Matrix A = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    Matrix B = matrix_transpose(A);
    Matrix C = matrix_transpose(B);

    EXPECT_EQ(C.data[0][0], A.data[0][0]);
    EXPECT_EQ(C.data[0][1], A.data[0][1]);
    EXPECT_EQ(C.data[1][0], A.data[1][0]);
    EXPECT_EQ(C.data[1][1], A.data[1][1]);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

// Тесты суммы элементов матрицы
TEST(MatrixTest, MatrixSum) {
    Matrix A = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    EXPECT_DOUBLE_EQ(matrix_sum(A), 10.0);
    free_matrix(A);
}

TEST(MatrixTest, MatrixSumEmpty) {
    Matrix A = create_matrix(1, 1);
    A.data[0][0] = 0.0;
    EXPECT_DOUBLE_EQ(matrix_sum(A), 0.0);
    free_matrix(A);
}

TEST(MatrixTest, MatrixSumSingleElement) {
    Matrix A = create_matrix(1, 1);
    A.data[0][0] = 5.5;
    EXPECT_DOUBLE_EQ(matrix_sum(A), 5.5);
    free_matrix(A);
}

TEST(MatrixTest, MatrixSumLargeMatrix) {
    Matrix A = create_matrix(3, 3);
    double sum = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            A.data[i][j] = i * 3 + j + 1;
            sum += A.data[i][j];
        }
    }
    EXPECT_DOUBLE_EQ(matrix_sum(A), sum);
    free_matrix(A);
}

// Тесты создания матрицы из массива
TEST(MatrixTest, MatrixFromArray) {
    double data[] = {1, 2, 3, 4, 5, 6};
    Matrix A = matrix_from_array(data, 2, 3);

    EXPECT_EQ(A.rows, 2);
    EXPECT_EQ(A.cols, 3);
    EXPECT_EQ(A.data[0][0], 1);
    EXPECT_EQ(A.data[0][1], 2);
    EXPECT_EQ(A.data[0][2], 3);
    EXPECT_EQ(A.data[1][0], 4);
    EXPECT_EQ(A.data[1][1], 5);
    EXPECT_EQ(A.data[1][2], 6);

    free_matrix(A);
}

TEST(MatrixTest, MatrixFromArrayInvalidSize) {
    double data[] = {1, 2, 3};
    EXPECT_THROW(matrix_from_array(data, -1, 3), std::invalid_argument);
    EXPECT_THROW(matrix_from_array(data, 3, -1), std::invalid_argument);
}

TEST(MatrixTest, MatrixFromArraySingleElement) {
    double data[] = {42};
    Matrix A = matrix_from_array(data, 1, 1);

    EXPECT_EQ(A.rows, 1);
    EXPECT_EQ(A.cols, 1);
    EXPECT_EQ(A.data[0][0], 42);

    free_matrix(A);
}

// Тесты горизонтального объединения матриц
TEST(MatrixTest, MatrixHStack) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_hstack(A, B);

    EXPECT_EQ(C.rows, 2);
    EXPECT_EQ(C.cols, 4);

    EXPECT_EQ(C.data[0][0], 1);
    EXPECT_EQ(C.data[0][1], 2);
    EXPECT_EQ(C.data[0][2], 5);
    EXPECT_EQ(C.data[0][3], 6);

    EXPECT_EQ(C.data[1][0], 3);
    EXPECT_EQ(C.data[1][1], 4);
    EXPECT_EQ(C.data[1][2], 7);
    EXPECT_EQ(C.data[1][3], 8);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

TEST(MatrixTest, MatrixHStackInvalidSize) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(3, 2); // Разное количество строк

    EXPECT_THROW(matrix_hstack(A, B), std::invalid_argument);

    free_matrix(A);
    free_matrix(B);
}

// Главная функция
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
