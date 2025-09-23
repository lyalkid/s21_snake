/*
* @author Azamat G.
* @date 20.09.2025.
* @details Контроллер для управления логикой игры Snake (MVC-паттерн).
*
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <unistd.h>

extern "C" {
#include "../../brick_game.h"
#include "../../utils/timer.h"
#include "../../../brick_game/utils/defines.h"
}

#include "../model/Snake.h"

#define BERRY 1   ///< Код для клетки с ягодой
#define HEAD 2    ///< Код для клетки с головой змейки
#define SNAKE 3   ///< Код для клетки с телом змейки

/**
 * @brief Возможные состояния игры Snake.
 */
typedef enum {
    INIT = 0,   ///< Инициализация
    GAME,       ///< Игровой процесс
    PAUSE,      ///< Пауза
    GAME_OVER,  ///< Конец игры
    WON         ///< Победа
} Snake_state;

namespace s21 {

    /**
     * @class Controller
     * @brief Управляет моделью Snake и взаимодействием с пользователем.
     *
     * Использует паттерн MVC: хранит указатель на модель (Snake),
     * управляет состоянием игры и реагирует на пользовательский ввод.
     */
    class Controller {
    public:
        /**
         * @brief Конструктор контроллера. Инициализирует модель и состояние.
         */
        Controller();

        /**
         * @brief Деструктор (по умолчанию).
         */
        ~Controller() = default;

        /**
         * @return true, если игра активна.
         */
        bool get_active() { return active; }

        /**
         * @return true, если игра на паузе.
         */
        bool get_paused() { return paused; }

        /**
         * @return true, если состояние обновилось.
         */
        bool get_updated() { return updated; }

        /**
         * @brief Сбрасывает флаг обновления.
         */
        void set_updated() { updated = false; }

        /**
         * @return Текущее состояние игры (INIT, GAME, PAUSE, GAME_OVER, WON).
         */
        Snake_state get_state() {
            if (paused) return PAUSE;
            return state;
        }

        /**
         * @return Текущая модель Snake.
         */
        Snake get_model() { return *model; }

        /**
         * @brief Возвращает информацию об игре (поле, счёт, уровень).
         */
        GameInfo_t get_game_info();

        /**
         * @brief Обрабатывает ввод пользователя.
         * @param action Действие (влево, вправо, вверх, вниз, пауза).
         * @param hold true — удержание клавиши.
         */
        void userInput(UserAction_t action, bool hold);

        /**
         * @brief Обновляет текущее состояние игры.
         * @return Структура GameInfo_t с данными об игре.
         */
        GameInfo_t updateCurrentState();

    private:
        bool paused;       ///< Флаг паузы
        bool active;       ///< Флаг активности игры
        bool updated;      ///< Флаг обновления состояния
        bool win;          ///< Флаг победы
        Snake_state state; ///< Текущее состояние
        GameInfo_t info{}; ///< Информация об игре
        Snake *model;      ///< Указатель на модель змейки

    public:
        Shift_timer timer{}; ///< Таймер для управления скоростью
    };
}
#endif //CONTROLLER_H
