#include <stdio.h>
#include "gui/cli/cli.h"
int main(){
    View* views = (View*)malloc(sizeof(View));
    init_ncurses(views);
}