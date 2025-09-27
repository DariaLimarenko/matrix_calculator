#include <iostream>
#include "matrix.h"

int main() {
    std::cout << "=== Демонстрация работы с матрицами ===" << std::endl;

    // Создание матриц
    std::cout << "\n1. Создание матриц 2x2:" << std::endl;
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    // Заполнение матриц значениями
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    std::cout << "Матрица A:" << std::endl;
    print_matrix(A);

    std::cout << "Матрица B:" << std::endl;
    print_matrix(B);

    // Сложение матриц
    std::cout << "\n2. Сложение матриц A + B:" << std::endl;
    Matrix C = matrix_add(A, B);
    print_matrix(C);
    free_matrix(C);

    // Умножение матриц
    std::cout << "\n3. Умножение матриц A * B:" << std::endl;
    Matrix D = matrix_multiply(A, B);
    print_matrix(D);
    free_matrix(D);

    // Транспонирование матрицы
    std::cout << "\n4. Транспонирование матрицы A:" << std::endl;
    Matrix E = matrix_transpose(A);
    print_matrix(E);
    free_matrix(E);

    // Сумма элементов матрицы
    std::cout << "\n5. Сумма элементов матрицы A: " << matrix_sum(A) << std::endl;

    // Создание матрицы из массива
    std::cout << "\n6. Создание матрицы из массива:" << std::endl;
    double data[] = {9, 8, 7, 6, 5, 4};
    Matrix F = matrix_from_array(data, 2, 3);
    print_matrix(F);

    // Горизонтальное объединение
    std::cout << "\n7. Горизонтальное объединение матриц:" << std::endl;
    Matrix G = create_matrix(2, 1);
    G.data[0][0] = 10; G.data[1][0] = 20;

    Matrix H = matrix_hstack(A, G);
    std::cout << "Матрица A:" << std::endl;
    print_matrix(A);
    std::cout << "Матрица G:" << std::endl;
    print_matrix(G);
    std::cout << "Результат горизонтального объединения:" << std::endl;
    print_matrix(H);

    // Освобождение памяти
    free_matrix(A);
    free_matrix(B);
    free_matrix(F);
    free_matrix(G);
    free_matrix(H);

    // Демонстрация обработки ошибок
    std::cout << "\n8. Демонстрация обработки ошибок:" << std::endl;
    try {
        Matrix invalid = create_matrix(-1, 2);
    } catch (const std::invalid_argument& e) {
        std::cout << "Поймано исключение: " << e.what() << std::endl;
    }

    try {
        Matrix A2 = create_matrix(2, 2);
        Matrix B2 = create_matrix(3, 3);
        Matrix C2 = matrix_add(A2, B2);
        free_matrix(A2);
        free_matrix(B2);
        free_matrix(C2);
    } catch (const std::invalid_argument& e) {
        std::cout << "Поймано исключение: " << e.what() << std::endl;
    }

    std::cout << "\n=== Программа завершена успешно ===" << std::endl;

    return 0;
}
