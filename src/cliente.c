#include <stdio.h>
#include "../include/interface.h"
#include <ncurses.h>

typedef struct cliente
{
    char identificador[5];
    char endereco[201];
    char telefone[15];
    char email[101];
}clt;

typedef struct fisica{
    char nome[101];
    char celular[15];
    char cpf[12];
    clt cf;
}fisi;

typedef struct juridica{
    char razao[201];
    char contato[101];
    char cnpj[15];
    clt cj;
}juri;

void cadastro(){
    desenhar_layout("CADASTRO", "PREENCHA TODOS OS CAMPOS E APERTE COMFIRMAR OU Q PARA CANCELAR E VOLTAR");
    mvprintw(10, 2, "Pressione algo para voltar...");
    getch();
}