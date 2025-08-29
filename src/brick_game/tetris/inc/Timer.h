/*
 * @author Azamat G.
 * @date 29.08.2025.
 * @details
 *
 */

#ifndef TIMER_H
#define TIMER_H
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#define TIME 1000000  // 2 seconds
#include "../../brick_game.h"
typedef struct {
  struct timeval before;
  struct timeval after;
  suseconds_t delay_to_shift;  // через какое время делать shift
  bool time_to_shift;  // показывает нужно ли делать shift
} Shift_timer;

int is_time_to_shift(struct timeval before, struct timeval after,
                     suseconds_t timer);

void countTime(Shift_timer *timer);

void init_timer(Shift_timer *timer);

Shift_timer init_shift_timer();
Shift_timer *get_shift_timer_instance();

#endif  // TIMER_H
