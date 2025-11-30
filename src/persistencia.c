#include "persistencia.h"
#include "produto.h"
#include "pedido.h"
#include "cliente.h"
#include <stdio.h>

void salvarProduto(FILE *fpro,Produto *produtos, int tamanhoProd);
void salvarPedido(FILE *fped,Pedido *pedidos,int tamanhoPed);
void salvarItemPedido(FILE *fitem,ItemPedido *itemsPedidos,int tamanhoItemPed);
void salvarCliente(FILE *fcli,Cliente *clientes,int tamanhoCli);

int main(){}



void salvarArquivo(FILE *fpro,FILE *fped, FILE *fcli,FILE *fitem,Produto *produtos, Pedido *pedidos, Cliente *clientes,ItemPedido *itemsPedidos,
                   int tamanhoProd,int tamanhoPed,int tamanhoItemPed,int tamanhoCli){
  salvarProduto(fpro,produtos,tamanhoProd);
  salvarPedido(fped,pedidos,tamanhoPed);
  salvarItemPedido(fitem,itemsPedidos,tamanhoItemPed);
  salvarCliente(fcli,clientes,tamanhoCli);

}



void salvarProduto(FILE *fpro,Produto *produtos,int tamanhoProd){
  for(int i=0;i<tamanhoProd;i++){
      fprintf(fpro,"%d, %s, %lf, %d \n",produtos[i].id,produtos[i].descricao,produtos[i].preco,produtos[i].estoque);
  }
  fclose(fpro);

}

void salvarPedido(FILE *fped,Pedido *pedidos,int tamanhoPed){
  for(int i =0;i<tamanhoPed;i++){
    fprintf(fped,"%d, %d, %s, %lf", pedidos[i].id,pedidos[i].clienteId, pedidos[i].data, pedidos[i].total);
  }
  fclose(fped);
}

void salvarCliente(FILE *fcli,Cliente *clientes,int tamanhoCli){
  for(int i =0; i<tamanhoCli;i++){

  }
  fclose(fcli);
}

void salvarItemPedido(FILE *fitem,ItemPedido *itemsPedidos,int tamanhoItemPed){
  for(int i=0;i<tamanhoItemPed;i++){
      (fitem,"%d, %d, %d, %lf", itemsPedidos[i].pedidoId,itemsPedidos[i].produtoId, itemsPedidos[i].quantidade, itemsPedidos[i].subtotal)
  }
  fclose(fitem);
}
int  carregarClientes(FILE **fcli,Cliente **clientes){
  //abrir o arquivo
    *fcli = fopen("Clientes.csv", "r+");
    //se não abrir
    if( *fcli== NULL){
        printf("O arquivo Clientes.csv não existe");
        printf("Ele sera criado");
        *fcli = fopen("Produtos.csv","a");
        fclose(*fcli);
        *fcli = fopen("Produtos.csv","r+");
    }
    // o cont serve para ir almentando a posição do vetor
    int cont =0;
    *clientes = (Cliente *) realloc(*clientes,(cont+1)*sizeof(Clientes));
    while(fscanf(*fcli,"%d, %199[^,], %s, %s",&(*cliente)[cont].id)){
      cont++;
        *clientes = (Cliente *) realloc(*clientes,(cont+1)*sizeof(Clientes));
    }
    return cont;
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

