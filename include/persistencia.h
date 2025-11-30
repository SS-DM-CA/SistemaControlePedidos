#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H


#include <stdio.h>
#include"../include/pedido.h"
#include"../include/cliente.h"
#include"../include/produto.h"
void salvarArquivo(FILE *fpro,FILE *fped, FILE *fcli,FILE *fitem,Produto *produtos, Pedido *pedidos, Cliente *clientes,ItemPedido *itemsPedidos,
    int tamanhoProd,int tamanhoPed,int tamanhoItemPed,int tamanhoCli);
int carregarProduto(FILE **fpro,Produto **produtos);
int carregarPedidos(FILE **fped,Pedido **pedidos);
int carregarClientes(FILE **fcli,Cliente **clientes);
int carregarItemPedido(FILE **fitem,ItemPedido **itemsPedidos);




















#endif //PERSISTENCIA_H