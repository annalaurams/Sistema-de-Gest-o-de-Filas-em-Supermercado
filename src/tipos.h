#ifndef TIPOS_H
#define TIPOS_H

typedef struct
{

    char nome[100];
    char cpf[12];
    int prioridade; // 1 representa alta prioridade, 2 prioridade média, e 3 baixa prioridade
    int numero_itens;
    int n_caixa;

} Cliente;

typedef struct No
{

    Cliente cliente;
    struct No *proximo;

} No;

typedef struct Fila
{

    No *primeiro;
    No *ultimo;
    No *ultimo_p1;
    No *ultimo_p2;
    int tamanho;

} Fila;

typedef struct
{

    int id;
    int estado; // 1 aberto, 0 fechado
    Fila fila;

} Caixa;

#endif