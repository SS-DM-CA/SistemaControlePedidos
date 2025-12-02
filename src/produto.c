#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/produto.h"
#include "../include/pedido.h"
#include "../include/interface.h"
#include "../include/persistencia.h"

Produto *lista_produtos = NULL;
int total_produtos = 0;

void sincronizar_produtos() {
    if (lista_produtos != NULL) { free(lista_produtos); lista_produtos = NULL; }
    total_produtos = carregarProduto(&lista_produtos);
}

void salvar_alteracoes_produto() {
    salvarProduto(lista_produtos, total_produtos);
}

int analisaProduto(int Id, Produto *produtos, int tamanhoProd) {
    if(produtos == NULL || tamanhoProd <= 0) return 2;
    for (int i = 0; i < tamanhoProd; i++) {
        if (Id == produtos[i].id) return 1;
    }
    return 2;
}

int apenas_num(char *str) {
    for (int i = 0; str[i] != '\0'; i++) if (!isdigit(str[i])) return 0;
    return 1;
}
int validador_prod(char *str) { return strlen(str) > 0; }
int validador_id_produto(char *str) { return (strlen(str) > 0 && apenas_num(str)); }

int obter_id_disponivel_produto() {
    int candidato = 1;
    while(1) {
        int existe = 0;
        for(int i = 0; i < total_produtos; i++) {
            if(lista_produtos[i].id == candidato) {
                existe = 1;
                break;
            }
        }
        if(!existe) return candidato;
        candidato++;
    }
}

void cadastrarProduto() {
    sincronizar_produtos();
    Produto novo;
    memset(&novo, 0, sizeof(Produto));
    
    char b_desc[100]="", b_preco[20]="", b_est[20]="";

    int id_auto = obter_id_disponivel_produto();
    char titulo[50]; sprintf(titulo, "NOVO PRODUTO [ID: %d]", id_auto);

    CampoFormulario campos[] = {
        {"Descricao:", b_desc, 99, 0, 0, 40, validador_prod},
        {"Preco:", b_preco, 19, 1, 0, 20, validador_prod},
        {"Estoque:", b_est, 19, 2, 0, 20, validador_prod}
    };

    if (formulario_generico(titulo, campos, 3)) {
        novo.id = id_auto;
        strcpy(novo.descricao, b_desc);
        novo.preco = atof(b_preco);
        novo.estoque = atoi(b_est);

        total_produtos++;
        lista_produtos = (Produto *) realloc(lista_produtos, total_produtos * sizeof(Produto));
        if (lista_produtos == NULL) { desenhar_janela_popup("ERRO", "Falha memoria"); return; }
        
        lista_produtos[total_produtos - 1] = novo;
        
        salvar_alteracoes_produto();
        desenhar_janela_popup("SUCESSO", "Produto cadastrado!");
    }
}

void consultarProduto() {
    sincronizar_produtos();
    char b_id[15] = "";
    CampoFormulario campos[] = { {"ID para consultar:", b_id, 14, 0, 0, 15, validador_id_produto} };

    if(formulario_generico("CONSULTAR PRODUTO", campos, 1)) {
        int id = atoi(b_id);
        if (analisaProduto(id, lista_produtos, total_produtos) == 2) {
            desenhar_janela_popup("ERRO", "Produto nao existe.");
        } else {
            for (int i = 0; i < total_produtos; i++) {
                if (lista_produtos[i].id == id) {
                    char msg[300];
                    snprintf(msg, 300, "ID: %d\nDesc: %s\nPreco: %.2f\nEstoque: %d", 
                             lista_produtos[i].id, lista_produtos[i].descricao, 
                             lista_produtos[i].preco, lista_produtos[i].estoque);
                    desenhar_janela_popup("DADOS DO PRODUTO", msg);
                    break;
                }
            }
        }
    }
}

void removerProduto() {
    sincronizar_produtos();
    char b_id[15] = "";
    CampoFormulario campos[] = { {"ID para remover:", b_id, 14, 0, 0, 15, validador_id_produto} };

    if (formulario_generico("REMOVER PRODUTO", campos, 1)) {
        int id = atoi(b_id);

        if (analisaProduto(id, lista_produtos, total_produtos) == 2) {
            desenhar_janela_popup("ERRO", "Produto nao encontrado.");
            return;
        }

        ItemPedido *temp_itens = NULL;
        int qtd_itens = carregarItemPedido(&temp_itens);
        for (int i = 0; i < qtd_itens; i++) {
            if (temp_itens[i].produtoId == id) {
                desenhar_janela_popup("BLOQUEADO", "Produto em uso em pedidos.");
                if(temp_itens) free(temp_itens);
                return;
            }
        }
        if(temp_itens) free(temp_itens);

        int opcao = menu_generico("CONFIRMAR?", (char*[]){"SIM", "NAO"}, 2);
        if (opcao == 0) { 
             for (int i = 0; i < total_produtos; i++) {
                if (lista_produtos[i].id == id) {
                    for (int j = i; j < total_produtos - 1; j++) lista_produtos[j] = lista_produtos[j + 1];
                    total_produtos--;
                    lista_produtos = (Produto *) realloc(lista_produtos, total_produtos * sizeof(Produto));
                    salvar_alteracoes_produto();
                    desenhar_janela_popup("SUCESSO", "Produto removido.");
                    return;
                }
            }
        }
    }
}

int tela_detalhes_produto_cb(int index) {
    if (index < 0 || index >= total_produtos) return 0;
    Produto p = lista_produtos[index];
    char msg[200];
    snprintf(msg, 200, "ID: %d\nItem: %s\nPreco: %.2f\nEstoque: %d", p.id, p.descricao, p.preco, p.estoque);
    desenhar_janela_popup("DETALHES", msg);
    return 1;
}

void listarProduto() {
    sincronizar_produtos();
    if (total_produtos == 0) {
        desenhar_janela_popup("AVISO", "Nenhum produto.");
        return;
    }
    char **itens = malloc(total_produtos * sizeof(char*));
    for (int i = 0; i < total_produtos; i++) {
        itens[i] = malloc(150);
        snprintf(itens[i], 150, "[%d] %-20s | R$ %.2f", lista_produtos[i].id, lista_produtos[i].descricao, lista_produtos[i].preco);
    }
    lista_scrollable_pesquisavel("LISTA DE PRODUTOS", itens, total_produtos, tela_detalhes_produto_cb);
    for (int i = 0; i < total_produtos; i++) free(itens[i]);
    free(itens);
}

void modulo_produtos() {
    sincronizar_produtos();
    int rodando = 1;
    char *opcoes[] = {"1. Cadastrar Produto", "2. Consultar Produto", "3. Remover Produto", "4. Listar Todos", "5. Voltar"};
    while (rodando) {
        int esc = menu_generico("GESTAO DE PRODUTOS", opcoes, 5);
        if(esc >= 0 && esc != 4) animacao_transicao(0);
        switch (esc) {
            case 0: cadastrarProduto(); break;
            case 1: consultarProduto(); break;
            case 2: removerProduto(); break;
            case 3: listarProduto(); break;
            case 4: case -1: rodando = 0; break;
        }
        if(esc >= 0 && esc != 4) animacao_transicao(1);
    }
}