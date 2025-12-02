#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/pedido.h"
#include "../include/produto.h"
#include "../include/cliente.h"
#include "../include/interface.h"
#include "../include/persistencia.h"

Pedido *lista_pedidos = NULL;
ItemPedido *lista_itens = NULL;
int total_pedidos = 0;
int total_itens = 0;

int ped_apenas_num(char *str) {
    if(strlen(str) == 0) return 0;
    for (int i = 0; str[i] != '\0'; i++) if (!isdigit(str[i])) return 0;
    return 1;
}
int validador_ped(char *str) { return strlen(str) > 0; }
int validador_id_ped(char *str) { return (strlen(str) > 0 && ped_apenas_num(str)); }

void sincronizar_pedidos() {
    if (lista_pedidos) { free(lista_pedidos); lista_pedidos = NULL; }
    if (lista_itens) { free(lista_itens); lista_itens = NULL; }
    total_pedidos = carregarPedidos(&lista_pedidos);
    total_itens = carregarItemPedido(&lista_itens);
}

void salvar_tudo_pedido() {
    salvarPedido(lista_pedidos, total_pedidos);
    salvarItemPedido(lista_itens, total_itens);
}

int analisaPedido(int Id, Pedido *pedidos, int tamanhoPed) {
    if(pedidos == NULL || tamanhoPed <= 0) return 2;
    for (int i = 0; i < tamanhoPed; i++) {
        if (Id == pedidos[i].id) return 1;
    }
    return 2;
}

int local_validaCliente(int Id) {
    Cliente *temps = NULL; 
    int qtd = carregarClientes(&temps);
    if(qtd == 0 || temps == NULL) return 2;
    int achou = 2;
    for(int i=0; i<qtd; i++) if(temps[i].id == Id) achou = 1;
    if(temps) free(temps);
    return achou;
}

int local_validaProduto(int Id, double *preco_out) {
    Produto *temps = NULL;
    int qtd = carregarProduto(&temps);
    if(qtd == 0 || temps == NULL) return 2;
    int achou = 2;
    for(int i=0; i<qtd; i++) {
        if(temps[i].id == Id) {
            achou = 1;
            if(preco_out) *preco_out = temps[i].preco;
            break;
        }
    }
    if(temps) free(temps);
    return achou;
}

int obter_id_disponivel_pedido() {
    int candidato = 1;
    while(1) {
        int existe = 0;
        for(int i = 0; i < total_pedidos; i++) {
            if(lista_pedidos[i].id == candidato) {
                existe = 1;
                break;
            }
        }
        if(!existe) return candidato;
        candidato++;
    }
}

void cadastrarItensPedido(int pedidoId) {
    int adicionando = 1;
    while(adicionando) {
        char b_prod[10]="", b_qtd[10]="";
        CampoFormulario campos[] = {
            {"ID Produto:", b_prod, 9, 0, 0, 15, validador_id_ped},
            {"Quantidade:", b_qtd, 9, 1, 0, 15, validador_id_ped}
        };

        if(!formulario_generico("ADICIONAR ITEM (ESC para Sair)", campos, 2)) break;

        int idProd = atoi(b_prod);
        double preco = 0;
        
        if(local_validaProduto(idProd, &preco) == 2) {
            desenhar_janela_popup("ERRO", "Produto nao existe!");
        } else {
            ItemPedido novo_item;
            novo_item.pedidoId = pedidoId;
            novo_item.produtoId = idProd;
            novo_item.quantidade = atoi(b_qtd);
            novo_item.subtotal = novo_item.quantidade * preco;

            total_itens++;
            lista_itens = (ItemPedido *) realloc(lista_itens, total_itens * sizeof(ItemPedido));
            if(lista_itens == NULL) { desenhar_janela_popup("ERRO", "Memoria insuficiente"); return; }
            lista_itens[total_itens-1] = novo_item;
            
            for(int i=0; i<total_pedidos; i++) {
                if(lista_pedidos[i].id == pedidoId) lista_pedidos[i].total += novo_item.subtotal;
            }
            salvar_tudo_pedido();
            desenhar_janela_popup("SUCESSO", "Item adicionado.");
        }
        if(menu_generico("CONTINUAR?", (char*[]){"Adicionar Outro", "Finalizar"}, 2) != 0) adicionando = 0;
    }
}

