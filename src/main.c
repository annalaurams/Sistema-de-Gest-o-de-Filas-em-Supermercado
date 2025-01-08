#include "funcoes.h"

int validar_opcao_menu()
{
    char entrada[10]; 
    int opcao;

    while (1)
    {
        printf("\nDigite o valor do que deseja fazer (0 a 5): ");
        scanf("%s", entrada);

        if (!validar_entrada_numerica(entrada))
        {
            printf("\n\t[ERRO] Entrada inválida! Digite apenas números.\n");
            continue;
        }

        opcao = atoi(entrada); 
        if (opcao < 0 || opcao > 5)
        {
            printf("\n\t[ERRO] Opção inválida! Escolha entre 0 e 5.\n");
            continue;
        }

        return opcao; // Retorna a opção válida
    }
}

int main()
{
    int num_caixas = 5;
    int numero_caixa = 0;
    Caixa caixas[num_caixas];

    ler_caixas(caixas, num_caixas);

    int opcao = -1;

    do
    {
        printf("\n=================================================================================================\n");
        printf("\n\tSeja Bem-Vindo(a) ao");
        printf("\n      Sistema de Gestão de Filas em Supermercado \n");
        printf("\nDigite o valor do que deseja fazer: \n");
        printf("\t\n[0] Sair ");
        printf("\t\n[1] Cadastrar um Cliente");
        printf("\t\n[2] Atender um Cliente");
        printf("\t\n[3] Abrir ou Fechar um Caixa");
        printf("\t\n[4] Imprimir a Lista de Clientes em Espera");
        printf("\t\n[5] Imprimir o Status dos Caixas");
    
        opcao = validar_opcao_menu();

        switch (opcao)
        {
        case 0:
            printf("\n\t Obrigado por utilizar nossos serviços! \n");
            break;

        case 1:
            cadastrar_cliente(caixas, num_caixas);
            break;

        case 2:
            remover_cliente(&caixas[numero_caixa], num_caixas);
            break;

        case 3:
            realocar_clientes_caixa(caixas, num_caixas);
            break;

        case 4:
            imprimir_clientes_espera(caixas, num_caixas);
            break;

        case 5:
            exibir_estado_caixas(caixas, num_caixas);
            break;

        default:
        
            printf("\nOpção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    printf("\n-------------------------------------------------------------------------------------------------\n");

    return 0;
}
