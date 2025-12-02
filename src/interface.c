#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../include/interface.h"
#include "../include/cliente.h" 
#include "../include/produto.h"
#include "../include/pedido.h"

int altura, comprimento, topo_h, fundo_h;

void calcular_dimensoes() {
    getmaxyx(stdscr, altura, comprimento);
    topo_h = 3; fundo_h = 3;
}

void animacao_transicao(int reverso) {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int meio = max_y / 2;

    attron(A_REVERSE);

    if (!reverso) {
        for(int i = 0; i <= meio; i++) {
            mvwhline(stdscr, i, 0, ' ', max_x);
            mvwhline(stdscr, max_y - 1 - i, 0, ' ', max_x);
            refresh();
            napms(10);
        }
    } else {
        for(int i = 0; i <= meio; i++) {
            mvwhline(stdscr, meio - i, 0, ' ', max_x);
            mvwhline(stdscr, meio + i, 0, ' ', max_x);
            refresh();
            napms(10);
        }
    }

    attroff(A_REVERSE);
    napms(50); 
    clear();   
    refresh();
}

void desenhar_layout_base(char *titulo_topo, char *rodape) {
    clear();
    box(stdscr, 0, 0);
    keypad(stdscr, TRUE); 
    mousemask(BUTTON1_CLICKED | BUTTON1_PRESSED | BUTTON1_DOUBLE_CLICKED, NULL);

    if(has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK); 
        init_pair(2, COLOR_BLUE, COLOR_BLACK); 
        init_pair(3, COLOR_BLACK, COLOR_RED);

        bkgd(COLOR_PAIR(1));
    }

    mvwhline(stdscr, topo_h - 1, 1, ACS_HLINE, comprimento - 2);
    attron(A_BOLD);
    mvprintw(1, (comprimento - strlen(titulo_topo)) / 2, "%s", titulo_topo);
    attroff(A_BOLD);
    mvwhline(stdscr, altura - 3, 1, ACS_HLINE, comprimento - 2);
    mvprintw(altura - 2, 2, "MSG: %s", rodape);
    refresh();
}

void desenhar_janela_popup(char *titulo, char *msg) {
    curs_set(0);
    int h = 12, w = 60;
    WINDOW *win = newwin(h, w, (altura-h)/2, (comprimento-w)/2);
    box(win, 0, 0);
    mvwprintw(win, 1, (w-strlen(titulo))/2, "%s", titulo);
    
    int linha = 3;
    char *token = strtok(msg, "\n");
    while(token != NULL && linha < h-2) {
        mvwprintw(win, linha++, 2, "%s", token);
        token = strtok(NULL, "\n");
    }
    
    mvwprintw(win, h-2, 2, "[Pressione qualquer tecla]");
    wrefresh(win);
    wgetch(win);
    delwin(win);
}

int menu_generico(char *titulo, char *opcoes[], int n_opcoes) {
    calcular_dimensoes();
    desenhar_layout_base(titulo, "Setas: Navegar | ENTER ou Clique: Selecionar");
    curs_set(0);

    int w_menu = 40;
    int h_menu = n_opcoes + 4;
    int start_y = (altura - h_menu) / 2;
    int start_x = (comprimento - w_menu) / 2;

    WINDOW *win = newwin(h_menu, w_menu, start_y, start_x);
    keypad(win, TRUE);
    box(win, 0, 0);
    wbkgd(win, COLOR_PAIR(2));

    int selecionado = 0;
    MEVENT event;

    while(1) {
        for(int i=0; i<n_opcoes; i++) {
            if(i == selecionado) wattron(win, A_REVERSE);
            mvwprintw(win, i+2, 2, " %s ", opcoes[i]);
            wattroff(win, A_REVERSE);
        }
        wrefresh(win);
        
        int ch = wgetch(win);
        switch(ch) {
            case KEY_UP: selecionado = (selecionado == 0) ? n_opcoes-1 : selecionado-1; break;
            case KEY_DOWN: selecionado = (selecionado == n_opcoes-1) ? 0 : selecionado+1; break;
            case 10: delwin(win); return selecionado;
            case 'q': case 27: delwin(win); return -1;
            case KEY_MOUSE:
                if (getmouse(&event) == OK) {
                    if (event.y >= start_y + 2 && event.y < start_y + 2 + n_opcoes) {
                        if (event.x >= start_x && event.x < start_x + w_menu) {
                            int item_clicado = event.y - (start_y + 2);
                            delwin(win);
                            return item_clicado;
                        }
                    }
                }
                break;
        }
    }
}