void cadastrarPedido() {
    sincronizar_pedidos();
    Pedido novo;
    memset(&novo, 0, sizeof(Pedido));
    
    char b_cli[10]="", b_data[12]="";
    
    int id_auto = obter_id_disponivel_pedido();
    char titulo[50]; sprintf(titulo, "NOVO PEDIDO [ID: %d]", id_auto);

    CampoFormulario campos[] = {
        {"ID Cliente:", b_cli, 9, 0, 0, 15, validador_id_ped},
        {"Data:", b_data, 11, 1, 0, 15, validador_ped}
    };

    if(formulario_generico(titulo, campos, 2)) {
        int idCli = atoi(b_cli);
        if(local_validaCliente(idCli) == 2) {
             desenhar_janela_popup("ERRO", "Cliente nao encontrado."); return;
        }

        novo.id = id_auto;
        novo.clienteId = idCli;
        strcpy(novo.data, b_data);
        novo.total = 0.0;

        total_pedidos++;
        lista_pedidos = (Pedido *) realloc(lista_pedidos, total_pedidos * sizeof(Pedido));
        if(lista_pedidos == NULL) { desenhar_janela_popup("ERRO", "Memoria insuficiente"); return; }
        
        lista_pedidos[total_pedidos-1] = novo;
        
        salvar_tudo_pedido();
        cadastrarItensPedido(novo.id);
    }
}

void removerPedido() {
    sincronizar_pedidos();
    char b_id[15]="";
    CampoFormulario campos[] = {{"ID Pedido:", b_id, 14, 0, 0, 15, validador_id_ped}};
    
    if(formulario_generico("REMOVER PEDIDO", campos, 1)) {
        int id = atoi(b_id);
        if(analisaPedido(id, lista_pedidos, total_pedidos) == 2) {
            desenhar_janela_popup("ERRO", "Pedido nao existe."); return;
        }

        if(menu_generico("CONFIRMAR REMOCAO?", (char*[]){"SIM", "NAO"}, 2) == 0) {
             for(int i=0; i<total_pedidos; i++) {
                 if(lista_pedidos[i].id == id) {
                     for(int j=i; j<total_pedidos-1; j++) lista_pedidos[j] = lista_pedidos[j+1];
                     total_pedidos--;
                     lista_pedidos = (Pedido *) realloc(lista_pedidos, total_pedidos * sizeof(Pedido));
                     break;
                 }
             }
             if(total_itens > 0) {
                 ItemPedido *novos_itens = malloc(0);
                 int novo_total = 0;
                 for(int k=0; k<total_itens; k++) {
                     if(lista_itens[k].pedidoId != id) {
                         novo_total++;
                         novos_itens = realloc(novos_itens, novo_total * sizeof(ItemPedido));
                         if(novos_itens) novos_itens[novo_total-1] = lista_itens[k];
                     }
                 }
                 free(lista_itens);
                 lista_itens = novos_itens;
                 total_itens = novo_total;
             }

             salvar_tudo_pedido();
             desenhar_janela_popup("SUCESSO", "Pedido removido.");
        }
    }
}

void removerItemDePedido() {
    sincronizar_pedidos();
    char b_ped[10]="", b_prod[10]="";
    
    CampoFormulario campos[] = {
        {"ID do Pedido:", b_ped, 9, 0, 0, 15, validador_id_ped},
        {"ID do Produto a remover:", b_prod, 9, 1, 0, 15, validador_id_ped}
    };

    if(formulario_generico("REMOVER ITEM", campos, 2)) {
        int idPed = atoi(b_ped);
        int idProd = atoi(b_prod);

        int idx_pedido = -1;
        for(int i=0; i<total_pedidos; i++) {
            if(lista_pedidos[i].id == idPed) {
                idx_pedido = i;
                break;
            }
        }

        if(idx_pedido == -1) {
            desenhar_janela_popup("ERRO", "Pedido nao encontrado.");
            return;
        }

        int encontrou = 0;
        for(int i=0; i<total_itens; i++) {
            if(lista_itens[i].pedidoId == idPed && lista_itens[i].produtoId == idProd) {
                
                lista_pedidos[idx_pedido].total -= lista_itens[i].subtotal;
                if(lista_pedidos[idx_pedido].total < 0) lista_pedidos[idx_pedido].total = 0;

                for(int j=i; j < total_itens - 1; j++) {
                    lista_itens[j] = lista_itens[j+1];
                }
                
                total_itens--;
                lista_itens = (ItemPedido *) realloc(lista_itens, total_itens * sizeof(ItemPedido));
                encontrou = 1;
                break;
            }
        }

        if(encontrou) {
            salvar_tudo_pedido();
            desenhar_janela_popup("SUCESSO", "Item removido e total atualizado.");
        } else {
            desenhar_janela_popup("ERRO", "Item nao encontrado neste pedido.");
        }
    }
}

