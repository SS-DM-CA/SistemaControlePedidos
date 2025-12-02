#include "../include/produto.h"
#include "../include/pedido.h"
#include "../include/cliente.h"
#include "../include/persistencia.h"
#include "../include/interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void garantir_pasta_data() {
    struct stat st = {0};
    if (stat("data", &st) == -1) {
        #ifdef _WIN32
            _mkdir("data");
        #else
            mkdir("data", 0700);
        #endif
    }
}

void ler_campo(char *linha, char *dest, int tamanho_max, int *cursor) {
    int i = 0;
    while (linha[*cursor] != ';' && linha[*cursor] != '\n' && linha[*cursor] != '\0') {
        if (i < tamanho_max - 1) {
            dest[i] = linha[*cursor];
            i++;
        }
        (*cursor)++;
    }
    dest[i] = '\0';
    if (linha[*cursor] == ';') (*cursor)++; 
}

void salvarArquivo(Produto *produtos, Pedido *pedidos, Cliente *clientes, ItemPedido *itemsPedidos,
                   int tamanhoProd, int tamanhoPed, int tamanhoItemPed, int tamanhoCli){
    salvarProduto(produtos, tamanhoProd);
    salvarPedido(pedidos, tamanhoPed);
    salvarItemPedido(itemsPedidos, tamanhoItemPed);
    salvarCliente(clientes, tamanhoCli);
}

void salvarProduto(Produto *produtos, int tamanhoProd){
    garantir_pasta_data();
    FILE *f = fopen("data/Produtos.csv", "w"); 
    if(!f) return;
    for(int i=0; i<tamanhoProd; i++) 
        fprintf(f, "%d;%s;%lf;%d\n", produtos[i].id, produtos[i].descricao, produtos[i].preco, produtos[i].estoque);
    fclose(f);
}

void salvarPedido(Pedido *pedidos, int tamanhoPed){
    garantir_pasta_data();
    FILE *f = fopen("data/Pedidos.csv", "w");
    if(!f) return;
    for(int i=0; i<tamanhoPed; i++) 
        fprintf(f, "%d;%d;%s;%lf\n", pedidos[i].id, pedidos[i].clienteId, pedidos[i].data, pedidos[i].total);
    fclose(f);
}

void salvarCliente(Cliente *clientes, int tamanhoCli){
    garantir_pasta_data();
    FILE *f = fopen("data/Clientes.csv", "w");
    if(!f) return;
    for(int i=0; i<tamanhoCli; i++) {
        fprintf(f, "%d;%s;%s;%s;%s;%s;%s\n", 
                clientes[i].id, 
                clientes[i].endereco, 
                strlen(clientes[i].telefone) > 0 ? clientes[i].telefone : "", 
                clientes[i].email, 
                clientes[i].nome, 
                strlen(clientes[i].contato) > 0 ? clientes[i].contato : "", 
                clientes[i].identidade);
    }
    fclose(f);
}

void salvarItemPedido(ItemPedido *itemsPedidos, int tamanhoItemPed){
    garantir_pasta_data();
    FILE *f = fopen("data/ItemPedidos.csv", "w");
    if(!f) return;
    for(int i=0; i<tamanhoItemPed; i++) 
        fprintf(f, "%d;%d;%d;%lf\n", itemsPedidos[i].pedidoId, itemsPedidos[i].produtoId, itemsPedidos[i].quantidade, itemsPedidos[i].subtotal);
    fclose(f);
}

