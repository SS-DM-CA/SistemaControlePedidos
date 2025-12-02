#include "../include/interface.h"
#include <ncurses.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);
    cbreak();

    menu_principal();

    endwin();
    return 0;
}