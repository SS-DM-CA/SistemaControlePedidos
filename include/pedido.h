#ifndef PEDIDO_H
#define PEDIDO_H

typedef struct{
  int id;
  int clienteid;
  char data[11];
  double total;
}Pedido;

typedef struct{
  int pedidoId;
  int peodutoId;
  int quantidade;
  double subtotal;
}ItemPedido;







#endif //PEDIDO_H