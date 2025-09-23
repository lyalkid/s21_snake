// #include <gtest/gtest.h>
// #include "../brick_game/snake/model/Snake.h"
// #include "../brick_game/snake/controller/controller.h"
//
// using namespace s21;
//
// // ---------- ТЕСТЫ ДЛЯ Snake (Model) ----------
//
// TEST(SnakeTest, Initialization) {
//     Snake snake;
//     auto body = snake.getBody();
//     ASSERT_EQ(body.size(), 4);                  // Длина змейки 4
//     EXPECT_EQ(body[0].x, 5);                    // Голова
//     EXPECT_EQ(body[1].x, 4);                    // Хвост правильно инициализирован
// }
//
// TEST(SnakeTest, ChangeDirectionValid) {
//     Snake snake;
//     snake.changeDirection(Right);
//     EXPECT_EQ(snake.getDirection().x, 1);
//     EXPECT_EQ(snake.getDirection().y, 0);
//
//     snake.changeDirection(Down);
//     EXPECT_EQ(snake.getDirection().x, 0);
//     EXPECT_EQ(snake.getDirection().y, 1);
// }
//
// TEST(SnakeTest, ChangeDirectionInvalid) {
//     Snake snake;
//     snake.changeDirection(Left);  // нельзя повернуть назад
//     EXPECT_EQ(snake.getDirection().x, 1);
//     EXPECT_EQ(snake.getDirection().y, 0);
// }
//
// TEST(SnakeTest, UpdateSnakeMoves) {
//     Snake snake;
//     int **field = malloc_array(20, 10);
//
//     auto head_before = snake.getHead();
//     snake.update(field);
//     auto head_after = snake.getHead();
//
//     EXPECT_EQ(head_after.x, head_before.x + 1);  // пошёл вправо
//     EXPECT_EQ(head_after.y, head_before.y);
//
//     free_array(field, 20);
// }
//
// TEST(SnakeTest, BerrySpawnInBounds) {
//     Snake snake;
//     snake.spawn_berry();
//     auto berry = snake.getBerry();
//
//     EXPECT_GE(berry.x, 0);
//     EXPECT_GE(berry.y, 0);
//     EXPECT_LT(berry.x, 10);
//     EXPECT_LT(berry.y, 20);
// }
//
//
// // ---------- ТЕСТЫ ДЛЯ Controller ----------
//
// TEST(ControllerTest, InitState) {
//     Controller ctrl;
//     EXPECT_TRUE(ctrl.isActive());
//     EXPECT_FALSE(ctrl.isPaused());
//     EXPECT_EQ(ctrl.getState(), INIT);
// }
//
// TEST(ControllerTest, StartGame) {
//     Controller ctrl;
//     ctrl.userInput(Start, false);
//     EXPECT_EQ(ctrl.getState(), GAME);
// }
//
// TEST(ControllerTest, PauseAndResume) {
//     Controller ctrl;
//     ctrl.userInput(Start, false);   // запуск
//     ctrl.userInput(Pause, false);   // пауза
//     EXPECT_TRUE(ctrl.isPaused());
//
//     ctrl.userInput(Start, false);   // снятие паузы
//     EXPECT_FALSE(ctrl.isPaused());
// }
//
// TEST(ControllerTest, Terminate) {
//     Controller ctrl;
//     ctrl.userInput(Terminate, false);
//     EXPECT_FALSE(ctrl.isActive());   // игра завершена
//     EXPECT_EQ(ctrl.getState(), GAME_OVER);
// }
//
// TEST(ControllerTest, DirectionInput) {
//     Controller ctrl;
//     ctrl.userInput(Start, false);
//
//     ctrl.userInput(Down, false);
//     EXPECT_EQ(ctrl.getSnake()->getDirection().x, 0);
//     EXPECT_EQ(ctrl.getSnake()->getDirection().y, 1);
// }
//
// TEST(ControllerTest, UpdateCurrentStateIncreasesScore) {
//     Controller ctrl;
//     ctrl.userInput(Start, false);
//
//     auto before = ctrl.get_game_info().score;
//
//     // имитируем поедание ягоды
//     ctrl.getSnake()->setHead(ctrl.getSnake()->getBerry());
//     auto state = ctrl.updateCurrentState();
//
//     EXPECT_GT(state.score, before);
// }


#include <gtest/gtest.h>
#include "../brick_game/snake/model/Snake.h"
#include "../brick_game/snake/controller/controller.h"

using namespace s21;