void montar_detalhes_pedido(Pedido p, char *msg) {
    int off = snprintf(msg, 2048, "PEDIDO %d\nCli: %d Data: %s\nTotal: %.2f\n-- ITENS --\n", p.id, p.clienteId, p.data, p.total);
    for(int i=0; i<total_itens; i++) {
        if(lista_itens[i].pedidoId == p.id) {
            off += snprintf(msg+off, 2048-off, "Prod %d (Qtd %d) = %.2f\n", 
               lista_itens[i].produtoId, lista_itens[i].quantidade, lista_itens[i].subtotal);
            if(off >= 2000) break;
        }
    }
}

void consultarPedidos() {
    sincronizar_pedidos();
    char b_id[15]="";
    CampoFormulario campos[] = {{"ID Pedido:", b_id, 14, 0, 0, 15, validador_id_ped}};

    if(formulario_generico("CONSULTAR PEDIDO", campos, 1)) {
        int id = atoi(b_id);
        if(analisaPedido(id, lista_pedidos, total_pedidos) == 2) {
            desenhar_janela_popup("ERRO", "Pedido nao existe.");
        } else {
            Pedido p;
            for(int i=0; i<total_pedidos; i++) if(lista_pedidos[i].id == id) p = lista_pedidos[i];

            char msg[2048];
            montar_detalhes_pedido(p, msg);
            desenhar_janela_popup("DETALHES", msg);
        }
    }
}

int detalhes_pedido_cb(int index) {
    if(index < 0 || index >= total_pedidos) return 0;
    Pedido p = lista_pedidos[index];
    char msg[2048];
    montar_detalhes_pedido(p, msg);
    desenhar_janela_popup("DETALHES", msg);
    return 1;
}

void listarPedidos() {
    sincronizar_pedidos();
    if(total_pedidos == 0) {
        desenhar_janela_popup("AVISO", "Nenhum pedido.");
        return;
    }
    char **itens = malloc(total_pedidos * sizeof(char*));
    for(int i=0; i<total_pedidos; i++) {
        itens[i] = malloc(150);
        snprintf(itens[i], 150, "PED %d | Cli: %d | Total: %.2f", lista_pedidos[i].id, lista_pedidos[i].clienteId, lista_pedidos[i].total);
    }
    lista_scrollable_pesquisavel("LISTA DE PEDIDOS", itens, total_pedidos, detalhes_pedido_cb);
    for(int i=0; i<total_pedidos; i++) free(itens[i]);
    free(itens);
}

void modulo_pedidos() {
    sincronizar_pedidos();
    int rodando = 1;
    char *opcoes[] = {
        "1. Novo Pedido", 
        "2. Consultar Pedido", 
        "3. Remover Pedido Completo", 
        "4. Remover Item de Pedido", 
        "5. Listar Todos", 
        "6. Voltar"
    };
    
    while(rodando) {
        int op = menu_generico("GESTAO DE PEDIDOS", opcoes, 6);
        
        if(op >= 0 && op != 5) animacao_transicao(0);

        switch(op) {
            case 0: cadastrarPedido(); break;
            case 1: consultarPedidos(); break;
            case 2: removerPedido(); break;
            case 3: removerItemDePedido(); break;
            case 4: listarPedidos(); break;
            case 5: case -1: rodando = 0; break;
        }

        if(op >= 0 && op != 5) animacao_transicao(1);
    }
}