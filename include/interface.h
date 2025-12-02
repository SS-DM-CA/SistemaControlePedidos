#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>

typedef struct {
    char *label;
    char *buffer;
    int max_len;
    int r, c;
    int largura;
    int (*validador)(char*);
} CampoFormulario;

void calcular_dimensoes();
void desenhar_layout_base(char *titulo_topo, char *rodape);
void desenhar_janela_popup(char *titulo, char *msg);

void animacao_transicao(int reverso);

int formulario_generico(char *titulo, CampoFormulario *campos, int qtd_campos);
int lista_scrollable_pesquisavel(char *titulo, char **itens, int qtd_itens, int (*callback_detalhes)(int));
int menu_generico(char *titulo, char *opcoes[], int n_opcoes);

void menu_principal();

#endif