int formulario_generico(char *titulo, CampoFormulario *campos, int qtd_campos) {
    calcular_dimensoes();
    desenhar_layout_base(titulo, "Setas/Mouse: Mudar Campo | Digite | ENTER: Salvar");
    
    int atual = 0;
    int mostrar_erros = 0;
    MEVENT event;
    curs_set(1); 

    while(1) {
        for(int i=0; i<qtd_campos; i++) {
            int y = topo_h + 2 + (i*3);
            int x_label = 2;
            int x_input = 20; 
            
            mvprintw(y+1, x_label, "%s", campos[i].label);
            
            if(i == atual) {
                attron(COLOR_PAIR(2) | A_BOLD); 
            } else if (mostrar_erros && campos[i].validador && !campos[i].validador(campos[i].buffer)) {
                attron(COLOR_PAIR(3) | A_BOLD); 
            } else {
                attron(COLOR_PAIR(1));
            }
            
            for(int k=0; k<campos[i].largura; k++) {
                mvaddch(y, x_input+k, ACS_HLINE);
                mvaddch(y+2, x_input+k, ACS_HLINE);
            }
            mvaddch(y, x_input, ACS_ULCORNER);
            mvaddch(y, x_input+campos[i].largura-1, ACS_URCORNER);
            mvaddch(y+2, x_input, ACS_LLCORNER);
            mvaddch(y+2, x_input+campos[i].largura-1, ACS_LRCORNER);
            mvaddch(y+1, x_input, ACS_VLINE);
            mvaddch(y+1, x_input+campos[i].largura-1, ACS_VLINE);

            move(y+1, x_input+1);
            for(int k=0; k < campos[i].largura - 2; k++) addch(' '); 

            mvprintw(y+1, x_input+1, "%s", campos[i].buffer);
            
            attroff(COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3) | A_BOLD);
        }
        
        int y_cursor = topo_h + 2 + (atual * 3) + 1;
        int x_cursor = 20 + 1 + strlen(campos[atual].buffer);
        move(y_cursor, x_cursor);
        refresh();
        
        int ch = getch();

        if (ch == KEY_MOUSE) {
            if(getmouse(&event) == OK) {
                if(event.bstate & (BUTTON1_CLICKED | BUTTON1_PRESSED)) {
                    for(int i=0; i<qtd_campos; i++) {
                        int y_campo = topo_h + 2 + (i*3);
                        if(event.y >= y_campo && event.y <= y_campo + 2) {
                            atual = i; 
                            break;
                        }
                    }
                }
            }
        }
        else if (ch == KEY_DOWN || ch == 9) { 
            atual++;
            if (atual >= qtd_campos) atual = 0;
        } 
        else if (ch == KEY_UP) { 
            atual--;
            if (atual < 0) atual = qtd_campos - 1;
        } 
        else if (ch == 27) { 
            curs_set(0);
            return 0;
        } 
        else if (ch == 10) { 
            int ok = 1;
            for(int k=0; k<qtd_campos; k++) {
                if(campos[k].validador && !campos[k].validador(campos[k].buffer)) ok = 0;
            }
            if(ok) {
                curs_set(0);
                return 1;
            }
            else {
                mostrar_erros = 1; 
                beep();
            }
        } 
        else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) { 
            int len = strlen(campos[atual].buffer);
            if(len > 0) campos[atual].buffer[len-1] = '\0';
        } 
        else if (isprint(ch)) { 
            int len = strlen(campos[atual].buffer);
            if(len < campos[atual].max_len - 1) {
                campos[atual].buffer[len] = ch;
                campos[atual].buffer[len+1] = '\0';
            }
        }
    }
}

