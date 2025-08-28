/*
 * @author Azamat G.
 * @date 15.08.2025.
 * @details
 *
 */

#include "utilities.h"

#include "../tetris/inc/tetris.h"

int **malloc_array(int rows, int cols) {
    int **field = malloc(sizeof(int *) * rows);
    for (int i = 0; i < rows; i++) {
        field[i] = calloc(cols, sizeof(int));
    }
    null_array(field, rows, cols);
    return field;
}

void free_array(int **field, int rows) {
    for (int i = 0; i < rows; i++) {
        if (field[i] != NULL) {
            free(field[i]);
        }
    }
    if (field != NULL) free(field);
}

void null_array(int **field, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            field[i][j] = 0;
        }
    }
}

void bin_array(int **src, int **dist, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (src[i][j] == 0)
                dist[i][j] = 0;
            else
                dist[i][j] = 1;
        }
    }
}

void init_array(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = 0;
    }
}

// получает длину числа без ведущих нулей
int get_real_len_of_number(const int a[], int size) {
    int i = 0;
    int count = 0;
    for (i = size - 1; i >= 0; i--) {
        if (a[i] == 0) {
            count++;
        } else {
            break;
        }
    }

    return size - count;
}

void print_array(int **array, int max_x, int min_x) {
    printf("max_x = %d, min_x = %d\n", max_x, min_x);
    // system("clear");
    for (int i = 0; i < WIDTH; i++) {
        if (i <= max_x && i >= min_x) {
            printf("# ");
        } else {
            printf("- ");
        }
    }
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (array[i][j]) {
                printf("%c ", '*');
            } else {
                printf("  ");
            }
        }


        printf("\n");
    }
    for (int i = 0; i < WIDTH; i++) {
        if (i <= max_x && i >= min_x) {
            printf("# ");
        } else {
            printf("- ");
        }
    }
    printf("\n");
    printf("max_x = %d, min_x = %d\n", max_x, min_x);
}

void overlay_array(int **field, int **next, int max_x, int min_x) {
    for (int j = 0; j < WIDTH; j++) {
        printf("%d ", j);
    }
    printf("\n");
    for (int i = 0; i < WIDTH; i++) {
        if (i <= max_x && i >= min_x) {
            printf("##");
        } else {
            printf("--");
        }
    }
    printf("\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int res = field[i][j] + next[i][j];
            if (res != 0)
                // printf("%d ", res);
                printf("##");
            else
                printf("  ");
        }
        printf("| %d\n", i);
    }
    for (int i = 0; i < WIDTH; i++) {
        if (i <= max_x && i >= min_x) {
            printf("##");
        } else {
            printf("--");
        }
    }
    printf("\n");
}


int findIndex(const int array[], int size, int i) {
    int res = 0;
    for (int k = 0; k < size; k++) {
        if (array[k] == i) {
            res = k;
            break;
        }
    }
    return res;
}

int get_min(const int a, const int b) { return a > b ? b : a; }

int get_max(const int a, const int b) { return a < b ? b : a; }
