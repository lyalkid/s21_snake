/*
 * @author Azamat G.
 * @date 14.08.2025.
 * @details
 *
 */

#ifndef TETRAMINO_MOVEMENT_H
#define TETRAMINO_MOVEMENT_H
#include "tetris.h"

/**
 * @brief Проверяет возможность движения фигуры.
 *
 * @param tetraMino Фигура.
 * @param field Игровое поле.
 * @param key Направление (Left/Right/Action).
 * @return 1 если возможно, иначе 0.
 */
int canMoveTetramino(Tetramino tetraMino, int **field, UserAction_t key);

/**
 * @brief Проверяет возможность поворота.
 *
 * @param tetraMino Фигура.
 * @param rotate Угол поворота (0-3).
 * @return 1 если возможно, иначе 0.
 */
int is_rotate_possible(Tetramino tetraMino, int rotate);
/**
 * @brief Двигает фигуру.
 *
 * @param tetraMino Указатель на фигуру.
 * @param key Направление (Left/Right/Action).
 */
// Аналогично для:
void moveTetramino(Tetramino *tetraMino, UserAction_t key);
void move_down_tetraMino(Tetramino *tetraMino);
void move_up_tetraMino(Tetramino *tetraMino);
void rotate_TetraMino(Tetramino *tetraMino);
/**
 * @brief Проверяет, является ли действие движением.
 *
 * @param userAction Действие.
 * @return 1 если да, иначе 0.
 */
int isHorizontalMoveOrRotate(UserAction_t userAction);
/**
 * @brief Проверяет, является ли действие движением вниз.
 *
 * @param userAction Действие.
 * @return 1 если нет, 0 если Down.
 */
int isDownMove(UserAction_t userAction);

#endif  // TETRAMINO_MOVEMENT_H
