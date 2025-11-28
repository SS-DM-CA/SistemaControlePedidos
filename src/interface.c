#include <ncurses.h>
#include <string.h>
#include <locale.h>

int altura, comprimento;
int topo_h, fundo_h, menu_box_w;

char *opcoes_main[] = {
    "1. GESTÃO CLIENTES",
    "2. GESTÃO PRODUTOS",
    "3. NOVO PEDIDO",
    "4. RELATÓRIOS",
    "0. SAIR DO SISTEMA"
};

char *opcoes_clientes[] = {
    "Cadastrar Cliente",
    "Consultar Cliente",
    "Listar Clientes",
    "Remover Cliente",
    "Voltar"
};

char *opcoes_produtos[] = { "Listar Produtos", "Novo Produto", "Voltar" };
char *opcoes_pedidos[] = { "Novo Pedido", "Listar Pedidos", "Voltar" };

void calcular_dimensoes() {
    getmaxyx(stdscr, altura, comprimento);

    topo_h = altura * 0.10;
    if (topo_h < 3) topo_h = 3;

    fundo_h = altura * 0.10;
    if (fundo_h < 3) fundo_h = 3;

    menu_box_w = comprimento * 0.40;
    if (menu_box_w < 25) menu_box_w = 25;
}

void desenhar_layout(char *titulo_topo) {
    clear();
    mvwhline(stdscr, 0, 0, ACS_HLINE, comprimento);
    mvwhline(stdscr, topo_h - 1, 0, ACS_HLINE, comprimento);
    mvwvline(stdscr, 0, 0, ACS_VLINE, topo_h);
    mvwvline(stdscr, 0, comprimento - 1, ACS_VLINE, topo_h);
    mvaddch(0, 0, ACS_ULCORNER);
    mvaddch(0, comprimento - 1, ACS_URCORNER);
    mvaddch(topo_h - 1, 0, ACS_LLCORNER);
    mvaddch(topo_h - 1, comprimento - 1, ACS_LRCORNER);

    attron(A_BOLD);
    mvprintw(topo_h / 2, (comprimento - strlen(titulo_topo)) / 2, "%s", titulo_topo);
    attroff(A_BOLD);

    int footer_y = altura - fundo_h;
    mvwhline(stdscr, footer_y, 0, ACS_HLINE, comprimento);
    mvwhline(stdscr, altura - 1, 0, ACS_HLINE, comprimento);
    mvwvline(stdscr, footer_y, 0, ACS_VLINE, fundo_h);
    mvwvline(stdscr, footer_y, comprimento - 1, ACS_VLINE, fundo_h);
    mvaddch(footer_y, 0, ACS_ULCORNER);
    mvaddch(footer_y, comprimento - 1, ACS_URCORNER);
    mvaddch(altura - 1, 0, ACS_LLCORNER);
    mvaddch(altura - 1, comprimento - 1, ACS_LRCORNER);

    char *instrucoes = "Use as setas [^][v] para navegar, [ENTER] para acessar e Q para sair.";
    mvprintw(footer_y + (fundo_h/2), 2, "%s", instrucoes);

    refresh();
}

void desenhar_menu_interno(WINDOW *menu_win, int destacado, char *opcoes[], int n_opcoes) {
    box(menu_win, 0, 0);

    char *titulo_menu = "MENU";
    mvwprintw(menu_win, 1, (menu_box_w - strlen(titulo_menu))/2, "%s", titulo_menu);
    mvwhline(menu_win, 2, 1, ACS_HLINE, menu_box_w - 2);

    int linha_inicial_opcoes = 3;

    for (int i = 0; i < n_opcoes - 1; i++) {
        if (i == destacado) {
            wattron(menu_win, COLOR_PAIR(2) | A_BOLD);
            mvwprintw(menu_win, linha_inicial_opcoes + i, 2, "> %s", opcoes[i]);
            wattroff(menu_win, COLOR_PAIR(2) | A_BOLD);
        } else {
            mvwprintw(menu_win, linha_inicial_opcoes + i, 2, "  %s", opcoes[i]);
        }
    }

    int linha_separador_final = linha_inicial_opcoes + (n_opcoes - 1);
    mvwhline(menu_win, linha_separador_final, 1, ACS_HLINE, menu_box_w - 2);
    mvwaddch(menu_win, linha_separador_final, 0, ACS_LTEE);
    mvwaddch(menu_win, linha_separador_final, menu_box_w - 1, ACS_RTEE);

    int i_ultima = n_opcoes - 1;
    if (i_ultima == destacado) {
         wattron(menu_win, COLOR_PAIR(2) | A_BOLD);
         mvwprintw(menu_win, linha_separador_final + 1, 2, "> %s", opcoes[i_ultima]);
         wattroff(menu_win, COLOR_PAIR(2) | A_BOLD);
    } else {
         mvwprintw(menu_win, linha_separador_final + 1, 2, "  %s", opcoes[i_ultima]);
    }

    wrefresh(menu_win);
}


