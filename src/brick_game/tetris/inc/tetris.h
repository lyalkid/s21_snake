/*
 * @author Azamat G.
 * @date 15.08.2025.
 * @details
 *
 */

#ifndef TETRIS_H
#define TETRIS_H
#include "../../brick_game.h"
#include "../../utils/defines.h"
#include "../../utils/utilities.h"

enum answer { YES, NO };
/** Статусы функций. */
enum status { ERROR, MY_OK };

/** Типы фигур. */
enum figures { T = 1, J, L, I, S, Z, O };

/** Углы поворота фигур. */
enum degrees { COMPLETE, RIGHT, STRAIGHT, REFLEX };

/**
 * @brief Структура тетрамино.
 *
 * @field type Текущий тип фигуры.
 * @field next_type Следующий тип.
 * @field rotate Угол поворота.
 * @field center_x X-центр фигуры.
 * @field center_y Y-центр фигуры.
 * @field coordinates Координаты блоков (относительно центра).
 * @field tmp_current_figure_on_field Временное поле для отрисовки.
 */
typedef struct {
  int type;
  int next_type;
  int rotate;
  int center_x;
  int center_y;
  int coordinates[8];
  int **tmp_current_figure_on_field;
} Tetramino;
/**
 * @brief Создает пустую фигуру.
 *
 * @return Инициализированная структура Tetramino.
 */
Tetramino init_empty_tetraMino();

Tetramino *get_tetramino_instance();

/**
 * @brief Преобразует фигуру в 2D-массив.
 *
 * @param tetraMino Фигура.
 * @param next Целевой массив.
 */
void placeTetraminoInArray(Tetramino tetraMino, int **next);
/**
 * @brief Копирует координаты фигуры.
 *
 * @param coordinates Целевой массив.
 * @param values Исходные координаты.
 */
void setCoordinates(int *coordinates, const int *values);
/**
 * @brief Генерирует координаты фигуры по типу и углу.
 *
 * @param coordinates Целевой массив.
 * @param rotate Угол поворота.
 * @param type Тип фигуры (T, J, L, I, S, Z, O).
 */
void generateTetraminoShape(int coordinates[], int rotate, int type);
/**
 * @brief Генерирует координаты фигуры по типу и углу.
 *
 * @param coordinates Целевой массив.
 * @param rotate Угол поворота.
 * @param type Тип фигуры (T, J, L, I, S, Z, O).
 */
void generateShapeSZorI(int coordinates[], int rotate, int type);
/**
 * @brief Генерирует координаты фигуры по типу и углу.
 *
 * @param coordinates Целевой массив.
 * @param rotate Угол поворота.
 * @param type Тип фигуры (T, J, L, I, S, Z, O).
 */
void generateShapeTJL(int coordinates[], int rotate, int type);

/**
 * @brief Создает новую фигуру.
 *
 * @param tetraMino Указатель на фигуру.
 *
 * @details Использует TGM3Randomizer для генерации.
 */
void spawnNextTetramino(Tetramino *tetraMino);

/**
 * @brief Сканирует поле на заполненные строки.
 *
 * @param field Игровое поле.
 * @param rows Число строк.
 * @param cols Число столбцов.
 * @return Количество удаленных строк.
 *
 * @details Удаляет строки и сдвигает поле вниз.
 */
int removeFullLines(int **field, int rows, int cols);
/**
 * @brief Проверяет, заполнена ли строка.
 *
 * @param a Строка поля.
 * @param size Длина строки.
 * @return 1 (YES) если заполнена, иначе 0.
 */
int isLineFull(const int a[], int size);
/**
 * @brief Удаляет строку и сдвигает поле.
 *
 * @param field Игровое поле.
 * @param cols Число столбцов.
 * @param row_not Индекс удаляемой строки.
 */
void removeLine(int **field, int cols, int row_not);

/**
 * @brief Вычисляет очки за удаленные строки.
 *
 * @param lines Число строк.
 * @return Количество очков.
 */
int calc_score(int lines);
/**
 * @brief Вычисляет текущий уровень игры на основе счета.
 *
 * @param current_score Текущий счет игрока.
 * @return Текущий уровень (0-10).
 *
 * @details Формула: level = current_score / 600, максимум 10.
 */
int calc_level(int current_score);
GameInfo_t init_empty_gameInfo();
/**
 * @brief Объединяет поле с фигурой.
 *
 * @param next Массив фигуры.
 * @param field Игровое поле.
 * @return 1 (MY_OK) если объединение успешно, 0 (ERROR) при коллизии.
 */
int mergeFigureIntoField(int **next, int **field);
/**
 * @brief Проверяет коллизию фигуры с игровым полем.
 *
 * @param tetraMino Фигура для проверки.
 * @param field Игровое поле.
 * @return 1 (MY_OK) если коллизий нет, 0 (ERROR) при коллизии.
 */
int checkCollisionWithWallsOrBlocks(Tetramino tetraMino, int **field);
/**
 * @brief Проверяет коллизию поля и фигуры.
 *
 * @param field Игровое поле.
 * @param next Фигура.
 * @return 1 если коллизии нет, иначе 0.
 */
int canMergeFigures(int **field, int **next);

/**
 * @brief Получает рекорд из файла.
 *
 * @return Текущий рекорд (0 если файл недоступен).
 *
 * @note Файл: "highscore.txt" в рабочей директории.
 */
int get_highScore();
/**
 * @brief Записывает новый рекорд в файл.
 *
 * @param h_score Новое значение рекорда.
 *
 * @note Файл: "highscore.txt" в рабочей директории.
 */
void write_high_score(int h_score);

#endif  // TETRIS_H
