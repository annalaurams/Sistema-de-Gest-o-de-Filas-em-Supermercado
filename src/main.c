#include "funcoes.h"

int main()
{
    int num_caixas = 5;
    int numero_caixa = 0;
    Caixa caixas[num_caixas];

    ler_caixas(caixas, num_caixas);

    // imprimir_caixa(caixas, num_caixas);

    int opcao = 0;

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
        printf("\t\n\n> ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:

            printf("\n\t Obrigado por utilizar nossos serviços! \n");

            break;
        case 1:

            cadastrar_cliente(caixas, num_caixas);
            // ler_clientes_do_arquivo(caixas, num_caixas);
            //  imprimir_clientes(caixas, num_caixas);

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