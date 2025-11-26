#include <stdio.h>
#include "../include/pedido.h"
#include "../include/produto.h"
#include "../include/cliente.h"

int analisaPedido(int Id, Pedido *pedidos,int tamanhoPed);
int analisaCliente(int Id, Cliente *clientes,int tamanhoCli);
void cadastrarItensPedido(int Id,Produto *produtos,int tamanhoProd );
int analisaProduto(int Id, Produto *produtos,int tamanhoProd);

int main(){}





void cadastrarItensPedido(int Id,Produto *produtos,int tamanhoProd, ItemPedido *itemsPedidos,ItemPedido itempedido,int tamanhoItemped) {
    //printf("Digite o codigo do produto: ")
    //scanf("%d",&Id);
    if (analisaProduto(Id,produtos,tamanhoProd) == 2) {
        return EXIT_FAILURE;
    }
    else {
        //produto existe
        scanf("%d %d %d %lf",&itempedido.pedidoId,&itempedido.produtoId,&itempedido.quantidade,&itempedido.subtotal);
        //Quando ele apertar o botão Cadastrar
        itemsPedidos = (ItemPedido *) realloc(itemsPedidos,(tamanhoItemped+1)*sizeof(ItemPedido));
        itemsPedidos[tamanhoItemPed] = itempedido;
        tamanhoItemPed++;
    }

}

















int analisaProduto(int Id, Produto *produtos,int tamanhoProd) {
    for (int i =0; i<tamanhoProd;i++) {
        //no struct esta Identificador, isso pode mudar, por isso aqui irei colocar id
        if (Id == produtos[i].id) {
            //retorna 1 se o produto já existir
            //o cursor deve retornar para o campo de codigo do clinte na tela de cadastro
            return 1;
        }
    }
    //retorna 2 se o o produto não existir
    return 2;
}


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







