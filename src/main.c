#include "funcoes.h"

int main()
{

    clock_t start_time, end_time;
    start_time = clock();

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
            // imprimir_clientes(caixas, num_caixas);

            break;

        case 2:

            printf("\nDigite o número do caixa: ");
            scanf("%d", &numero_caixa);

            numero_caixa--;

            if (numero_caixa >= 0 && numero_caixa < num_caixas)
                remover_cliente(&caixas[numero_caixa]);
            else
                printf("\nNúmero do caixa inválido.\n");

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

    end_time = clock();
    double tempo = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\n\nTempo de execução: %.6f segundos. \n", tempo);
    printf("\n-------------------------------------------------------------------------------------------------\n");

    return 0;
}