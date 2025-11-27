#ifndef PEDIDO_H
#define PEDIDO_H


#include "cliente.h"
#include "produto.h"
typedef struct{
  int id;
  int clienteid;
  char data[11];
  double total;
}Pedido;

typedef struct{
  int pedidoId;
  int produtoId;
  int quantidade;
  double subtotal;
}ItemPedido;

void cadastrarPedido(Pedidos **pedidos, int *tamanhoPed, Cliente *clientes, int tamanhoCli,ItemPedido *itemsPedidos,int tamanhoItemPed,
                     Produto *produtos,int tamanhoProd);
void listarPedidos();
void removerPedido();
void consultarPedido();








#endif //PEDIDO_H