void movimento(WINDOW *menu_win, int *destacado, int *escolha, int n_opcoes){
    int ch;
    ch = wgetch(menu_win);

    switch (ch) {
        case KEY_UP:
            if (*destacado == 0) *destacado = n_opcoes - 1; else (*destacado)--;
            break;
        case KEY_DOWN:
            if (*destacado == n_opcoes - 1) *destacado = 0; else (*destacado)++;
            break;
        case 10: case 13: case KEY_ENTER:
            *escolha = *destacado; break;
        case 'q': case 'Q':
            *escolha = n_opcoes - 1; break;
        case KEY_RESIZE:
            *escolha = -99;
            break;
    }
}


int menu_generico(char *titulo_janela, char *opcoes[], int n_opcoes) {
    calcular_dimensoes();
    desenhar_layout(titulo_janela);

    int win_altura_menu, win_comprimento_menu, espaco_vertical_disponivel, start_y_menu, start_x_menu;

    WINDOW *menu_win = NULL;

    int destacado = 0;
    int escolha = -1;

    while (1) {
        if (menu_win == NULL) {
            win_altura_menu = n_opcoes + 5;
            win_comprimento_menu = menu_box_w;
            espaco_vertical_disponivel = altura - topo_h - fundo_h;
            start_y_menu = topo_h + (espaco_vertical_disponivel - win_altura_menu) / 2;
            start_x_menu = (comprimento - win_comprimento_menu) / 2;
            menu_win = newwin(win_altura_menu, win_comprimento_menu, start_y_menu, start_x_menu);
            keypad(menu_win, TRUE);
        }

        desenhar_menu_interno(menu_win, destacado, opcoes, n_opcoes);
        movimento(menu_win, &destacado, &escolha, n_opcoes);

        if (escolha == -99) {
            delwin(menu_win);
            menu_win = NULL;
            refresh();
            calcular_dimensoes();
            desenhar_layout(titulo_janela);
            escolha = -1;
            continue;
        }

        if (escolha != -1) break;
    }
    if (menu_win) {
        wclear(menu_win);
        wrefresh(menu_win);
        delwin(menu_win);
    }

    return escolha;
}
//função para teste, pode apagar
void mostrar_tela_teste(char *titulo_acao) {
    int ch;
    do {
        calcular_dimensoes();
        desenhar_layout(titulo_acao);
        WINDOW *msg_win = newwin(5, comprimento-4, altura/2 - 2, 2);
        box(msg_win, 0,0);
        mvwprintw(msg_win, 2, 2, "Funcao '%s' em desenvolvimento...", titulo_acao);
        mvwprintw(msg_win, 3, 2, "Pressione qualquer tecla para voltar.");
        wrefresh(msg_win);
        ch = getch();
        delwin(msg_win);
    } while (ch == KEY_RESIZE);
}

void modulo_clientes() {
    int n_opcoes = sizeof(opcoes_clientes) / sizeof(opcoes_clientes[0]);
    int rodando = 1;
    while(rodando) {
        int escolha = menu_generico("MÓDULO: GESTÃO DE CLIENTES", opcoes_clientes, n_opcoes);
        if (escolha == n_opcoes - 1) rodando = 0;
        else mostrar_tela_teste(opcoes_clientes[escolha]);
    }
}

void modulo_produtos() {
     int n_opcoes = sizeof(opcoes_produtos)/sizeof(opcoes_produtos[0]);
     int rodando = 1; 
     while(rodando) {
         if(menu_generico("MÓDULO: PRODUTOS", opcoes_produtos, n_opcoes) == n_opcoes-1) rodando = 0;
     }
}
void modulo_pedidos() {
     int n_opcoes = sizeof(opcoes_pedidos)/sizeof(opcoes_pedidos[0]);
     int rodando = 1; while(rodando) {
         if(menu_generico("MÓDULO: PEDIDOS", opcoes_pedidos, n_opcoes) == n_opcoes-1) rodando = 0;
     }
}

void menu_principal() {
    int n_opcoes_main = sizeof(opcoes_main) / sizeof(opcoes_main[0]);
    int rodando = 1;

    while (rodando) {
        int escolha = menu_generico("SISTEMA DE GESTÃO COMERCIAL - NCURSES", opcoes_main, n_opcoes_main);

        switch (escolha){
            case 0: modulo_clientes(); break;
            case 1: modulo_produtos(); break;
            case 2: modulo_pedidos(); break;
            case 3: mostrar_tela_teste("Relatorios"); break;
            case 4:
                rodando = 0;
                break;
        }
    }
}


int main() {
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