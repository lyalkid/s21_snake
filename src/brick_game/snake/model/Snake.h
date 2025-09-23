/*
* @author Azamat G.
* @date 13.09.2025.
* @details Модель игры Snake.
*
*/

#ifndef SNAKE_H
#define SNAKE_H

extern "C" {
#include "../../brick_game.h"
#include "../../utils/defines.h"
}

#include <stdlib.h>
#include <vector>

namespace s21 {

    /**
     * @struct Vec2
     * @brief Двумерный вектор для координат (x, y).
     */
    typedef struct {
        int x; ///< Координата X
        int y; ///< Координата Y
    } Vec2;

    /**
     * @class Snake
     * @brief Класс, реализующий игровую модель "Змейка".
     */
    class Snake {
    public:
        friend class Controller;

        /**
         * @brief Конструктор. Инициализирует змейку в начале игры.
         */
        Snake();

        /**
         * @brief Сброс состояния змейки (начало новой игры).
         */
        void reset();

        /**
         * @brief Изменяет направление движения.
         * @param action Ввод пользователя (влево, вправо, вверх, вниз).
         */
        void changeDirection(UserAction_t action);

        /**
         * @brief Обновляет состояние змейки (перемещение, еда, рост).
         * @param field Игровое поле.
         */
        void update(int **field);

        /**
         * @return Текущее направление движения.
         */
        Vec2 getDirection(){ return dir; }

        /**
         * @return Позиция головы змейки.
         */
        Vec2 getHead(){ return head; }

        /**
         * @return Указатель на массив с телом змейки.
         */
        Vec2 *getBody(){ return body; }

        /**
         * @brief Устанавливает позицию ягоды.
         * @param b Вектор позиции ягоды.
         */
        void set_berry(const Vec2 b) {
            berry.x = b.x;
            berry.y = b.y;
        }

        /**
         * @return Текущий счёт игрока.
         */
        int getScore(){ return score; }

        /**
         * @brief Деструктор (по умолчанию).
         */
        ~Snake() = default;

    private:
        int width;          ///< Ширина поля
        int height;         ///< Высота поля
        int score;          ///< Текущий счёт
        Vec2 body[200];     ///< Массив клеток тела
        Vec2 head;          ///< Голова змейки
        Vec2 berry;         ///< Позиция ягоды
        Vec2 dir;           ///< Направление движения
        bool direction_changed; ///< Флаг изменения направления

        /**
         * @brief Генерирует новую ягоду на поле.
         */
        void spawn_berry();
    };
}
#endif //SNAKE_H
