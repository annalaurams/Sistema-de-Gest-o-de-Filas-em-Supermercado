
#ifndef FUNCOES_H
#define FUNCOES_H

#include "include.h" 

void ler_caixas(Caixa *caixas, int num_caixas);
void imprimir_caixa(Caixa *caixas, int num_caixas);

void ler_clientes_do_arquivo(Caixa *caixas, int num_caixas);
void imprimir_clientes(Caixa *caixas, int num_caixas);

void inicializar_fila(Fila *fila);
void inserir_fila_com_prioridade(Fila *fila, Cliente cliente);

int validar_nome(char nome[]) ;
int validar_cpf(const char *cpf);
int validar_entrada_numerica(const char *entrada);
int verificar_cpf_existe(Caixa *caixas, int num_caixas, const char *cpf);

void cadastrar_cliente(Caixa *caixas, int num_caixas);

void remover_cliente(Caixa *caixa);
void realocar_clientes_caixa(Caixa *caixas, int num_caixas);
void imprimir_clientes_espera(Caixa *caixas, int num_caixas);
void exibir_estado_caixas(Caixa *caixas, int num_caixas);
void abrir_caixa(Caixa *caixas, int num_caixas);

#endif 