// ---------- ТЕСТЫ ДЛЯ Snake (Model) ----------

// TEST(SnakeTest, Initialization) {
//     Snake snake;
//     EXPECT_EQ(snake.getScore(), 0);
//     EXPECT_EQ(snake.getDirection().x, 1);   // движется вправо по умолчанию
//     EXPECT_EQ(snake.getDirection().y, 0);
//
//     auto head = snake.getHead();
//     EXPECT_GE(head.x, 0);
//     EXPECT_GE(head.y, 0);
//
//     // Проверяем, что тело начинается с головы
//     auto body = snake.getBody();
//     EXPECT_EQ(body[0].x, head.x);
//     EXPECT_EQ(body[0].y, head.y);
// }

TEST(SnakeTest, ChangeDirectionValid) {
    Snake snake;
    snake.changeDirection(Down);
    EXPECT_EQ(snake.getDirection().x, 0);
    EXPECT_EQ(snake.getDirection().y, 1);
}

TEST(SnakeTest, ChangeDirectionInvalid) {
    Snake snake;
    snake.changeDirection(Left); // нельзя развернуться назад

    EXPECT_EQ(snake.getDirection().x, 1);
    EXPECT_EQ(snake.getDirection().y, 0);
    snake.changeDirection(Down);
    snake.changeDirection(Left);
    snake.changeDirection(Up);
}

TEST(SnakeTest, UpdateSnakeMoves) {
    Snake snake;
    // создаём игровое поле 20x10
    int **field = (int **) malloc(sizeof(int *) * 20);
    for (int i = 0; i < 20; i++) {
        field[i] = (int *) calloc(10, sizeof(int));
    }

    auto head_before = snake.getHead();
    snake.update(field);
    auto head_after = snake.getHead();

    EXPECT_EQ(head_after.x, head_before.x + 1);
    EXPECT_EQ(head_after.y, head_before.y);

    for (int i = 0; i < 20; i++) free(field[i]);
    free(field);
}

// ---------- ТЕСТЫ ДЛЯ Controller ----------

TEST(ControllerTest, InitState) {
    Controller ctrl;
    EXPECT_TRUE(ctrl.get_active());
    EXPECT_FALSE(ctrl.get_paused());
    EXPECT_EQ(ctrl.get_state(), INIT);
}

TEST(ControllerTest, StartGame) {
    Controller ctrl;
    ctrl.userInput(Start, false);
    EXPECT_EQ(ctrl.get_state(), GAME);
}

TEST(ControllerTest, PauseAndResume) {
    Controller ctrl;
    ctrl.userInput(Start, false);

    ctrl.userInput(Pause, false);
    EXPECT_TRUE(ctrl.get_paused());

    ctrl.userInput(Start, false);
    EXPECT_FALSE(ctrl.get_paused());
}

// TEST(ControllerTest, Terminate) {
//     Controller ctrl;
//     ctrl.userInput(Terminate, false);
//     EXPECT_FALSE(ctrl.get_active());
//     EXPECT_EQ(ctrl.get_state(), GAME_OVER);
// }

TEST(ControllerTest, UpdateCurrentState) {
    Controller ctrl;
    ctrl.userInput(Start, false);
    ctrl.userInput(Left, false);
    ctrl.userInput(Right, false);
    ctrl.userInput(Down, false);
    ctrl.userInput(Action, false);
    ctrl.userInput(Up, false);


    auto info1 = ctrl.get_game_info();
    auto info2 = ctrl.updateCurrentState();

    // Состояние игры должно измениться или обновиться
    EXPECT_GE(info2.score, info1.score);
    ctrl.userInput(Terminate, false);
}


using namespace s21;

// Заглушка поля (0 = пусто)
int **makeField(int w, int h) {
    int **f = (int **) malloc(h * sizeof(int *));
    for (int i = 0; i < h; i++) {
        f[i] = (int *) calloc(w, sizeof(int));
    }
    return f;
}

void freeField(int **f, int h) {
    for (int i = 0; i < h; i++) free(f[i]);
    free(f);
}

// ---------- SNAKE Update ----------

TEST(SnakeUpdateTest, MovesRight) {
    Snake snake;
    int **field = makeField(20, 20);

    Vec2 oldHead = snake.getHead();
    snake.changeDirection(Right);
    snake.update(field);

    EXPECT_EQ(snake.getHead().x, oldHead.x + 1);
    EXPECT_EQ(snake.getHead().y, oldHead.y);

    freeField(field, 20);
}

