//
// Created by Azamat G. on 08.08.2025.
//

#ifndef BRICK_GAME_H
#define BRICK_GAME_H
#ifdef __cplusplus
extern "C" {
#endif
// #define None_action 8
typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action,
} UserAction_t;

typedef struct {
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
    int **field;
    int **next;
} GameInfo_t;

GameInfo_t init_empty_gameInfo(int type);

UserAction_t getSignal(int user_input);
#ifdef __cplusplus
}
#endif
#endif  // BRICK_GAME_H