int carregarClientes(Cliente **clientes){
    garantir_pasta_data();
    *clientes = NULL; 
    
    FILE *f = fopen("data/Clientes.csv", "r"); 
    if(f == NULL) return 0;
    
    int cont = 0;
    char linha[1024];

    while(fgets(linha, sizeof(linha), f)) {
        if(strlen(linha) < 5) continue; 

        Cliente *temp_ptr = (Cliente *) realloc(*clientes, (cont+1)*sizeof(Cliente));
        if (temp_ptr == NULL) {
            fclose(f);
            return cont;
        }
        *clientes = temp_ptr;

        Cliente *c = &(*clientes)[cont]; 
        int cursor = 0;
        char buffer_id[20];

        ler_campo(linha, buffer_id, 20, &cursor); 
        c->id = atoi(buffer_id);
        ler_campo(linha, c->endereco, 201, &cursor);
        ler_campo(linha, c->telefone, 20, &cursor);
        ler_campo(linha, c->email, 101, &cursor);
        ler_campo(linha, c->nome, 201, &cursor);
        ler_campo(linha, c->contato, 101, &cursor);
        ler_campo(linha, c->identidade, 21, &cursor);

        cont++;
    }
    fclose(f);
    return cont;
}

int carregarProduto(Produto **produtos){
    garantir_pasta_data();
    *produtos = NULL;

    FILE *f = fopen("data/Produtos.csv", "r");
    if(f == NULL) return 0;

    int cont = 0;
    char linha[1024];

    while(fgets(linha, sizeof(linha), f)) {
        if(strlen(linha) < 5) continue;

        *produtos = (Produto *) realloc(*produtos, (cont+1)*sizeof(Produto));
        Produto *p = &(*produtos)[cont];
        
        int cursor = 0;
        char buf_id[20], buf_preco[20], buf_est[20];

        ler_campo(linha, buf_id, 20, &cursor); p->id = atoi(buf_id);
        ler_campo(linha, p->descricao, 100, &cursor);
        ler_campo(linha, buf_preco, 20, &cursor); p->preco = atof(buf_preco);
        ler_campo(linha, buf_est, 20, &cursor); p->estoque = atoi(buf_est);

        cont++;
    }
    fclose(f);
    return cont;
}

int carregarPedidos(Pedido **pedidos){
    garantir_pasta_data();
    *pedidos = NULL;

    FILE *f = fopen("data/Pedidos.csv", "r");
    if(f == NULL) return 0;

    int cont = 0;
    char linha[1024];

    while(fgets(linha, sizeof(linha), f)){
        if(strlen(linha) < 5) continue;

        *pedidos = (Pedido *) realloc(*pedidos, (cont+1)*sizeof(Pedido));
        Pedido *p = &(*pedidos)[cont];

        int cursor = 0;
        char buf_id[20], buf_cli[20], buf_total[30];

        ler_campo(linha, buf_id, 20, &cursor); p->id = atoi(buf_id);
        ler_campo(linha, buf_cli, 20, &cursor); p->clienteId = atoi(buf_cli);
        ler_campo(linha, p->data, 11, &cursor);
        ler_campo(linha, buf_total, 30, &cursor); p->total = atof(buf_total);

        cont++;
    }
    fclose(f);
    return cont;
}

int carregarItemPedido(ItemPedido **itemsPedidos){
    garantir_pasta_data();
    *itemsPedidos = NULL;

    FILE *f = fopen("data/ItemPedidos.csv", "r");
    if(f == NULL) return 0;

    int cont = 0;
    char linha[1024];

    while(fgets(linha, sizeof(linha), f)){
        if(strlen(linha) < 5) continue;

        *itemsPedidos = (ItemPedido *) realloc(*itemsPedidos, (cont+1)*sizeof(ItemPedido));
        ItemPedido *ip = &(*itemsPedidos)[cont];

        int cursor = 0;
        char buf_ped[20], buf_prod[20], buf_qtd[20], buf_sub[30];

        ler_campo(linha, buf_ped, 20, &cursor); ip->pedidoId = atoi(buf_ped);
        ler_campo(linha, buf_prod, 20, &cursor); ip->produtoId = atoi(buf_prod);
        ler_campo(linha, buf_qtd, 20, &cursor); ip->quantidade = atoi(buf_qtd);
        ler_campo(linha, buf_sub, 30, &cursor); ip->subtotal = atof(buf_sub);

        cont++;
    }
    fclose(f);
    return cont;
}