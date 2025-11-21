#include "persistencia.h"
#include "produto.h"
#include "pedido.h"
#include "cliente.h"
#include <stdio.h>

int main(){}

void carregarArquivo(FILE *fpro,FILE *fped, FILE *fcli,Produto *produtos, Pedido *pedidos, Cliente *clientes){
    fpro = fopen("Produtos.csv","r+");
    int cont =0;
    while (fscanf("%d, %99[^,], %lf, %d ",&produtos[cont].id,produtos[cont].descricao,&produtos[cont].preco,&produtos[cont].estoque) == 4) {
        cont +=1;
    }
    cont =0;

    fped = fopen("Pedidos.csv","r+");
    while (fscanf("%d %d %s %lf", &pedidos.id[0],&pedidos.clienteId[0], pedidos.data[0], &pedidos.total[0])==4){
      
    }

}