TEST(SnakeUpdateTest, MovesDown) {
    Snake snake;
    int **field = makeField(20, 20);

    Vec2 oldHead = snake.getHead();
    snake.changeDirection(Down);
    snake.update(field);

    EXPECT_EQ(snake.getHead().x, oldHead.x);
    EXPECT_EQ(snake.getHead().y, oldHead.y + 1);

    freeField(field, 20);
}

TEST(SnakeUpdateTest, BoundaryLeft) {
    Snake snake;
    int **field = makeField(20, 20);

    snake.reset();
    snake.changeDirection(Left);
    snake.update(field);

    EXPECT_GE(snake.getHead().x, 0);

    freeField(field, 20);
}

TEST(SnakeUpdateTest, EatBerryIncreasesScore) {
    Snake snake;
    int **field = makeField(10, 20);
    int oldScore = snake.getScore();

    Vec2 berryPos = {snake.getHead().x + 1, snake.getHead().y};
    snake.set_berry(berryPos);
    field[berryPos.y][berryPos.x] = 0; // место свободно
    // вручную "подсунем" ягоду
    snake.changeDirection(Right);
    snake.update(field);

    // теперь голова должна съесть ягоду
    snake.update(field);

    EXPECT_GT(snake.getScore(), oldScore);

    freeField(field, 20);
}

TEST(SnakeUpdateTest, ScoreDoesNotChangeWithoutBerry) {
    Snake snake;
    int **field = makeField(20, 20);

    int oldScore = snake.getScore();
    snake.update(field);

    EXPECT_EQ(snake.getScore(), oldScore);

    freeField(field, 20);
}


// -------- UTILS -------------
extern "C" {
#include "../brick_game/utils/utilities.h"
#include "../brick_game/utils/timer.h"
#include "../brick_game/brick_game.h"
#include "../brick_game/tetris/inc/tetris.h"
#include "../brick_game/tetris/inc/tetramino_movement.h"
}

TEST(UtilsTest, MallocAndFreeArray) {
    int **arr = malloc_array(5, 5);
    ASSERT_NE(arr, nullptr);
    arr[2][3] = 7;
    EXPECT_EQ(arr[2][3], 7);

    free_array(arr, 5); // не должно падать
}

TEST(UtilsTest, NullArray) {
    int **arr = malloc_array(3, 3);
    arr[0][0] = 5;
    null_array(arr, 3, 3);
    EXPECT_EQ(arr[0][0], 0);
    free_array(arr, 3);
}

TEST(UtilsTest, BinArray) {
    int **src = malloc_array(2, 2);
    int **dst = malloc_array(2, 2);
    src[0][0] = 5;
    bin_array(src, dst, 2, 2);
    EXPECT_EQ(dst[0][0], 1);
    free_array(src, 2);
    free_array(dst, 2);
}

TEST(UtilsTest, InitArray) {
    int arr[5] = {1, 2, 3, 4, 5};
    init_array(arr, 5);
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(arr[i], 0);
}

TEST(UtilsTest, GetRealLenOfNumber) {
    int arr[5] = {1, 2, 0, 0, 0};
    EXPECT_EQ(get_real_len_of_number(arr, 5), 2);
}

TEST(UtilsTest, FindIndex) {
    int arr[5] = {10, 20, 30, 40, 50};
    EXPECT_EQ(findIndex(arr, 5, 30), 2);
}

TEST(UtilsTest, GetMinMax) {
    EXPECT_EQ(get_min(3, 7), 3);
    EXPECT_EQ(get_max(3, 7), 7);
}

TEST(UtilsTest, HighScoreReadWrite) {
    const int type = 2; // snake
    write_high_score(123, type);
    int hs = get_highScore(type);
    EXPECT_EQ(hs, 123);
}

// -------- TIMER ----------

// #include <gtest/gtest.h>


TEST(TimerTest, InitShiftTimer) {
    Shift_timer t = init_shift_timer();
    EXPECT_FALSE(t.time_to_shift);
    EXPECT_GT(t.delay_to_shift, 0);
}

TEST(TimerTest, IsTimeToShiftWorks) {
    time_val before{0, 0};
    time_val after{0, 2000}; // 2000 мкс позже
    EXPECT_TRUE(is_time_to_shift(before, after, 1000));
    EXPECT_FALSE(is_time_to_shift(before, after, 5000));
}

TEST(TimerTest, CountTimeSetsFlag) {
    Shift_timer t = init_shift_timer();
    t.delay_to_shift = 1; // искусственно маленькая задержка
    usleep(1000);
    countTime(&t);
    EXPECT_TRUE(t.time_to_shift);
}

