/*
 * @author Azamat G.
 * @date 29.08.2025.
 * @details
 *
 */
#include "../inc/Timer.h"

int is_time_to_shift(struct timeval before, struct timeval after,
                     suseconds_t timer) {
  int res = ((suseconds_t)(after.tv_sec * 1000000 + after.tv_usec) -
             ((suseconds_t)before.tv_sec * 1000000 + before.tv_usec));

  return res > timer;
}
void countTime(Shift_timer* timer) {
  gettimeofday(&timer->after, NULL);

  if (is_time_to_shift(timer->before, timer->after, timer->delay_to_shift)) {
    timer->time_to_shift = true;
  }
}

Shift_timer init_shift_timer() {
  Shift_timer sh_timer = {0};
  gettimeofday(&sh_timer.before, NULL);
  gettimeofday(&sh_timer.after, NULL);
  sh_timer.delay_to_shift = TIME;
  sh_timer.time_to_shift = false;
  return sh_timer;
}

Shift_timer* get_shift_timer_instance() {
  static Shift_timer* sh_timer;
  if (sh_timer == NULL) {
    sh_timer = malloc(sizeof(Shift_timer));

    gettimeofday(&sh_timer->before, NULL);
    gettimeofday(&sh_timer->after, NULL);
    sh_timer->delay_to_shift = TIME * pow(0.9, get_game_info_instance()->level);
    ;
    sh_timer->time_to_shift = false;
  }
  return sh_timer;
}