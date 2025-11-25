#ifndef  PRODUTO_H
#define  PRODUTO_H

typedef struct {
    int id;
    char descricao[100];
    double preco;
    int estoque;
}Produto;

void cadastrarProduto(int Id,Produto produto,Produto *produtos,int tamanhoProd);

void consultarProduto(int Id, Produto *produtos, int tamanhoProd);

void removerProduto(int Id, Produto *produtos, int tamanhoProd);

void listarProdutos(Produto *produtos, int tamanhoProd);






#endif //PRODUTO_H