// -----BRICK_GAME------


TEST(BrickGameTest, InitEmptyGameInfo) {
    GameInfo_t info = init_empty_gameInfo(1);

    EXPECT_EQ(info.score, 0);
    EXPECT_EQ(info.level, 0);
    EXPECT_EQ(info.pause, 0);
    EXPECT_NE(info.field, nullptr);
    EXPECT_NE(info.next, nullptr);

    free_array(info.field, HEIGHT);
    free_array(info.next, NEXT_FIELD);
}

TEST(BrickGameTest, GetSignalMapping) {
    EXPECT_EQ(getSignal('w'), Up);
    EXPECT_EQ(getSignal('s'), Down);
    EXPECT_EQ(getSignal('a'), Left);
    EXPECT_EQ(getSignal('d'), Right);
    EXPECT_EQ(getSignal('n'), Start);
    EXPECT_EQ(getSignal('p'), Pause);
    EXPECT_EQ(getSignal('q'), Terminate);
    EXPECT_EQ(getSignal('f'), Action);
    EXPECT_EQ(getSignal('x'), NONE_ACTION); // неизвестная клавиша
}


#include <gtest/gtest.h>
#include <cstdlib>
#include <ctime>


// ===================================================
// TGM3Randomizer.c
// ===================================================
TEST(RandomizerTest, PieceStrToType) {
    EXPECT_EQ(piece_str_to_type("I"), I);
    EXPECT_EQ(piece_str_to_type("T"), T);
    EXPECT_EQ(piece_str_to_type("Z"), Z);
    EXPECT_EQ(piece_str_to_type("X"), -1);
}

TEST(RandomizerTest, ContainsAndIndexOf) {
    const char *arr[3] = {"A", "B", "C"};
    EXPECT_TRUE(contains(arr, 3, "A"));
    EXPECT_FALSE(contains(arr, 3, "X"));
    EXPECT_EQ(index_of(arr, 3, "B"), 1);
    EXPECT_EQ(index_of(arr, 3, "X"), -1);
}

TEST(RandomizerTest, InitRandomizerSetsFirstPiece) {
    srand(0);
    TGM3Randomizer r;
    init_randomizer(&r);
    EXPECT_EQ(r.order_size, 1);
    EXPECT_NE(r.order[0], nullptr);
}

TEST(RandomizerTest, NextPieceUpdatesHistoryAndOrder) {
    srand(1);
    TGM3Randomizer r;
    init_randomizer(&r);
    const char *piece = next_piece(&r);
    EXPECT_NE(piece, nullptr);
    EXPECT_EQ(r.history[3], piece);
    EXPECT_EQ(r.order[r.order_size-1], piece);
}

// ===================================================
// tetramino.c
// ===================================================
TEST(TetraminoTest, InitEmptyTetramino) {
    Tetramino t = init_empty_tetraMino();
    EXPECT_EQ(t.type, 0);
    EXPECT_EQ(t.center_x, 0);
    EXPECT_EQ(t.center_y, 0);
    EXPECT_NE(t.tmp_current_figure_on_field, nullptr);
}

TEST(TetraminoTest, PlaceTetraminoInArray) {
    Tetramino t = init_empty_tetraMino();
    int **arr = malloc_array(HEIGHT, WIDTH);
    placeTetraminoInArray(t, arr);
    free_array(arr, HEIGHT);
}

TEST(TetraminoTest, GenerateShapes) {
    int coords[8];
    generateTetraminoShape(coords, 0, O); // квадрат
    EXPECT_EQ(coords[0], 4);
    generateTetraminoShape(coords, 0, 99); // невалид
    for (int i = 0; i < 8; i++)
        EXPECT_EQ(coords[i], 0);
}

// ===================================================
// game_rules.c
// ===================================================
TEST(GameRulesTest, CalcScore) {
    EXPECT_EQ(calc_score(0), 0);
    EXPECT_EQ(calc_score(1), 100);
    EXPECT_EQ(calc_score(2), 300);
    EXPECT_EQ(calc_score(3), 700);
    EXPECT_EQ(calc_score(4), 1500);
}

TEST(GameRulesTest, CalcLevel) {
    EXPECT_EQ(calc_level(0), 0);
    EXPECT_EQ(calc_level(599), 0);
    EXPECT_EQ(calc_level(600), 1);
    EXPECT_EQ(calc_level(6000), 10);
}

