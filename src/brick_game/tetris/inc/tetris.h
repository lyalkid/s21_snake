/*
 * @author Azamat G.
 * @date 15.08.2025.
 * @details
 *
 */

#ifndef TETRIS_H
#define TETRIS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "../../brick_game.h"
#include "../../utils/defines.h"
#include "../../utils/utilities.h"
#include "timer.h"

enum answer { YES, NO };

/** Статусы функций. */
enum status { ERROR, MY_OK };

/** Типы фигур. */
enum figures { T = 1, J, L, I, S, Z, O };

/** Углы поворота фигур. */
enum degrees { COMPLETE, RIGHT, STRAIGHT, REFLEX };

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
    int order_size;
    const char *history[4];
    const char *pieces[7];
    const char *order[7];
    const char *pool[35];
} TGM3Randomizer;

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
    TGM3Randomizer r;
} Tetramino;

/**
 * @brief Создает пустую фигуру.
 *
 * @return Инициализированная структура Tetramino.
 */
Tetramino init_empty_tetraMino();

// Tetramino *get_tetramino_instance();

int piece_str_to_type(const char *piece);

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

void print_tetramino(Tetramino tetramino);

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


typedef enum {
    STATE_INITIALIZE,
    STATE_SPAWN,
    STATE_MOVEMENT ,

    STATE_SHIFT,
    STATE_PAUSE,
    STATE_GAME_OVER,
    STATE_EXIT
}Tetris_state_t;

/**
 * @brief Структура для хранения игровой информации
 * @field currenState - текущее состоянии
 * @field shift_timer - таймер для управления скоростью
 * @field current_tetraMino - текущая фигура
 * @field current_game_info - текущее состояние игры
 */
typedef struct {
    bool is_active;
    bool is_win;
    bool changed;
    UserAction_t current_action;
    Tetris_state_t current_state;
    // Tetris_state_t prev_state;
    Shift_timer shift_timer;
    Tetramino current_tetraMino;
    GameInfo_t current_game_info;
}TetrisData_t;

void game_mechanics(TetrisData_t* data);
GameInfo_t init_empty_gameInfo(void);

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
int check_collision(Tetramino tetraMino, int **field);

/**
 * @brief Проверяет коллизию поля и фигуры.
 *
 * @param field Игровое поле.
 * @param next Фигура.
 * @return 1 если коллизии нет, иначе 0.
 */
int canMergeFigures(int **field, int **next);







TetrisData_t *get_data(void);
TetrisData_t init_empty_data(void);

const char* stateToString(Tetris_state_t s);
const char *actionToString(UserAction_t s) ;
void main_fsm(TetrisData_t *data, UserAction_t action);
void game_fsm(TetrisData_t *data);
void finish_game(TetrisData_t *data);
void reset_game(TetrisData_t *data);
void free_game(TetrisData_t *data);

void userInput(UserAction_t action, bool hold);
void onMoving(UserAction_t action);

void onStart(TetrisData_t* data);
int figure_is_attaching(UserAction_t action, TetrisData_t *data) ;
void attach_tetramino(TetrisData_t *data);

/**
 * @brief пытается создать новую фигуру, возвращает MY_OK или ERROR
 * @param tetraMino фигура
 * @param game_info структура игры
 * @return
 */
int spawn_figure(Tetramino *tetraMino, GameInfo_t *game_info);
void is_game_over(int* state, int status);
int onShifting(void);
GameInfo_t updateCurrentState();


#endif  // TETRIS_H
