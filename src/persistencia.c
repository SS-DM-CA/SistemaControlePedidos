#include "persistencia.h"
#include "produto.h"
#include "pedido.h"
#include "cliente.h"
#include <stdio.h>
void carregarProduto(FILE *fpro,Produto *produtos);
void carregarPedidos(FILE *fped,Pedido *pedidos);
void carregarClientes(Cliente *clientes,Cliente *clientes);
void carregarItemPedido(FILE *fitem,ItemPedido *itemsPedidos);
int main(){}

void carregarArquivo(FILE *fpro,FILE *fped, FILE *fcli,FILE *fitem,Produto *produtos, Pedido *pedidos, Cliente *clientes,ItemPedido *itemsPedidos)
    carregarProduto(fpro,produtos);
    carregarPedidos(fped,pedidos);
    carregarItemPedidos(fitem,itemsPedidos);
    //problema por causa da pessoa juridica ou pessoa fisica
    fcli = fopen("Clientes.csv", "r+");
    fscanf(fcli)
    while(fscanf(fcli,"%d, %199[^,], %s, %s, %s, %s, %s")){}
}

int carregarProduto(FILE **fpro,Produto **produtos){
     *fpro=fopen("Produtos.csv","r+");
    if( *fpro== NULL){
      printf("O arquivo Produtos.csv não existe");
      printf("Ele sera criado");
      *fpro = fopen("Produtos.csv","a");
      fclose(*fpro);
      *fpro = fopen("Produtos.csv","r+");
    }
    // o cont serve para ir almentando a posição do vetor
    int cont =0;
    *produtos = (Produto *) realloc(*produtos,(cont+1)*sizeof(Produto));
    while (fscanf(*fpro,"%d, %99[^,], %lf, %d ",&(*produtos)[cont].id,(*produtos)[cont].descricao,&(*produtos)[cont].preco,&(*produtos)[cont].estoque) == 4) {
        cont ++;
        *produtos = (Produto *) realloc(*produtos,(cont+1)*sizeof(Produto));
    }
    return cont;
    //cont =0;
}
int carregarPedidos(FILE **fped,Pedido **pedidos){
    *fped = fopen("Pedidos.csv","r+");
    if(*fped==NULL){
        printf("O arquivo Pedidos.csv não existe");
        printf("Ele sera criado");
        *fped = fopen("Pedidos.csv","a");
        fclose(*fped);
        *fped = fopen("Pedidos.csv","r+");
    }
    int cont =0;
    *pedidos = (Pedido *) realloc(*pedidos,(cont+1)*sizeof(Pedido));
    while (fscanf(*fped,"%d, %d, %s, %lf", &(*pedidos)[cont].id,&(*pedidos)[cont].clienteId, (*pedidos)[cont].data, &(*pedidos)[cont].total)==4){
        cont++;
        *pedidos = (Pedido *) realloc(*pedidos,(cont+1)*sizeof(Pedido));
    }
    return cont;
}

int carregarItemPedido(FILE **fitem,ItemPedido **itemsPedidos){
    *fitem = fopen("ItemPedidos.csv","r+");
    if(fitem==NULL){
        printf("O arquivo ItemPedidos.csv não existe");
        printf("Ele sera criado");
        *fitem = fopen("ItemPedidos.csv","a");
        fclose(*fitem);
        *fitem = fopen("ItemPedidos.csv","r+");
    }
    int cont = 0;
    *itemsPedidos=(ItemPedido *) realloc(*itemsPedidos,(cont+1)*sizeof(ItemPedido));
    while (fscanf(*fitem,"%d, %d, %d, %lf", &(*itemsPedidos)[cont].pedidoId,&(*itemsPedidos)[cont].produtoId, &(*itemsPedidos)[cont].quantidade, &(*itemsPedidos)[cont].subtotal)==4){
        cont++;
        *itemsPedidos=(ItemPedido *) realloc(*itemsPedidos,(cont+1)*sizeof(ItemPedido));
    }
    return cont;
}