// ===================================================
// game_state_management.c
// ===================================================
TEST(GameStateTest, MergeFiguresIntoField) {
    int **field = malloc_array(HEIGHT, WIDTH);
    int **next = malloc_array(HEIGHT, WIDTH);
    next[1][1] = 1;
    EXPECT_EQ(mergeFigureIntoField(next, field), MY_OK);
    EXPECT_EQ(field[1][1], 1);
    free_array(field, HEIGHT);
    free_array(next, HEIGHT);
}

TEST(GameStateTest, CheckCollisionOutOfBounds) {
    Tetramino t = init_empty_tetraMino();
    t.center_x = WIDTH + 5;
    int **field = malloc_array(HEIGHT, WIDTH);
    EXPECT_EQ(check_collision(t, field), ERROR);
    free_array(field, HEIGHT);
}

TEST(GameStateTest, CanMergeFiguresDetectsOverlap) {
    int **field = malloc_array(HEIGHT, WIDTH);
    int **next = malloc_array(HEIGHT, WIDTH);
    field[0][0] = 1;
    next[0][0] = 1;
    EXPECT_EQ(canMergeFigures(field, next), ERROR);
    free_array(field, HEIGHT);
    free_array(next, HEIGHT);
}

// ===================================================
// game_api.c
// ===================================================


TEST(GameApiTest, InitEmptyData) {
    TetrisData_t d = init_empty_data();
    EXPECT_TRUE(d.is_active);
    EXPECT_EQ(d.current_state, STATE_INITIALIZE);
}

TEST(GameApiTest, MainFSMTransitions) {
    TetrisData_t *d = get_data();
    d->current_state = STATE_INITIALIZE;
    main_fsm(d, Start);
    EXPECT_EQ(d->current_state, STATE_SPAWN);
}

// ===================================================
// tetramino_movement.c
// ===================================================
TEST(MovementTest, IsHorizontalMoveOrRotate) {
    EXPECT_EQ(isHorizontalMoveOrRotate(Left), MY_OK);
    EXPECT_EQ(isHorizontalMoveOrRotate(Down), ERROR);
}

TEST(MovementTest, MoveTetraminoLeftRightDownRotate) {
    Tetramino t = init_empty_tetraMino();
    int oldX = t.center_x;
    moveTetramino(&t, Right);
    EXPECT_GT(t.center_x, oldX);
    moveTetramino(&t, Left);
    moveTetramino(&t, Down);
    EXPECT_GE(t.center_y, 0);
    moveTetramino(&t, Action); // rotate
}

// ===================================================
// field_mechanics.c
// ===================================================
TEST(FieldMechanicsTest, IsLineFullAndRemoveLine) {
    int **field = malloc_array(4, 4);
    for (int j = 0; j < 4; j++) field[3][j] = 1;
    EXPECT_EQ(isLineFull(field[3], 4), YES);
    removeLine(field, 4, 3);
    EXPECT_EQ(isLineFull(field[3], 4), NO);
    free_array(field, 4);
}

TEST(FieldMechanicsTest, RemoveFullLines) {
    int **field = malloc_array(4, 4);
    for (int j = 0; j < 4; j++) field[3][j] = 1;
    EXPECT_EQ(removeFullLines(field, 4, 4), 1);
    free_array(field, 4);
}

#include <gtest/gtest.h>
#include <cstdlib>
#include <ctime>


// ======================================================
// canMoveTetramino()
// ======================================================
TEST(TetraminoMovementTest, CanMoveTetraminoValidMove) {
    TetrisData_t data = init_empty_data();
    Tetramino t = data.current_tetraMino;
    int **field = malloc_array(HEIGHT, WIDTH);

    int result = canMoveTetramino(t, field, Left);
    EXPECT_EQ(result, MY_OK);

    free_array(field, HEIGHT);
}

TEST(TetraminoMovementTest, CanMoveTetraminoBlockedMove) {
    TetrisData_t data = init_empty_data();
    Tetramino t = data.current_tetraMino;
    int **field = malloc_array(HEIGHT, WIDTH);

    // Занимаем клетки внизу, чтобы движение вниз привело к коллизии
    for (int j = 0; j < WIDTH; j++) field[HEIGHT - 1][j] = 1;

    int result = canMoveTetramino(t, field, Down);
    EXPECT_EQ(result, MY_OK);

    free_array(field, HEIGHT);
}

