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
    fila->tamanho = 0; // Inicializa o tamanho da fila como 0
    fila->tamanho = 0;
}
// Funções para validar a entrada
void inserir_fila_com_prioridade(Fila *f, Cliente c)

{
    No *novo = malloc(sizeof(No));
    if (!novo)
    {
        printf("Erro ao alocar memória para o novo nó.\n");
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
        f->ultimo_p1 = novo; // Atualiza o último com prioridade 1
    }
    else if (c.prioridade == 2)
    {
        if (f->ultimo_p2 == NULL)
        {
            if (f->ultimo_p1 == NULL)
            {
                // Inserir no início da fila (não há prioridade 1 nem 2)
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
        // Inserir no final da fila (prioridade 3)
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

int validar_entrada_numerica(const char *entrada) {
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (!isdigit(entrada[i])) {
            return 0; // Contém caracteres não numéricos
        }
    }
    return 1; 
}

int verificar_cpf_existe(Caixa *caixas, int num_caixas, const char *cpf) {
    for (int i = 0; i < num_caixas; i++) {
        No *atual = caixas[i].fila.primeiro;
        while (atual != NULL) {
            if (strcmp(atual->cliente.cpf, cpf) == 0) {
                return 1; // CPF já cadastrado
            }
            atual = atual->proximo;
        }
    }
    return 0; // CPF não encontrado
}

int validar_nome(char nome[])
{
    for (size_t i = 0; i < strlen(nome); i++)
    {
        if (!isalpha(nome[i]) && nome[i] != '\n')
        {
            return 0; // Nome inválido
        }
    }
    return 1; // Nome válido
}

int validar_cpf(const char *cpf)
{
    // Verifica se o CPF tem exatamente 11 caracteres
    if (strlen(cpf) != 11)
    {
        return 0;
    }
    // Verifica se todos os caracteres são números
    for (int i = 0; i < 11; i++)
    {
        if (!isdigit(cpf[i]))
        {
            return 0;
        }
    }
    return 1; // CPF válido
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
        printf("Cliente cadastrado: %s (CPF: %s) no caixa %d!\n", cliente.nome, cliente.cpf, cliente.n_caixa);
    }

    fclose(file);

    printf("\nClientes Cadastrados\n");
}

void cadastrar_cliente(Caixa *caixas, int num_caixas) {
    Cliente cliente;
    char entrada[20];

    printf("\n\tDigite as informações\n\n");

    // Solicitar o nome
    printf("\nNome: ");
    getchar();
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0'; // Remove o '\n' ao final da string

    // Solicitar e validar CPF
    do {
        printf("\nCPF (somente números, 11 dígitos): ");
        scanf("%s", cliente.cpf);

        if (!validar_cpf(cliente.cpf)) {
            printf("CPF inválido! Certifique-se de digitar apenas números e com 11 dígitos.\n");
        } else {
            if (verificar_cpf_existe(caixas, num_caixas, cliente.cpf)) {
                printf("CPF já cadastrado: %s\n", cliente.cpf);
            } else {
                break; // CPF válido e não cadastrado
            }
        }
    } while (1);

    // Solicitar prioridade
    do {
        printf("\nPrioridade: \n[1] Alta \n[2] Média \n[3] Baixa \n");
        scanf("%s", entrada);

        if (!validar_entrada_numerica(entrada) || (atoi(entrada) < 1 || atoi(entrada) > 3)) {
            printf("Prioridade inválida! Escolha entre 1, 2 ou 3.\n");
        } else {
            cliente.prioridade = atoi(entrada);
            break;
        }
    } while (1);

    // Solicitar o número de itens
    do {
        printf("\nNúmero de itens no carrinho: ");
        scanf("%s", entrada);

        if (!validar_entrada_numerica(entrada)) {
            printf("Entrada inválida! Digite apenas números.\n");
        } else {
            cliente.numero_itens = atoi(entrada);
            break;
        }
    } while (1);

    // Solicitar o número do caixa
    do {
        printf("\nNúmero Caixa: ");
        scanf("%s", entrada);

        if (!validar_entrada_numerica(entrada) || (atoi(entrada) < 1 || atoi(entrada) > num_caixas)) {
            printf("Caixa inválido! Escolha entre 1 e %d.\n", num_caixas);
        } else {
            cliente.n_caixa = atoi(entrada);
            break;
        }
    } while (1);

    printf("\n\tCliente cadastrado na fila do caixa %d!\n\n", cliente.n_caixa);

    // Inserir cliente na fila com prioridade
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

void remover_cliente(Caixa *caixa)
{

    if (caixa->fila.tamanho == 0)
    {
        printf("\nA fila do caixa %d está vazia.\n", caixa->id);
        return;
    }

    Cliente cliente_removido = caixa->fila.primeiro->cliente;

    No *temp = caixa->fila.primeiro;

    caixa->fila.primeiro = caixa->fila.primeiro->proximo; // Move o primeiro para o próximo nó

    // Se a fila agora estiver vazia, atualiza o último
    if (caixa->fila.primeiro == NULL)
    {
        caixa->fila.ultimo = NULL;
        caixa->fila.ultimo_p1 = NULL;
        caixa->fila.ultimo_p2 = NULL;
    }
    else
    {

        if (cliente_removido.prioridade == 1)
        {
            caixa->fila.ultimo_p1 = NULL;
        }
        else if (cliente_removido.prioridade == 2)
        {
            caixa->fila.ultimo_p2 = NULL;
        }
    }

    free(temp);
    caixa->fila.tamanho--;
    printf("\n%s foi atendido(a) %d.\n\n", cliente_removido.nome, caixa->id);
}

void realocar_clientes_caixa(Caixa *caixas, int num_caixas)
{
    int fechar = 0;

    if (auxiliar == 4)
    {
        printf("\nNão é possível fechar mais caixas\n");
        printf("\n-------------------------------------------------------------------------------------------------\n");

        return;
    }

    int resultado;

    printf("\nNúmero do caixa que deseja fechar: ");
    resultado = scanf("%d", &fechar);

    if (resultado != 1)
    {
        printf("Entrada inválida. Por favor, digite apenas números.\n");

        while (getchar() != '\n')
            ; // Limpa até a nova linha
    }
    else
    {
        if (fechar < 1 || fechar > num_caixas)
        {
            printf("Número do caixa inválido. Deve ser entre 1 e %d.\n", num_caixas);
        }

        else
        {
            printf("\nFechando o caixa %d...\n", fechar);
            auxiliar++;

            for (int i = 0; i < num_caixas; i++)
            {
                if (caixas[i].id == fechar)
                {
                    if (caixas[i].estado == 0)
                    {
                        printf("\nCaixa %d já está fechado.\n", fechar);
                        return;
                    }

                    for (int j = 0; j < num_caixas; j++)
                    {
                        if (caixas[j].estado == 1 && j != i)
                        { // Caixa deve estar aberto e não ser o caixa que está sendo fechado

                            printf("\nRealocando clientes do Caixa %d...\n", fechar);

                            int menor_fila_idx = -1;
                            int menor_tamanho = __INT_MAX__;

                            for (int j = 0; j < num_caixas; j++)
                            {
                                if (caixas[j].estado == 1 && j != i)
                                {

                                    if (caixas[j].fila.tamanho < menor_tamanho)
                                    {
                                        menor_tamanho = caixas[j].fila.tamanho;
                                        menor_fila_idx = j;
                                    }
                                }
                            }

                            if (menor_fila_idx != -1)
                            {
                                printf("\nClientes do Caixa %d serão realocados para o Caixa %d\n", fechar, caixas[menor_fila_idx].id);

                                No *atual = caixas[i].fila.primeiro;
                                while (atual != NULL)
                                {
                                    inserir_fila_com_prioridade(&caixas[menor_fila_idx].fila, atual->cliente);
                                    atual = atual->proximo;
                                }

                                // Zerar a fila do caixa fechado
                                caixas[i].fila.primeiro = NULL;
                                caixas[i].fila.ultimo = NULL;
                                caixas[i].fila.ultimo_p1 = NULL;
                                caixas[i].fila.ultimo_p2 = NULL;
                                caixas[i].fila.tamanho = 0;

                                caixas[i].estado = 0;
                                printf("\nCaixa %d fechado com sucesso.\n", fechar);
                            }

                            else
                            {
                                printf("\nNenhum outro caixa aberto disponível para realocação.\n");
                            }

                            return;
                            printf("\n-------------------------------------------------------------------------------------------------\n");
                        }
                    }
                }
            }
            printf("\nCaixa %d não encontrado.\n", fechar);
            printf("\n-------------------------------------------------------------------------------------------------\n");
        }
    }
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
                printf("\nNenhum cliente em espera.\n");
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

            //printf("\nResumo: %d clientes de prioridade 1, %d de prioridade 2, %d de prioridade 3.\n", p1, p2, p3);
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

    printf("\nNúmero do caixa que deseja abrirr: ");
    scanf("%d", &abrir);

    // Procura o caixa que deseja fechar

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