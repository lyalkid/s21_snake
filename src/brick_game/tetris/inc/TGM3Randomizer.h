/*
 * @author Azamat G.
 * @date 12.08.2025.
 * @details
 *
 */

#ifndef TGM3RANDOMIZER_H
#define TGM3RANDOMIZER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tetris.h"

int piece_str_to_type(const char *piece);

/**
 * @brief Генератор фигур в стиле TGM3.
 *
 * @field pieces Доступные фигуры.
 * @field pool Пул фигур (35 элементов).
 * @field order Порядок выдачи фигур.
 * @field order_size Текущий размер order.
 * @field history История последних фигур (4 элемента).
 */
typedef struct {
  const char *pieces[7];
  const char *pool[35];
  const char *order[7];
  int order_size;
  const char *history[4];
} TGM3Randomizer;
/**
 * @brief Инициализация генератора TGM3
 *
 * @param r Указатель на структуру генератора
 */
void init_randomizer(TGM3Randomizer *r);

/**
 * @brief Получить следующую фигуру
 *
 * @param r Указатель на структуру генератора
 * @return const char* Символ фигуры ("I", "J", "L", "O", "S", "T", "Z")
 */
const char *next_piece(TGM3Randomizer *r);

/**
 * @brief Проверяет, содержится ли элемент в массиве
 *
 * @param arr Массив строк
 * @param size Размер массива
 * @param value Строка для поиска
 * @return 1 — найдено, 0 — нет
 */
int contains(const char *arr[], int size, const char *value);

/**
 * @brief Ищет индекс элемента в массиве
 *
 * @param arr Массив строк
 * @param size Размер массива
 * @param value Строка для поиска
 * @return Индекс или -1, если не найдено
 */
int index_of(const char *arr[], int size, const char *value);
void next_tetramino(TGM3Randomizer *r);
#endif  // TGM3RANDOMIZER_H