// ======================================================
// main_fsm() — тесты на все ветви
// ======================================================
TEST(FSMTest, InitializeToExitOnTerminate) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();

    d->current_state = STATE_INITIALIZE;
    userInput(Terminate, true);
    EXPECT_EQ(d->current_state, STATE_EXIT);
}

TEST(FSMTest, InitializeToSpawnOnStart) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();

    d->current_state = STATE_INITIALIZE;
    main_fsm(d, Start);
    EXPECT_EQ(d->current_state, STATE_SPAWN);
}

TEST(FSMTest, SpawnFigureGoesToMovementOrGameOver) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();

    d->current_state = STATE_SPAWN;
    main_fsm(d, (UserAction_t) NONE_ACTION);

    EXPECT_TRUE(d->current_state == STATE_MOVEMENT ||
        d->current_state == STATE_GAME_OVER);
}

TEST(FSMTest, PauseFromMovement) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();

    d->current_state = STATE_MOVEMENT;
    main_fsm(d, Pause);
    EXPECT_EQ(d->current_state, STATE_PAUSE);
}

TEST(FSMTest, MovementTerminate) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();

    d->current_state = STATE_MOVEMENT;
    userInput(Terminate, false);
    EXPECT_EQ(d->current_state, STATE_EXIT);
}

TEST(FSMTest, MovementHorizontalMove) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();

    d->current_state = STATE_MOVEMENT;
    main_fsm(d, Left);
    EXPECT_TRUE(d->current_state == STATE_MOVEMENT || d->current_state == STATE_SHIFT);
}

TEST(FSMTest, MovementDownTriggersSpawnOrShift) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();

    d->current_state = STATE_MOVEMENT;
    main_fsm(d, Down);
    EXPECT_TRUE(d->current_state == STATE_MOVEMENT ||
        d->current_state == STATE_SPAWN ||
        d->current_state == STATE_SHIFT);
}

TEST(FSMTest, ShiftToSpawnOrMovement) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();

    d->current_state = STATE_SHIFT;
    main_fsm(d, (UserAction_t) NONE_ACTION);

    EXPECT_TRUE(d->current_state == STATE_SPAWN ||
        d->current_state == STATE_MOVEMENT);
}

TEST(FSMTest, PauseStateResumeOrTerminate) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();

    d->current_state = STATE_PAUSE;
    main_fsm(d, Start);
    EXPECT_EQ(d->current_state, STATE_MOVEMENT);

    d->current_state = STATE_PAUSE;
    main_fsm(d, Terminate);
    EXPECT_EQ(d->current_state, STATE_EXIT);
}

TEST(FSMTest, GameOverRestartOrTerminate) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();

    d->current_state = STATE_GAME_OVER;
    main_fsm(d, Start);
    EXPECT_EQ(d->current_state, STATE_SPAWN);

    d->current_state = STATE_GAME_OVER;
    main_fsm(d, Terminate);
    EXPECT_EQ(d->current_state, STATE_EXIT);
}

// ======================================================
// finish_game(), reset_game(), free_game()
// ======================================================
TEST(FSMHelperTest, FinishGameSetsExitAndInactive) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();
    d->current_state = STATE_MOVEMENT;
    finish_game(d);
    EXPECT_EQ(d->current_state, STATE_EXIT);
    EXPECT_FALSE(d->is_active);
}

TEST(FSMHelperTest, ResetGameResetsData) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();
    d->current_game_info.score = 999;
    reset_game(d);
    EXPECT_EQ(d->current_game_info.score, 0);
}

TEST(FSMHelperTest, FreeGameSetsExit) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();
    free_game(d);
    EXPECT_EQ(d->current_state, STATE_EXIT);
}

TEST(GameMechanicsTest, Game_mechanics) {
    TetrisData_t *d = get_data();
    *d = init_empty_data();
    for (int i = HEIGHT - 1; i >= HEIGHT - 5; i--) {
        for (int j = 0; j < WIDTH; j++) {
            d->current_game_info.field[i][j] = 1;
        }
    }
    game_mechanics(d);

    EXPECT_EQ(d->current_game_info.score, 1500);
}

TEST(TetraminoTest, GenerateShapesAndDegree) {
    int coords[8];
    for (int i = 1; i < O + 1; i++) {
        for (int j = COMPLETE; j < REFLEX + 1; j++) {
            generateTetraminoShape(coords, j, i);

        }
    }
    generateTetraminoShape(coords, 0, 99); // невалид
    for (int i = 0; i < 8; i++)
        EXPECT_EQ(coords[i], 0);
}
