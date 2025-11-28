#include <stdio.h>
#include "../include/pedido.h"
#include "../include/produto.h"
#include "../include/cliente.h"

int analisaPedido(int Id, Pedido *pedidos,int tamanhoPed);
int analisaCliente(int Id, Cliente *clientes,int tamanhoCli);
void cadastrarItensPedido(Produto *produtos,int tamanhoProd, ItemPedido *itemsPedidos,ItemPedido itempedido,int tamanhoItemped);
int analisaProduto(int Id, Produto *produtos,int tamanhoProd);

int main(){}

void removerPedido(Pedido *pedidos, int tamanhoPed){
  int Id;
  printf("Digite o id do pedido que deseja consultar: ");
  scanf("%d",&Id);
  if(analisaPedido(Id,pedidos,tamanhoPed)==2){
    //pedido não existe
    //não é possivel apagar
    printf("O pedido não existe");
  }
  else{

  }
}

void consultarPedidos(Pedido *pedidos, int tamanhoPed){
  int Id;
  printf("Digite o id do pedido que deseja consultar: ");
  scanf("%d",&Id);
  if(analisaPedido(Id,pedidos,tamanhoPed) == 2){
    //Pedido não existe
    return EXIT_FAILURE;
  }
  else{
    //O pedido existe
    for(int i=0;i<tamanhoPed;i++ ){
      if(pedidos[i].id==Id){
        //na interface podemos colocar ainda um botão para consultar os items pedidos;
        //aqui ele apenas imprimi os valores do pedido que deseja consultar
        printf("%d %d %s %lf", &pedidos[i].id,&pedidos[i].clienteId,pedidos[i].data,pedidos[i].total);
      }
    }
  }
}


void listarPedido(Pedido *pedidos, int tamanhoPed,ItemPedido *itemsPedidos){
  //contador para o while;
  int cont =0;

  for(int i =0; i<tamanhoPed;i++){
    printf("%d %d %s %lf", &pedidos[i].id,&pedidos[i].clienteId,pedidos[i].data,pedidos[i].total);
    //imprimi os items do pedido ate comparando os codigos
    //compara até o codigo de um item pedido for diferente do codigo do pedido
    while(itemsPedidos[cont].pedidoId == pedidos[i].id){
      printf("%d %d %d %lf",&itemsPedidos[cont].pedidoId,&itemsPedidos[cont].produtoId,&itemsPedidos[cont].quantidade,&itemsPedidos[cont].subtotal);
    }
  }
}
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
       pedido.clienteId = IdCli;
       scanf("%d %s %lf",&pedido.id,&pedido.data,&pedido.total);
       *pedidos = (Pedido *) realloc(*pedidos,(*tamanhoPed+1)*sizeof(Pedido));
       *pedidos[*tamanhoPed] = pedido;
       (*tamanhoPed)++;



       cadastrarItensPedido(produtos,tamanhoProd,&itemsPedidos,&tamanhoItemPed);
     }
   }
}


void removerItemPedido(Produto *produtos,int tamanhoProd){
  int Id;
  printf("Digite o id do pedido que deseja consultar: ");
  scanf("%d",&Id);
  if(analisaProduto(Id,produtos,tamanhoProd)== 2){
    //O produto não existe
    printf("O produto não existe não existe");
  }
  else{
    //o produto existe
    //agora ele deve ser apagado
    
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







