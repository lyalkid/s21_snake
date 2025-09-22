/*
 * @author Azamat G.
 * @date 29.08.2025.
 * @details
 *
 */

#ifndef TIMER_H
#define TIMER_H
#ifdef __cplusplus
extern "C" {
#endif
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define TIME 750000  // 1 second

typedef struct {
  long tv_sec;
  long tv_usec;
} time_val;

typedef struct {
  time_val before;
  time_val after;
  long delay_to_shift;  // через какое время делать shift
  bool time_to_shift;  // показывает нужно ли делать shift
} Shift_timer;

Shift_timer init_shift_timer();
// Shift_timer *get_shift_timer_instance();

int is_time_to_shift(time_val before, time_val after, long timer);

void countTime(Shift_timer *timer);
#include <stdint.h>

int get_time(time_val *tp);
#ifdef __cplusplus
}
#endif
#endif  // TIMER_H
