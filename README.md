
<h1 align="center" font-size="200em"><b>Sistema de Gestão de Filas em Supermercado</b></h1>

<div align="center">

[![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%20Code-informational)](https://code.visualstudio.com/docs/?dv=linux64_deb)
![Make](https://img.shields.io/badge/Compilacao-Make-orange)
![Linguagem](https://img.shields.io/badge/Linguagem-C-blue)

</div>

---

## Sumário

1. [Objetivo](#-objetivo)
2. [Estrutura](#estrutura)
3. [Considerações](#-considerações)
4. [Funcionalidades](#-funcionalidades)
5. [Ambiente de Desenvolvimento](#-ambiente-de-desenvolvimento)
6. [Compilação e Execução](#-compilação-e-execução)
7. [Contato](#-contato)


---

## 🎯 Objetivo

Este projeto consiste em desenvolver um sistema de gestão de filas para um supermercado, com atenção especial para grupos prioritários, como idosos, gestantes e pessoas com deficiência, de modo a proporcionar um atendimento eficiente e justo para todos.


## Estrutura

A organização do projeto segue a seguinte estrutura:
### 📂 **build/**  
> Diretório para arquivos compilados.

### 📂 **data/**  
> Contém os arquivos de entrada de dados.

### 📂 **src/**  
> Diretório com os códigos-fonte do sistema:  
- **funcoes.c**: Implementação das funcionalidades.  
- **funcoes.h**: Declaração das funções.  
- **main.c**: Função principal do programa.  
- **tipos.h**: Definição das structs (*caixa, cliente e fila*).  

### 📄 **Makefile**  
> Scripts para a compilação do sistema.

## 💡 Considerações

#### Gerenciamento das Filas

O gerenciamento das filas no sistema é realizado utilizando uma estrutura de **lista encadeada**, composta por nós que armazenam os dados dos clientes e apontam para o próximo na fila. A estrutura da fila é representada por ponteiros que controlam:

- **primeiro**: Aponta para o início da fila.
- **ultimo**: Aponta para o final da fila.
- **ultimo_p1**: Último cliente de prioridade alta.
- **ultimo_p2**: Último cliente de prioridade média.

Na remoção, o primeiro cliente é retirado, e o ponteiro `primeiro` é atualizado para o próximo nó. Caso necessário, os ponteiros das prioridades (`ultimo_p1`, `ultimo_p2`) também são ajustados. 

#### Prioridades

  - **1 Alta** -  Sempre atendidos primeiro, inseridos no início da fila ou após o último de alta prioridade.
  - **2 Média** - Inseridos após os de alta prioridade (1), mas antes dos de baixa (3).
  - **3 Baixa** - Inseridos no final da fila.

#### Informações Adicionais

- O sistema é gerenciado por um switch case.
- O sistema inicia com número fixo de 5 caixas, todos iniciam como abertos.
- Durante a execução, sempre há pelo menos 1 caixa aberto. São configurados via leitura de um arquivo intitulado `caixas.txt`. Onde uma linha é o identificador do caixa e a outra o valor `1` corresponde a variável boleana estado, que indica que estã aberto.
- Não se pode cadastrar caixas além dos inicialmente disponíveis. 
- Cada caixa terá sua própria fila.
- Durante a execução do sistema, sempre haverá pelo menos um caixa aberto. Os caixas são configurados através da leitura do arquivo `caixas.txt`, no início do programa, onde:  
  - Cada linha contém o identificador do caixa.  
  - A linha seguinte contém o valor `1` para indicar que o caixa está aberto (variável booleana `estado`).  
- O sistema permite o cadastro de clientes de forma manual ou através da leitura do arquivo `clientes.txt`. Por padrão, o cadastro manual está configurado, mas é possível alterar a chamada da função no código para habilitar a leitura via arquivo.  
- Na leitura de arquivo, as informações devem ser fornecidas na seguinte ordem:  
  1. **Nome**  
  2. **CPF** (11 dígitos)  
  3. **Prioridade**  
  4. **Número de itens no carrinho**  
  5. **Caixa escolhido**  

- Para a leitura dos arquivos, cada informação deve ser fornecida em uma linha separada, seguindo a ordem especificada, com os dados organizados um abaixo do outro.

## 📝 Funcionalidades

- **Cadastro de Clientes:** Possibilidade de cadastrar clientes, fornecendo seu nome, cpf (11 dígitos), nível de prioridade, número de itens no carrinho e o caixa que deseja ser atendido.
- **Atender cliente:** Remover cliente da fila (com a prioridade maior) para ser atendido, no caixa escolhido.
- **Gerenciamento de Caixas:** Abertura e fechamento de caixas, com realocação automática de clientes entre caixas, quando um deles é fechado, levando para o com a menor fila.
- **Imprimir a Lista de Clientes em Espera:** Mostrar clientes em espera em cada fila, de acordo com a prioridade.
- **Imprimir o Status dos Caixas:** Exibir o estado (aberto ou fechado) de cada caixa e o número de clientes em espera.


## 💻 Ambiente de Desenvolvimento

Este projeto foi desenvolvido e testado no seguinte ambiente:

- **Sistema Operacional:** Ubuntu 24.04.1 LTS
- **Compilador C:** GCC 13.3.0
- **IDE:** Visual Studio Code
- **Linguagem de Programação:** C


## 👾 Compilação e Execução

Os comandos a seguir são utilizados para compilar e executar o sistema:

| Comando                | Função                                                                                           |
|------------------------|---------------------------------------------------------------------------------------------------|
| `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
| `make`                | Realiza a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
| `make run`            | Executa o programa após a compilação                                                               |

---

## 📞 Contato

<div>
 <p align="justify">Anna Laura Moura Santana</p>
 <a href="https://t.me/">
 <img align="center" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/>
 </a>
</div>
<a style="color:black" href="mailto:nalauramoura@gmail.com?subject=[GitHub]%20Source%20Dynamic%20Lists">
✉️ <i>nalauramoura@gmail.com</i>
</a>



