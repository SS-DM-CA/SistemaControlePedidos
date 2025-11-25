#include <stdio.h>
#include "../include/pedido.h"
#include "../include/produto.h"
#include "../include/cliente.h"

int analisaPedido(int Id, Pedido *pedidos,int tamanhoPed);
int analisaCliente(int Id, Cliente *clientes,int tamanhoCli);

int main(){}

int analisaPedido(int Id, Pedido *pedidos,int tamanhoPed) {
    for (int i = 0; i<tamanhoPed;i++) {
        if (Id == pedidos[i].id) {
            //retorna 1 se o pedido já existir
            //o cursor deve retornar para o campo de codigo  na tela de cadastro
            return 1;
        }
    }
    //retorna 2 se o pedido não existir
    return 2;
}

int analisaCliente(int Id, Cliente *clientes,int tamanhoCli) {
    for (int i =0; i<tamanhoCli;i++) {
        //no struct esta Identificador, isso pode mudar, por isso aqui irei colocar id
        if (Id == clientes[i].id) {
            //retorna 1 se o pedido já existir
            //o cursor deve retornar para o campo de codigo do clinte na tela de cadastro
            return 1;
        }
    }
    //retorna 2 se o pedido não existir
    return 2;
}



