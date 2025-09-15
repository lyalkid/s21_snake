/*
 * @author Azamat G.
 * @date 29.08.2025.
 * @details
 *
 */
#include "../inc/timer.h"

int is_time_to_shift(time_val before, time_val after, long timer) {
  long res = (after.tv_sec * 1000000 + after.tv_usec) -
             (before.tv_sec * 1000000 + before.tv_usec);

  return res > timer;
}
void countTime(Shift_timer* timer) {
  get_time(&timer->after);

  if (is_time_to_shift(timer->before, timer->after, timer->delay_to_shift)) {
    timer->time_to_shift = true;
  }
}

Shift_timer init_shift_timer() {
  Shift_timer timer = {0};
  get_time(&timer.before);
  get_time(&timer.after);
  timer.delay_to_shift = TIME;
  timer.time_to_shift = false;
  return timer;
}

int get_time(time_val* tp) {
  if (!tp) return -1;

  // clock() возвращает время с начала выполнения программы в тактах
  clock_t t = clock();
  double seconds = (double)t / CLOCKS_PER_SEC;

  tp->tv_sec = (long)seconds;
  tp->tv_usec = (long)((seconds - tp->tv_sec) * 1000000);
  return 0;
}

// Shift_timer* get_shift_timer_instance() {
//   static Shift_timer* sh_timer;
//   if (sh_timer == NULL) {
//     sh_timer = malloc(sizeof(Shift_timer));
//
//     gettimeofday(&sh_timer->before, NULL);
//     gettimeofday(&sh_timer->after, NULL);
//     sh_timer->delay_to_shift = TIME * pow(0.9,
//     get_game_info_instance()->level);
//     ;
//     sh_timer->time_to_shift = false;
//   }
//   return sh_timer;
// }