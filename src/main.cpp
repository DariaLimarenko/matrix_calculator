#include "matrix.h"
#include <iostream>

void demo_basic_operations() {
    std::cout << "=== Демонстрация базовых операций с матрицами ===" << std::endl;

    // Создание матриц
    std::cout << "\n1. Создание матриц:" << std::endl;
    Matrix A = create_matrix(2, 3);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;
    std::cout << "Матрица A:" << std::endl;
    print_matrix(A);

    Matrix B = create_matrix(2, 3);
    B.data[0][0] = 2; B.data[0][1] = 3; B.data[0][2] = 4;
    B.data[1][0] = 5; B.data[1][1] = 6; B.data[1][2] = 7;
    std::cout << "Матрица B:" << std::endl;
    print_matrix(B);

    // Сложение матриц
    std::cout << "\n2. Сложение матриц A + B:" << std::endl;
    try {
        Matrix C = matrix_add(A, B);
        print_matrix(C);
        free_matrix(C);
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void demo_multiplication() {
    std::cout << "\n=== Демонстрация умножения матриц ===" << std::endl;

    // Матрица 2x3
    Matrix A = create_matrix(2, 3);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;

    // Матрица 3x2
    Matrix B = create_matrix(3, 2);
    B.data[0][0] = 7; B.data[0][1] = 8;
    B.data[1][0] = 9; B.data[1][1] = 10;
    B.data[2][0] = 11; B.data[2][1] = 12;

    std::cout << "Матрица A (2x3):" << std::endl;
    print_matrix(A);
    std::cout << "Матрица B (3x2):" << std::endl;
    print_matrix(B);

    std::cout << "Результат умножения A * B:" << std::endl;
    try {
        Matrix C = matrix_multiply(A, B);
        print_matrix(C);
        free_matrix(C);
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    free_matrix(A);
    free_matrix(B);
}

void demo_transpose() {
    std::cout << "\n=== Демонстрация транспонирования ===" << std::endl;

    Matrix A = create_matrix(3, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    A.data[2][0] = 5; A.data[2][1] = 6;

    std::cout << "Исходная матрица:" << std::endl;
    print_matrix(A);

    Matrix A_transposed = matrix_transpose(A);
    std::cout << "Транспонированная матрица:" << std::endl;
    print_matrix(A_transposed);

    free_matrix(A);
    free_matrix(A_transposed);
}

void demo_from_array() {
    std::cout << "\n=== Демонстрация создания из массива ===" << std::endl;

    double data[] = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5};
    Matrix A = matrix_from_array(data, 2, 3);

    std::cout << "Матрица созданная из массива:" << std::endl;
    print_matrix(A);

    std::cout << "Сумма всех элементов: " << matrix_sum(A) << std::endl;

    free_matrix(A);
}

void demo_error_handling() {
    std::cout << "\n=== Демонстрация обработки ошибок ===" << std::endl;

    std::cout << "Попытка создания матрицы с неверными размерами:" << std::endl;
    try {
        Matrix invalid = create_matrix(-1, 5);
    } catch (const std::exception& e) {
        std::cout << "Поймано исключение: " << e.what() << std::endl;
    }

    std::cout << "Попытка сложения матриц разных размеров:" << std::endl;
    try {
        Matrix A = create_matrix(2, 2);
        Matrix B = create_matrix(3, 3);
        Matrix C = matrix_add(A, B);
        free_matrix(C);
        free_matrix(A);
        free_matrix(B);
    } catch (const std::exception& e) {
        std::cout << "Поймано исключение: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Программа для работы с матрицами" << std::endl;
    std::cout << "=================================" << std::endl;

    demo_basic_operations();
    demo_multiplication();
    demo_transpose();
    demo_from_array();
    demo_error_handling();

    std::cout << "\n=================================" << std::endl;
    std::cout << "Демонстрация завершена!" << std::endl;

    return 0;
}
