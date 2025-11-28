#include "../include/interface.h"
#include <ncurses.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);
    cbreak();

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_BLUE);
    }

    menu_principal();

    endwin();
    return 0;
}