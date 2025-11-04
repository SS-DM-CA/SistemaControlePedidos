#include <ncurses.h>
#include <string.h>
#define num_op 4
#define altura 10
#define largura 40

char *opcoes[]= {
        "Opção 1",
        "Opçãoooo 2",
        "Opçãooooo 3",
        "Sair"
};

void desenhar(WINDOW *menu_win, int destacado, char *opcoes[]) {
    //Desenho da caixa
    int y=2;
    box(menu_win, 0, 0);
    wattron(menu_win, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(menu_win, 1, (largura - 14) / 2, "MENU PRINCIPAL");
    wattroff(menu_win, COLOR_PAIR(1) | A_BOLD);
    //Mudança do destacado
    for (int i=0; i < num_op; i++) {
        if (i==destacado) {
            wattron(menu_win, COLOR_PAIR(2) | A_BOLD);
            mvwprintw(menu_win, y + i + 1, (largura-26)/2, " %s", opcoes[i]);
            wattroff(menu_win, COLOR_PAIR(2) | A_BOLD);
        }
        else {
            mvwprintw(menu_win, y + i + 1, (largura-26)/2, " %s", opcoes[i]);
        }
    }
    mvwprintw(menu_win, 8, (largura-19)/2, "Use setas e Enter");
    wrefresh(menu_win);
}

void menu() {
    //Inicialização
    initscr();
    clear();
    noecho();
    curs_set(0);
    cbreak();
    int inicio_y=(LINES - altura) / 2;
    int inicio_x=(COLS - largura) / 2;
    WINDOW *menu_win=newwin(altura, largura, inicio_y, inicio_x);
    keypad(menu_win, TRUE);
    int escolha=0;
    int destacado=0;
    int ch;
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_BLUE);
    //LOOP do menu
    while (1) {
        desenhar(menu_win, destacado, opcoes);
        ch=wgetch(menu_win);
        //Mudar destacado, sair e selecionar
        switch (ch) {
            case KEY_UP:
                if (destacado > 0) destacado--;
            break;
            case KEY_DOWN:
                if (destacado < num_op - 1) destacado++;
            break;
            case 10:
                escolha=destacado;
            break;
            case 'q':
            case 'Q': 
                escolha=num_op - 1;
                break;
        }
        if (ch==10 || ch=='q'|| ch=='Q') {
            if (escolha==num_op - 1) {
                break;
            }
            else {
                clear();
                attron(COLOR_PAIR(1) | A_BOLD);
                mvprintw(LINES/2, (COLS - 30)/2, "Você escolheu: %s",
                    opcoes[escolha]);
                attroff(COLOR_PAIR(1) | A_BOLD);
                mvprintw(LINES/2 + 2, (COLS - 30)/2, "Pressione qualquer tecla...");
                refresh();
                getch();
            }
        }
    }
    delwin(menu_win);
    endwin();
    return;
}

int main(){
    menu();
}
