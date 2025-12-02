#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/cliente.h"
#include "../include/interface.h"
#include "../include/persistencia.h"

Cliente *lista_clientes = NULL; 
int total_clientes = 0;

int apenas_numeros(char *str) {
    for (int i = 0; str[i] != '\0'; i++) if (!isdigit(str[i])) return 0;
    return 1;
}

int validador_id_cliente(char *str) { return (strlen(str) > 0 && apenas_numeros(str)); }
int validador_obrigatorio(char *str) { return strlen(str) > 0; }
int validador_cpf(char *str) { return (strlen(str) == 11 && apenas_numeros(str)); }
int validador_cnpj(char *str) { return (strlen(str) == 14 && apenas_numeros(str)); }
int validador_email(char *str) { return (strlen(str) > 5 && strchr(str, '@') && strchr(str, '.')); }
int validador_telefone(char *str) { 
    if (strlen(str) == 0) return 1; 
    return ((strlen(str) == 10 || strlen(str) == 11) && apenas_numeros(str)); 
}

void sincronizar_clientes() {
    if(lista_clientes != NULL) {
        free(lista_clientes);
        lista_clientes = NULL;
    }
    total_clientes = carregarClientes(&lista_clientes);
}

void salvar_alteracoes_cliente() {
    salvarCliente(lista_clientes, total_clientes);
}

int analisaCliente(int Id, Cliente *clientes, int tamanhoCli) {
    if (clientes == NULL || tamanhoCli <= 0) return 2; 
    for (int i = 0; i < tamanhoCli; i++) {
        if (clientes[i].id == Id) return 1;
    }
    return 2;
}
int obter_id_disponivel_cliente() {
    int candidato = 1;
    while(1) {
        int existe = 0;
        for(int i = 0; i < total_clientes; i++) {
            if(lista_clientes[i].id == candidato) {
                existe = 1;
                break;
            }
        }
        if(!existe) return candidato;
        candidato++;
    }
}

void cadastrarCliente() {
    sincronizar_clientes(); 

    Cliente novo;
    memset(&novo, 0, sizeof(Cliente));
    
    char b_nome[200]="", b_doc[20]="", b_email[100]="", b_tel[20]="", b_end[200]="", b_cont[100]="";

    int id_auto = obter_id_disponivel_cliente();
    
    char titulo[50];
    sprintf(titulo, "NOVO CLIENTE [ID: %d]", id_auto);

    char *opcoes_tipo[] = {"Pessoa Fisica (CPF)", "Pessoa Juridica (CNPJ)", "Cancelar"};
    int tipo = menu_generico("TIPO DE CLIENTE", opcoes_tipo, 3);
    if (tipo == -1 || tipo == 2) return;

    char lbl_nome[30], lbl_doc[30]; 
    int (*validador_doc)(char*);

    if (tipo == 0) { 
        strcpy(lbl_nome, "Nome Completo *:");
        strcpy(lbl_doc, "CPF (So num) *:");
        validador_doc = validador_cpf;
    } else { 
        strcpy(lbl_nome, "Razao Social *:");
        strcpy(lbl_doc, "CNPJ (So num) *:");
        validador_doc = validador_cnpj;
    }
    CampoFormulario campos[] = {
        {lbl_nome, b_nome, 199, 0, 0, 40, validador_obrigatorio},
        {lbl_doc, b_doc, 19, 1, 0, 20, validador_doc},
        {"Email *:", b_email, 99, 2, 0, 30, validador_email},
        {"Telefone:", b_tel, 19, 3, 0, 20, validador_telefone},
        {"Endereco *:", b_end, 199, 4, 0, 40, validador_obrigatorio},
        {"Contato *:", b_cont, 99, 5, 0, 30, validador_obrigatorio}
    };
    
    if (formulario_generico(titulo, campos, 6)) {
        for(int i=0; i<total_clientes; i++) {
            if(strcmp(lista_clientes[i].identidade, b_doc) == 0) {
                desenhar_janela_popup("ERRO", "CPF/CNPJ ja cadastrado!"); return;
            }
        }

        novo.id = id_auto;
        strcpy(novo.nome, b_nome); strcpy(novo.identidade, b_doc);
        strcpy(novo.email, b_email); strcpy(novo.telefone, b_tel);
        strcpy(novo.endereco, b_end); strcpy(novo.contato, b_cont);

        total_clientes++;
        lista_clientes = (Cliente *) realloc(lista_clientes, total_clientes * sizeof(Cliente));
        if (lista_clientes == NULL) { desenhar_janela_popup("ERRO", "Memoria insuficiente!"); return; }
        
        lista_clientes[total_clientes - 1] = novo;

        salvar_alteracoes_cliente();
        desenhar_janela_popup("SUCESSO", "Cliente cadastrado!");
    }
}

