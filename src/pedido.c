#include <stdio.h>
#include "../include/pedido.h"
#include "../include/produto.h"
#include "../include/cliente.h"

int analisaPedido(int Id, Pedido *pedidos,int tamanhoPed);
int analisaCliente(int Id, Cliente *clientes,int tamanhoCli);
void cadastrarItensPedido(Produto *produtos,int tamanhoProd, ItemPedido *itemsPedidos,ItemPedido itempedido,int tamanhoItemped);
int analisaProduto(int Id, Produto *produtos,int tamanhoProd);

int main(){}
void cadastrarPedido(Pedidos **pedidos, int *tamanhoPed, Cliente *clientes, int tamanhoCli,ItemPedido *itemsPedidos,int tamanhoItemPed,
                     Produto *produtos,int tamanhoProd){
   Pedido pedido;
    int IdPed;
    printf("Digite o id do pedido:");
    scanf("%d", &IdPed);
  //analisar se o pedido existe ou não
   if(analisaPedido(IdPed,pedidos,*tamanhoPed)==1){
     //o pedido já existe
     //o cursor deve retornar para o campo de codigo  na tela de cadastro
     return EXIT_FAILURE;
   }
   else{
     int IdCli;
     //pedido ainda não existe
     //analisar se o cliente existe ou não
     printf("Digite o id do cliente:");
     scanf("%d", &IdCli);
     if(analisaCliente(IdCli,clientes,tamanhoCli) == 2){
       //O cliente não existe
       //o cursor deve retornar para o campo de codigo do clinte na tela de cadastro
       return EXIT_FAILURE;
     }
     else{
       //cliente existe
       pedido.clienteid = IdCli;
       scanf("%d %s %lf",&pedido.id,&pedido.data,&pedido.total);
       *pedidos = (Pedido *) realloc(*pedidos,(*tamanhoPed+1)*sizeof(Pedido));
       *pedidos[*tamanhoPed] = pedido;
       (*tamanhoPed)++;



       cadastrarItensPedido(produtos,tamanhoProd,&itemsPedidos,&tamanhoItemPed);
     }
   }
}
void cadastrarItensPedido(Produto *produtos,int tamanhoProd, ItemPedido **itemsPedidos,int *tamanhoItemPed) {
    ItemPedido itempedido;
    int IdProd;
    printf("Digite o codigo do produto: ");
    scanf("%d",&IdProd);
    if (analisaProduto(IdProd,produtos,tamanhoProd) == 2) {
        return EXIT_FAILURE;
    }
    else {
        //produto existe
        scanf("%d %d %d %lf",&itempedido.pedidoId,&itempedido.produtoId,&itempedido.quantidade,&itempedido.subtotal);
        //Quando ele apertar o botão Cadastrar
        *itemsPedidos =(ItemPedido *) realloc(*itemsPedidos,(*tamanhoItemPed+1)*sizeof(ItemPedido));
        *itemsPedidos[*tamanhoItemPed] = itempedido;
        (*tamanhoItemPed)++;
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
            //retorna 1 se o cliente já existir

            return 1;
        }
    }
    //retorna 2 se o pedido não existir
    //o cursor deve retornar para o campo de codigo do clinte na tela de cadastro
    return 2;
}







