#include <ncurses.h>
#include <string.h>
#include <locale.h>

int altura, comprimento;

char *opcoes_main[] = {
    "Cliente",
    "Produto",
    "Pedido",
    "Sair"
};
char *opcoes_clientes[] = {
    "Cadastrar",
    "Consultar",
    "Analisar",
    "Listar",
    "Remover"
};
void desenhar(WINDOW *menu_win, int destacado, char *opcoes[], int n_opcoes, int x, int y) {
    box(menu_win, 0, 0);
    int tamanho_max = 0;
    for (int i = 0; i < n_opcoes; i++) {
        int len = strlen(opcoes[i]);
        if (len > tamanho_max) {
            tamanho_max= len;
        }
    }
    for (int i = 0; i < n_opcoes; i++) {
        if (i == destacado) {
            wattron(menu_win, COLOR_PAIR(2) | A_BOLD);
            mvwprintw(menu_win, y/2 - n_opcoes/2 + i, (x - (tamanho_max + 2))/2, "%s ", opcoes[i]);
            wattroff(menu_win, COLOR_PAIR(2) | A_BOLD);
        } else {
            mvwprintw(menu_win, y/2 - n_opcoes/2 + i, (x - (tamanho_max + 2))/2, "%s ", opcoes[i]);
        }
    }
    wrefresh(menu_win);
}
void movimento(WINDOW *menu_win, int *destacado, int *escolha, int n_opcoes){
    int ch;
    ch = wgetch(menu_win);
        switch (ch) {
            case KEY_UP:
                if (*destacado == 0) {
                    *destacado = n_opcoes-1;
                }
                else {
                    *destacado = *destacado - 1;
                }
                break;
            case KEY_DOWN:
                if (*destacado == n_opcoes-1) {
                    *destacado = 0;
                }
                else {
                    *destacado = *destacado + 1;
                }
                break;
            case 10: // Enter (Line Feed)
            case 13: // Enter (Carriage Return)
            case KEY_ENTER:
                *escolha = *destacado;
                break;
            case 'q':
            case 'Q':
                *escolha = n_opcoes - 1;
                break;
        }
}
void menu() {
    setlocale(LC_ALL, "");
    initscr();
    clear();
    noecho();
    curs_set(0);
    cbreak();
    getmaxyx(stdscr, altura, comprimento);
    int win_altura_menu = altura * 0.8;
    int win_comprimento_menu = comprimento * 0.7;
    int start_y_menu = (altura - win_altura_menu) / 2;
    int start_x_menu = (comprimento - win_comprimento_menu) / 2;
    WINDOW *menu_win = newwin(win_altura_menu, win_comprimento_menu, start_y_menu, start_x_menu);
    keypad(menu_win, TRUE);
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_BLUE); 
    int n_opcoes_main = sizeof(opcoes_main) / sizeof(opcoes_main[0]);
    int destacado = 0;
    int escolha = -1;
    while (1) {
        desenhar(menu_win, destacado, opcoes_main, n_opcoes_main, win_comprimento_menu, win_altura_menu);
        movimento(menu_win, &destacado, &escolha, n_opcoes_main);
        switch (escolha){
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                wclear(menu_win);
                delwin(menu_win);
                endwin();
                return;
        }
    }
    delwin(menu_win);
    endwin();
}

int main() {
    menu();
    return 0;
}