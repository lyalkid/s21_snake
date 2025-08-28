/*
 * @author Azamat G.
 * @date 15.08.2025.
 * @details
 *
 */

#ifndef UTILITIES_H
#define UTILITIES_H
#include <stdio.h>
#include <stdlib.h>
/**
 * @brief Выделяет память под 2D-массив.
 *
 * @param rows Строки.
 * @param cols Столбцы.
 * @return Указатель на массив.
 */
int **malloc_array(int rows, int cols);
/**
 * @brief Освобождает 2D-массив.
 *
 * @param field Массив.
 * @param rows Строки.
 */
void free_array(int **field, int rows);

/**
 * @brief Сортирует массив по убыванию пузырьковой сортировкой.
 *
 * @param array Целевой массив.
 * @param size Размер массива.
 */
// void sort(int array[], int size);

/**
 * @brief Заполняет 2D-массив нулями.
 *
 * @param field Целевой массив.
 * @param rows Число строк.
 * @param cols Число столбцов.
 */
void null_array(int **field, int rows, int cols);
/**
 * @brief Бинаризует массив (0 → 0, !0 → 1).
 *
 * @param src Исходный массив.
 * @param dist Целевой массив.
 * @param rows Число строк.
 * @param cols Число столбцов.
 */
void bin_array(int **src, int **dist, int rows, int cols);
/**
 * @brief Заполняет массив нулями.
 *
 * @param array Целевой массив.
 * @param size Размер массива.
 */
void init_array(int array[], int size);
/**
 * @brief Вычисляет значимую длину массива (без завершающих нулей).
 *
 * @param a Целевой массив.
 * @param size Физический размер массива.
 * @return Число значимых элементов.
 */
int get_real_len_of_number(const int a[], int size);

/**
 * @brief Выводит 2D-массив в stdout.
 *
 * @param array Целевой массив.
 *
 * @note Для отладки, формат:
 *   --------------------
 *   0 0 1 0 ...
 *   1 0 0 1 ...
 *   --------------------
 */
void print_array(int **array, int max_x, int min_x);

void overlay_array(int** field, int** next, int max_x, int min_x);
/**
 * @brief Возвращает минимальное из двух чисел.
 *
 * @param a Первое число.
 * @param b Второе число.
 * @return Меньшее из a и b.
 */
int get_min(int a, int b);
/**
 * @brief Возвращает максимальное из двух чисел.
 *
 * @param a Первое число.
 * @param b Второе число.
 * @return Большее из a и b.
 */
int get_max(int a, int b);

/**
 * @brief Ищет первое вхождение элемента в массиве.
 *
 * @param array Целевой массив.
 * @param size Размер массива.
 * @param i Искомое значение.
 * @return Индекс первого вхождения или -1 если не найдено.
 */
int findIndex(const int array[], int size, int i);
#endif  // UTILITIES_H