void consultarCliente() {
    sincronizar_clientes();
    char b_id[15]="";
    CampoFormulario campos[] = { {"ID Cliente:", b_id, 14, 0, 0, 15, validador_id_cliente} };
    
    if(formulario_generico("CONSULTAR CLIENTE", campos, 1)) {
        int id = atoi(b_id);
        if(analisaCliente(id, lista_clientes, total_clientes) == 2) {
            desenhar_janela_popup("ERRO", "Cliente nao encontrado.");
        } else {
            for(int i=0; i<total_clientes; i++) {
                if(lista_clientes[i].id == id) {
                    char msg[2048];
                    snprintf(msg, 2048, "ID: %d\nNome: %s\nDoc: %s\nTel: %s\nEmail: %s\nEnd: %s\nCtto: %s", 
                        lista_clientes[i].id, lista_clientes[i].nome, lista_clientes[i].identidade, 
                        lista_clientes[i].telefone, lista_clientes[i].email, lista_clientes[i].endereco, lista_clientes[i].contato);
                    desenhar_janela_popup("DADOS DO CLIENTE", msg);
                    return;
                }
            }
        }
    }
}

void removerCliente() {
    sincronizar_clientes();
    char b_id[15]="";
    CampoFormulario campos[] = { {"ID para remover:", b_id, 14, 0, 0, 15, validador_id_cliente} };
    
    if(formulario_generico("REMOVER CLIENTE", campos, 1)) {
        int id = atoi(b_id);
        if(analisaCliente(id, lista_clientes, total_clientes) == 2) {
            desenhar_janela_popup("ERRO", "Cliente nao encontrado."); return;
        }
        int op = menu_generico("CONFIRMAR EXCLUSAO?", (char*[]){"SIM", "NAO"}, 2);
        if(op == 0) { 
            for(int i=0; i<total_clientes; i++) {
                if(lista_clientes[i].id == id) {
                    for(int j=i; j<total_clientes-1; j++) lista_clientes[j] = lista_clientes[j+1];
                    total_clientes--;
                    lista_clientes = (Cliente *) realloc(lista_clientes, total_clientes * sizeof(Cliente));
                    salvar_alteracoes_cliente();
                    desenhar_janela_popup("SUCESSO", "Cliente removido."); return;
                }
            }
        }
    }
}

int detalhes_cliente_cb(int index) {
    if (index < 0 || index >= total_clientes) return 0;
    Cliente c = lista_clientes[index];
    char msg[2048];
    snprintf(msg, 2048, "ID: %d\nNome: %s\nDoc: %s", c.id, c.nome, c.identidade);
    desenhar_janela_popup("RESUMO", msg);
    return 1;
}

void listarClientes() {
    sincronizar_clientes();
    if (total_clientes == 0) { desenhar_janela_popup("AVISO", "Nenhum cliente cadastrado."); return; }
    char **itens = malloc(total_clientes * sizeof(char*));
    for (int i = 0; i < total_clientes; i++) {
        itens[i] = malloc(300);
        snprintf(itens[i], 300, "[%03d] %-25s | %s", 
                 lista_clientes[i].id, lista_clientes[i].nome, lista_clientes[i].identidade);
    }
    lista_scrollable_pesquisavel("LISTA DE CLIENTES", itens, total_clientes, detalhes_cliente_cb);
    for(int i=0; i<total_clientes; i++) free(itens[i]);
    free(itens);
}

void modulo_clientes() {
    sincronizar_clientes();
    int rodando = 1;
    char *opcoes[] = {"1. Cadastrar Cliente", "2. Consultar Cliente", "3. Remover Cliente", "4. Listar Todos", "5. Voltar"};
    while(rodando) {
        int escolha = menu_generico("GESTAO DE CLIENTES", opcoes, 5);
        if(escolha >= 0 && escolha != 4) animacao_transicao(0);
        switch(escolha) {
            case 0: cadastrarCliente(); break;
            case 1: consultarCliente(); break;
            case 2: removerCliente(); break;
            case 3: listarClientes(); break;
            case 4: case -1: rodando = 0; break;
        }
        if(escolha >= 0 && escolha != 4) animacao_transicao(1);
    }
}