#include "funcoes.h"

int auxiliar = 0;
Cliente *tabela_clientes = NULL;

void ler_caixas(Caixa *caixas, int num_caixas)
{
    FILE *arquivo = fopen("data/caixas.txt", "r");

    if (arquivo == NULL)
    {
        printf("\nErro ao tentar abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < num_caixas; i++)
    {
        fscanf(arquivo, "%d %d", &caixas[i].id, &caixas[i].estado);

        inicializar_fila(&caixas[i].fila); // Inicializa a fila do caixa ao ser criado
    }

    fclose(arquivo);
}

void imprimir_caixa(Caixa *caixas, int num_caixas)
{
    printf("\n================ CAIXAS CADASTRADOS =================\n\n");

    for (int i = 0; i < num_caixas; i++)
    {
        printf("\nId: %d", caixas[i].id);

        if (caixas[i].estado == 1)
            printf(" - Caixa Aberto\n");
        else
            printf(" - Caixa Fechado\n");
    }
    printf("\n===================================================================\n\n");
}

void inicializar_fila(Fila *fila)
{
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    fila->ultimo_p1 = NULL;
    fila->ultimo_p2 = NULL;
    fila->tamanho = 0;
}

void inserir_fila_com_prioridade(Fila *f, Cliente c)
{
    // Funções para validar a entrada
    No *novo = malloc(sizeof(No));
    if (!novo)
    {
        printf("\n\t[ERRO] Para tentar alocar memória para o novo nó.\n");
        return;
    }

    novo->cliente = c;
    novo->proximo = NULL;

    f->tamanho++;

    if (c.prioridade == 1)
    {
        if (f->ultimo_p1 == NULL)
        {
            // Inserir no início da fila
            novo->proximo = f->primeiro;
            f->primeiro = novo;

            if (f->ultimo == NULL)
                f->ultimo = novo;
        }
        else
        {

            novo->proximo = f->ultimo_p1->proximo;
            f->ultimo_p1->proximo = novo;

            if (novo->proximo == NULL) // Se inserido no final
                f->ultimo = novo;
        }
        f->ultimo_p1 = novo; // Atualiza o último com prioridade 1
    }
    else if (c.prioridade == 2)
    {
        if (f->ultimo_p2 == NULL)
        {
            if (f->ultimo_p1 == NULL)
            {
                novo->proximo = f->primeiro;
                f->primeiro = novo;

                if (f->ultimo == NULL) // Fila estava vazia
                    f->ultimo = novo;
            }
            else
            {
                // Inserir após o último cliente com prioridade 1
                novo->proximo = f->ultimo_p1->proximo;
                f->ultimo_p1->proximo = novo;

                if (novo->proximo == NULL) // Se inserido no final
                    f->ultimo = novo;
            }
        }
        else
        {
            // Inserir após o último cliente com prioridade 2
            novo->proximo = f->ultimo_p2->proximo;
            f->ultimo_p2->proximo = novo;

            if (novo->proximo == NULL) // Se inserido no final
                f->ultimo = novo;
        }
        f->ultimo_p2 = novo; // Atualiza o último com prioridade 2
    }
    else
    {
        if (f->ultimo == NULL)
        {
            // Fila estava vazia
            f->primeiro = novo;
        }
        else
        {
            // Inserir no final
            f->ultimo->proximo = novo;
        }
        f->ultimo = novo;
    }
}

int validar_entrada_numerica(const char *entrada)
{
    for (int i = 0; entrada[i] != '\0'; i++)
    {
        if (!isdigit(entrada[i]))
        {
            return 0;
        }
    }
    return 1;
}

int verificar_cpf_existe(Caixa *caixas, int num_caixas, const char *cpf)
{
    for (int i = 0; i < num_caixas; i++)
    {
        No *atual = caixas[i].fila.primeiro;
        while (atual != NULL)
        {
            if (strcmp(atual->cliente.cpf, cpf) == 0)
            {
                return 1;
            }
            atual = atual->proximo;
        }
    }
    return 0;
}

int validar_nome(char nome[])
{
    for (size_t i = 0; i < strlen(nome); i++)
    {
        if (!isalpha(nome[i]) && nome[i] != '\n')
        {
            return 0;
        }
    }
    return 1;
}

int validar_cpf(const char *cpf)
{
    if (strlen(cpf) != 11)
    {
        return 0;
    }

    for (int i = 0; i < 11; i++)
    {
        if (!isdigit(cpf[i]))
        {
            return 0;
        }
    }
    return 1;
}

int verificar_caixa_aberto(Caixa *caixas, int num_caixas)
{
    char entrada[10];
    int caixa_escolhido;

    while (1)
    {
        printf("\nEscolha o número do caixa (entre 1 e %d): ", num_caixas);
        scanf("%s", entrada);

        if (!validar_entrada_numerica(entrada))
        {
            printf("\n\t[ERRO] Entrada inválida! Digite apenas números.\n");
            continue;
        }

        caixa_escolhido = atoi(entrada);

        if (caixa_escolhido < 1 || caixa_escolhido > num_caixas)
        {
            printf("\n\t[ERRO]  Número de caixa inválido! Escolha entre 1 e %d.\n", num_caixas);
            continue;
        }

        if (caixas[caixa_escolhido - 1].estado == 1)
        {
            return caixa_escolhido; // Caixa está aberto
        }
        else
        {
            printf("\n\t[ATENÇÃO] O caixa %d está fechado, escolha uma das opções abaixo.\n", caixa_escolhido);
            printf("\n\tCaixas abertos\n");
            for (int i = 0; i < num_caixas; i++)
            {
                if (caixas[i].estado == 1)
                {
                    printf("Caixa %d\n", caixas[i].id);
                }
            }
        }
    }
}

void ler_clientes_do_arquivo(Caixa *caixas, int num_caixas)
{
    FILE *file = fopen("data/clientes.txt", "r");
    if (file == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    Cliente cliente;

    for (int i = 0; i < 10; i++)
    {
        fgets(cliente.nome, sizeof(cliente.nome), file);
        cliente.nome[strcspn(cliente.nome, "\n")] = 0;

        fgets(cliente.cpf, sizeof(cliente.cpf), file);
        cliente.cpf[strcspn(cliente.cpf, "\n")] = 0;

        fscanf(file, "%d\n", &cliente.prioridade);
        fscanf(file, "%d\n", &cliente.numero_itens);
        fscanf(file, "%d\n", &cliente.n_caixa);

        if (cliente.n_caixa < 1 || cliente.n_caixa > num_caixas + 1)
        {
            printf("\nCaixa inválido para o cliente: %s\n", cliente.nome);
            continue;
        }

        inserir_fila_com_prioridade(&caixas[cliente.n_caixa - 1].fila, cliente);
        // printf("Cliente cadastrado: %s (CPF: %s) no caixa %d!\n", cliente.nome, cliente.cpf, cliente.n_caixa);
    }

    fclose(file);

    printf("\nClientes Cadastrados\n");
}

void cadastrar_cliente(Caixa *caixas, int num_caixas)
{
    Cliente cliente;
    char entrada[20];

    printf("\n\tDigite as informações\n\n");

    printf("\nNome: ");
    getchar();
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0'; // Remove o '\n' ao final da string

    do
    {
        printf("\nCPF (somente números, 11 dígitos): ");
        scanf("%s", cliente.cpf);

        if (!validar_cpf(cliente.cpf))
        {
            printf("\n\t[ERRO] CPF inválido! Certifique-se de digitar apenas números e com 11 dígitos.\n");
        }
        else
        {
            if (verificar_cpf_existe(caixas, num_caixas, cliente.cpf))
            {
                printf("\n\t[ATENÇÃO] CPF já cadastrado: %s\n", cliente.cpf);
            }
            else
            {
                break; // CPF válido e não cadastrado
            }
        }
    } while (1);

    do
    {
        printf("\nPrioridade: \n[1] Alta \n[2] Média \n[3] Baixa \n\n> ");
        scanf("%s", entrada);

        if (!validar_entrada_numerica(entrada) || (atoi(entrada) < 1 || atoi(entrada) > 3))
        {
            printf("\n\t[ERRO] Prioridade inválida! Escolha entre 1, 2 ou 3.\n");
        }
        else
        {
            cliente.prioridade = atoi(entrada);
            break;
        }
    } while (1);

    do
    {
        printf("\nNúmero de itens no carrinho: ");
        scanf("%s", entrada);

        if (!validar_entrada_numerica(entrada))
        {
            printf("\n\t[ERRO] Entrada inválida! Digite apenas números.\n");
        }
        else
        {
            cliente.numero_itens = atoi(entrada);
            break;
        }
    } while (1);

    do
    {
        // printf("\nNúmero do caixa: ");
        int c = verificar_caixa_aberto(caixas, num_caixas);
        cliente.n_caixa = c;
        break;
    } while (1);

    printf("\n\tCliente cadastrado na fila do caixa %d!\n\n", cliente.n_caixa);

    inserir_fila_com_prioridade(&caixas[cliente.n_caixa - 1].fila, cliente);
}

void imprimir_clientes(Caixa *caixas, int num_caixas)
{
    printf("\n================ CLIENTES NAS FILAS =================\n\n");

    for (int i = 0; i < num_caixas; i++)
    {
        printf("Caixa %d (Estado: %s):\n", i + 1, caixas[i].estado == 1 ? "Aberto" : "Fechado");

        if (caixas[i].fila.tamanho == 0)
        {
            printf("  Fila vazia\n\n");
            continue;
        }

        No *atual = caixas[i].fila.primeiro;
        int posicao = 1;

        while (atual != NULL)
        {
            Cliente cliente = atual->cliente;
            printf("  [%d] Nome: %s\n", posicao, cliente.nome);
            printf("      CPF: %s\n", cliente.cpf);
            printf("      Prioridade: %s\n", cliente.prioridade == 1 ? "Alta" : cliente.prioridade == 2 ? "Média"
                                                                                                        : "Baixa");
            printf("      Itens: %d\n", cliente.numero_itens);
            printf("      Caixa: %d\n\n", cliente.n_caixa);

            atual = atual->proximo;
            posicao++;
        }
    }

    printf("\n===================================================================\n\n");
}

void remover_cliente(Caixa *caixas, int num_caixas) {
    char entrada[10];
    int numero_caixa;

    while (1) {
        printf("\nDigite o número do caixa: ");
        scanf("%s", entrada);

        if (!validar_entrada_numerica(entrada)) {
            printf("\n\t[ERRO] Entrada inválida! Digite apenas números.\n");
            continue;
        }

        numero_caixa = atoi(entrada) - 1; // Subtrai 1 para ajustar ao índice do vetor

        if (numero_caixa < 0 || numero_caixa >= num_caixas) {
            printf("\n\t[ERRO] Caixa inválido! Escolha um número entre 1 e %d.\n", num_caixas);
            continue;
        }

        Caixa *caixa = &caixas[numero_caixa];

        if (caixa->estado == 0) {
            printf("\n[ATENÇÃO] O caixa %d está fechado. Escolha um caixa aberto:\n", numero_caixa + 1);
            for (int i = 0; i < num_caixas; i++) {
                if (caixas[i].estado == 1) {
                    printf("Caixa %d\n", caixas[i].id);
                }
            }
            continue; // Retorna ao início do loop para solicitar outro caixa
        }

        if (caixa->fila.tamanho == 0) {
            printf("\nA fila do caixa %d está vazia. Não há clientes para serem atendidos\n", caixa->id);
            return;
        }

        Cliente cliente_removido = caixa->fila.primeiro->cliente;
        No *temp = caixa->fila.primeiro;

        caixa->fila.primeiro = caixa->fila.primeiro->proximo; // Move o primeiro para o próximo nó

        // Se a fila agora estiver vazia, atualiza o último
        if (caixa->fila.primeiro == NULL) {
            caixa->fila.ultimo = NULL;
            caixa->fila.ultimo_p1 = NULL;
            caixa->fila.ultimo_p2 = NULL;
        } else {
            if (cliente_removido.prioridade == 1) {
                caixa->fila.ultimo_p1 = NULL;
            } else if (cliente_removido.prioridade == 2) {
                caixa->fila.ultimo_p2 = NULL;
            }
        }

        free(temp);
        caixa->fila.tamanho--;
        printf("\n%s foi atendido(a) no caixa %d.\n\n", cliente_removido.nome, caixa->id);
        return;
    }
}
void realocar_clientes_caixa(Caixa *caixas, int num_caixas)
{
    int fechar = 0;

    if (auxiliar == 4)
    {
        printf("\n\t[ATENÇÃO] Não é possível fechar mais caixas.\n");
        printf("\n-------------------------------------------------------------------------------------------------\n");
        return;
    }

    printf("\nNúmero do caixa que deseja fechar: ");
    scanf("%d", &fechar);

    int idx_fechar = -1;

    // Identificar o índice do caixa a ser fechado
    for (int i = 0; i < num_caixas; i++)
    {
        if (caixas[i].id == fechar)
        {
            idx_fechar = i;
            break;
        }
    }
    Caixa *caixa_fechar = &caixas[idx_fechar];

    if (idx_fechar == -1 || caixas[idx_fechar].estado == 0)
    {
        printf("\n\t[ERRO] Caixa inválido ou já fechado.\n");
        return;
    }

    else if (caixa_fechar->fila.tamanho == 0)
    {
        printf("\n\t[ATENÇÃO] O caixa %d já está vazio.\n", fechar);
        caixas[idx_fechar].estado = 0;
        auxiliar++;
        return;
    }

    // Lista de caixas abertos
    int caixas_abertos[num_caixas];
    int num_abertos = 0;
    for (int i = 0; i < num_caixas; i++)
    {
        if (caixas[i].estado == 1 && i != idx_fechar)
        {
            caixas_abertos[num_abertos++] = i;
        }
    }

    if (num_abertos == 0)
    {
        printf("\n\t[ERRO] Nenhum outro caixa aberto para realocar clientes.\n");
        return;
    }

    // Distribuir os clientes de forma equilibrada
    No *atual = caixa_fechar->fila.primeiro;
    while (atual != NULL)
    {
        // Encontrar o caixa com a menor fila entre os abertos
        int menor_fila_idx = caixas_abertos[0];
        for (int j = 1; j < num_abertos; j++)
        {
            if (caixas[caixas_abertos[j]].fila.tamanho < caixas[menor_fila_idx].fila.tamanho)
            {
                menor_fila_idx = caixas_abertos[j];
            }
        }

        // Realocar o cliente para o caixa com a menor fila
        inserir_fila_com_prioridade(&caixas[menor_fila_idx].fila, atual->cliente);
        caixas[menor_fila_idx].fila.tamanho++;

        // Avançar para o próximo cliente
        atual = atual->proximo;
    }

    // Limpar a fila do caixa fechado
    caixa_fechar->fila.primeiro = NULL;
    caixa_fechar->fila.ultimo = NULL;
    caixa_fechar->fila.ultimo_p1 = NULL;
    caixa_fechar->fila.ultimo_p2 = NULL;
    caixa_fechar->fila.tamanho = 0;

    // Fechar o caixa
    caixas[idx_fechar].estado = 0;
    auxiliar++;
    printf("\n\tCaixa %d fechado e clientes realocados com sucesso.\n", fechar);
}


void imprimir_clientes_espera(Caixa *caixas, int num_caixas)
{
    for (int i = 0; i < num_caixas; i++)
    {
        if (caixas[i].estado == 1)
        {

            printf("\n\tCAIXA %d\n", caixas[i].id);

            if (caixas[i].fila.tamanho == 0)
            {
                printf("\n\t[ATENÇÃO] Nenhum cliente em espera.\n");
                printf("\n-------------------------------------------------------------------------------------------------\n");
                continue;
            }

            No *atual = caixas[i].fila.primeiro;
            int p1 = 0, p2 = 0, p3 = 0; // Contadores para prioridades

            // Exibe clientes com prioridade 1
            printf("\n\tClientes com prioridade 1 (Alta):\n\n");
            atual = caixas[i].fila.primeiro;
            while (atual != NULL)
            {
                if (atual->cliente.prioridade == 1)
                {
                    p1++;
                    printf("Nome: %s\nCPF: %s\nItens: %d\nCaixa: %d\n\n",
                           atual->cliente.nome,
                           atual->cliente.cpf,
                           atual->cliente.numero_itens,
                           atual->cliente.n_caixa);
                }
                atual = atual->proximo;
            }

            // Exibe clientes com prioridade 2
            printf("\n\tClientes com prioridade 2 (Média):\n\n");
            atual = caixas[i].fila.primeiro;
            while (atual != NULL)
            {
                if (atual->cliente.prioridade == 2)
                {
                    p2++;
                    printf("Nome: %s\nCPF: %s\nItens: %d\nCaixa: %d\n\n",
                           atual->cliente.nome,
                           atual->cliente.cpf,
                           atual->cliente.numero_itens,
                           atual->cliente.n_caixa);
                }
                atual = atual->proximo;
            }

            // Exibe clientes com prioridade 3
            printf("\n\tClientes com prioridade 3 (Baixa):\n\n");
            atual = caixas[i].fila.primeiro;
            while (atual != NULL)
            {
                if (atual->cliente.prioridade == 3)
                {
                    p3++;
                    printf("Nome: %s\nCPF: %s\nItens: %d\nCaixa: %d\n\n",
                           atual->cliente.nome,
                           atual->cliente.cpf,
                           atual->cliente.numero_itens,
                           atual->cliente.n_caixa);
                }
                atual = atual->proximo;
            }

            // printf("\nResumo: %d clientes de prioridade 1, %d de prioridade 2, %d de prioridade 3.\n", p1, p2, p3);
        }
        else
        {
            printf("\nCaixa %d está fechado.\n", caixas[i].id);
        }

        printf("\n-------------------------------------------------------------------------------------------------\n");
    }
}

void exibir_estado_caixas(Caixa *caixas, int num_caixas)
{
    for (int i = 0; i < num_caixas; i++)
    {

        if (caixas[i].estado == 1)
        {
            printf("\nCaixa %d: Aberto\n", caixas[i].id);
        }
        else
        {
            printf("\nCaixa %d: Fechado\n", caixas[i].id);
        }

        printf("\nNúmero de clientes em espera: %d\n", caixas[i].fila.tamanho);
        printf("\n-------------------------------------------------------------------------------------------------\n");
    }
}

void abrir_caixa(Caixa *caixas, int num_caixas)
{

    int abrir = 0;

    printf("\nNúmero do caixa que deseja abrir: ");
    scanf("%d", &abrir);

    for (int i = 0; i < num_caixas; i++)
    {
        if (caixas[i].id == abrir)
        {
            if (caixas[i].estado == 1)
            {
                printf("\nCaixa %d já está aberto.\n", abrir);
                return;
            }
            else
            {
                caixas[i].estado = 1;
                auxiliar--;
                return;
            }
        }
    }
}