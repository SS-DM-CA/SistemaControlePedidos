#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "produto.h"
#include "pedido.h"
#include "cliente.h"

void salvarArquivo(Produto *produtos, Pedido *pedidos, Cliente *clientes, ItemPedido *itemsPedidos,
                   int tamanhoProd, int tamanhoPed, int tamanhoItemPed, int tamanhoCli);

void salvarProduto(Produto *produtos, int tamanhoProd);
void salvarPedido(Pedido *pedidos, int tamanhoPed);
void salvarCliente(Cliente *clientes, int tamanhoCli);
void salvarItemPedido(ItemPedido *itemsPedidos, int tamanhoItemPed);

int carregarProduto(Produto **produtos);
int carregarPedidos(Pedido **pedidos);
int carregarClientes(Cliente **clientes);
int carregarItemPedido(ItemPedido **itemsPedidos);

#endif