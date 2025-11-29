#include "persistencia.h"
#include "produto.h"
#include "pedido.h"
#include "cliente.h"
#include <stdio.h>

int main(){}

void carregarArquivo(FILE *fpro,FILE *fped, FILE *fcli,FILE *fitem,Produto *produtos, Pedido *pedidos, Cliente *clientes,ItemPedido *itemsPedidos){

    fpro = fopen("Produtos.csv","r+");
    // o cont serve para ir almentando a posição do vetor
    int cont =0;
    while (fscanf(fpro,"%d, %99[^,], %lf, %d ",&produtos[cont].id,produtos[cont].descricao,&produtos[cont].preco,&produtos[cont].estoque) == 4) {
        cont +=1;
    }
    cont =0;

    fped = fopen("Pedidos.csv","r+");
    while (fscanf(fped,"%d, %d, %s, %lf", &pedidos[cont].id,&pedidos[cont].clienteId, pedidos[cont].data, &pedidos[cont].total)==4){
      cont++;
    }
    cont =0;

    fitem = fopen("ItemPedidos.csv","r+");
    while (fscanf(fped,"%d, %d, %d, %lf", &itemsPedidos[cont].pedidoId,&itemsPedidos[cont].produtoId, &itemsPedidos[cont].quantidade, &itemsPedidos[cont].subtotal)==4){
        cont++;
    }
    cont =0;
    //problema por causa da pessoa juridica ou pessoa fisica
    fcli = fopen("Clientes.csv", "r+");
    while(fscanf(fcli,"%d, %199[^,], %s, %s, %s, %s, %s")){}
}