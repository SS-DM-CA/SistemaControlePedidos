#ifndef  PRODUTO_H
#define  PRODUTO_H

//#include"../include/pedido.h"
typedef struct ItemPedido ItemPedido;
typedef struct Produto{
    int id;
    char descricao[100];
    double preco;
    int estoque;
}Produto;

void cadastrarProduto(Produto produto,Produto **produtos,int *tamanhoProd);

void consultarProduto( Produto *produtos, int tamanhoProd);

void removerProduto(Produto **produtos, int *tamanhoProd,ItemPedido *itemsPedidos, int tamanhoItemPed);

void listarProdutos(Produto *produtos, int tamanhoProd);

int analisaProduto(int Id,Produto *produtos,int tamanhoProd);




#endif //PRODUTO_H
