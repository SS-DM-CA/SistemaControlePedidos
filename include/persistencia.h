#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

void salvarArquivo(FILE *fpro,FILE *fped, FILE *fcli,FILE *fitem,Produto *produtos, Pedido *pedidos, Cliente *clientes,ItemPedido *itemsPedidos,
    int tamanhoProd,int tamanhoPed,int tamanhoItemPed,int tamanhoCli);
int carregarProduto(FILE **fpro,Produto **produtos);
int carregarPedidos(FILE **fped,Pedido **pedidos);
int carregarClientes(FILE **fcli,Cliente **clientes);
int carregarItemPedido(FILE **fitem,ItemPedido **itemsPedidos);




















#endif //PERSISTENCIA_H