int lista_scrollable_pesquisavel(char *titulo, char **itens, int qtd_itens, int (*callback_detalhes)(int)) {
    char filtro[50] = "";
    int selecionado_tela = 0;
    int scroll_offset = 0;
    int *indices_filtrados = malloc(qtd_itens * sizeof(int));
    MEVENT event;
    curs_set(1);

    while(1) {
        calcular_dimensoes();
        desenhar_layout_base(titulo, "Digite para filtrar | Clique Seleciona | ENTER: Detalhes");
        
        int qtd_visivel = 0;
        for(int i=0; i<qtd_itens; i++) {
            if(strlen(filtro) == 0 || strstr(itens[i], filtro)) {
                indices_filtrados[qtd_visivel++] = i;
            }
        }
        
        mvprintw(topo_h, 2, "PESQUISAR: %s", filtro);
        int x_pesquisa = 13 + strlen(filtro); 
        mvwhline(stdscr, topo_h+1, 1, ACS_HLINE, comprimento-2);

        int max_linhas = altura - topo_h - fundo_h - 3;
        int inicio = scroll_offset;
        int fim = (scroll_offset + max_linhas > qtd_visivel) ? qtd_visivel : scroll_offset + max_linhas;
        int y_inicial_lista = topo_h + 2;

        for(int i=inicio; i<fim; i++) {
            int real_idx = indices_filtrados[i];
            int y = y_inicial_lista + (i - scroll_offset);
            
            if(i == selecionado_tela) attron(A_REVERSE);
            mvprintw(y, 2, " %-60.60s ", itens[real_idx]);
            attroff(A_REVERSE);
        }
        move(topo_h, x_pesquisa);
        refresh();

        int ch = getch();
        if (ch == KEY_MOUSE) {
            if(getmouse(&event) == OK) {
                if(event.bstate & (BUTTON1_CLICKED | BUTTON1_PRESSED | BUTTON1_DOUBLE_CLICKED)) {
                    if (event.y >= y_inicial_lista && event.y < y_inicial_lista + max_linhas) {
                        int linha_clicada = event.y - y_inicial_lista;
                        int indice_novo = scroll_offset + linha_clicada;
                        if (indice_novo < qtd_visivel) selecionado_tela = indice_novo;
                    }
                }
            }
        }
        else if(ch == KEY_DOWN) {
            if(selecionado_tela < qtd_visivel - 1) {
                selecionado_tela++;
                if(selecionado_tela >= scroll_offset + max_linhas) scroll_offset++;
            }
        } 
        else if(ch == KEY_UP) {
            if(selecionado_tela > 0) {
                selecionado_tela--;
                if(selecionado_tela < scroll_offset) scroll_offset--;
            }
        } 
        else if(ch == 10) { 
            if(qtd_visivel > 0) {
                curs_set(0);
                callback_detalhes(indices_filtrados[selecionado_tela]);
                clear(); 
                curs_set(1);
            }
        } 
        else if(ch == 27) { 
            free(indices_filtrados);
            curs_set(0);
            return -1;
        } 
        else if(isprint(ch)) {
            int l = strlen(filtro);
            if(l < 49) { filtro[l] = ch; filtro[l+1] = 0; }
            selecionado_tela = 0; scroll_offset = 0;
        } 
        else if(ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
            int l = strlen(filtro);
            if(l > 0) filtro[l-1] = 0;
            selecionado_tela = 0; scroll_offset = 0;
        }
    }
}

void menu_principal() {
    char *opcoes[] = {
        "1. Gestao de Clientes",
        "2. Gestao de Produtos",
        "3. Gestao de Pedidos",
        "0. Sair"
    };
    int n_opcoes = 4;
    int rodando = 1;

    animacao_transicao(0);

    while(rodando) {
        int escolha = menu_generico("SISTEMA DE VENDAS", opcoes, n_opcoes);
        
        if (escolha >= 0 && escolha != 3) {
            animacao_transicao(0); 
            
            switch(escolha) {
                case 0: modulo_clientes(); break;
                case 1: modulo_produtos(); break;
                case 2: modulo_pedidos(); break;
            }
            
            animacao_transicao(1); 
        
        } else if (escolha == 3 || escolha == -1) {
            rodando = 0;
        }
    }
}