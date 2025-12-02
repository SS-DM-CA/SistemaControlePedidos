#ifndef PEDIDO_H
#define PEDIDO_H

typedef struct{
  int id;
  int clienteId;
  char data[11];
  double total;
} Pedido;

typedef struct{
  int pedidoId;
  int produtoId;
  int quantidade;
  double subtotal;
} ItemPedido;

void modulo_pedidos();
void cadastrarPedido();
void consultarPedidos();
void removerPedido();
void listarPedidos();

void removerItemDePedido();

int analisaPedido(int Id, Pedido *pedidos, int tamanhoPed);

#endif // PEDIDO_H