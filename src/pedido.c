#include <stdio.h>
#include "../include/pedido.h"
#include "../include/produto.h"

int analisaPedido(int Id, Pedido *pedidos,int tamanhoPed);

int main(){}

int analisaPedido(int Id, Pedido *pedidos,int tamanhoPed) {
    for (int i = 0; i<tamanhoPed;i++) {
        if (Id == pedidos[i].id) {
            //retorna 1 se o pedido já existir
            return 1;
        }
    }
    //retorna 2 se o pedido não existir
    return 2;
}