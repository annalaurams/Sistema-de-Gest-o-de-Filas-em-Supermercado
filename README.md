
<h1 align="center" font-size="200em"><b>Sistema de Gestão de Filas em Supermercado</b></h1>

<div align="center">

[![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%20Code-informational)](https://code.visualstudio.com/docs/?dv=linux64_deb)
![Make](https://img.shields.io/badge/Compilacao-Make-orange)
![Linguagem](https://img.shields.io/badge/Linguagem-C-blue)

</div>

---

## Sumário

1. [Objetivo](#-objetivo)
2. [Estrutura](#-estrutura)
3. [Considerações](#-considerações)
4. [Funcionalidades](#-funcionalidades)
5. [Ambiente de Desenvolvimento](#-ambiente-de-desenvolvimento)
6. [Compilação e Execução](#-compilação-e-execução)
7. [Contato](#-contato)


---

## 🎯 Objetivo

Este projeto consiste em desenvolver um sistema de gestão de filas para um supermercado, com atenção especial para grupos prioritários, como idosos, gestantes e pessoas com deficiência, de modo a proporcionar um atendimento eficiente e justo para todos.



## 🗂️ Estrutura

O projeto está organizado da seguinte maneira:


|— build/              # Diretório para arquivos compilados
|— data/               # Entrada
|— src/                # Códigos-fonte do sistema
|   |— funcoes.c       # Implementação das funcionalidades
|   |— funcoes.h       # Declaração de funções
|   |— main.c          # Função principal do programa
|   |— tipos.h         # Struct caixa, cliente e fila
|— Makefile            # Scripts para compilação




## 💡 Considerações

- O sistema é gerenciado por um switch case.
- Utiliza-se listas encadeadas para armazenar os registros de clientes nas filas de cada caixa.
- O sistema inicia com número fixo de 5 caixas, todos iniciam como abertos.
- Durante a execução, sempre há pelo menos 1 caixa aberto. 
- Não se pode cadastrar caixas além dos inicialmente disponíveis. 
- Cada caixa terá sua própria fila.
- Existe a opção de cadastrar manualmente clientes e caixas, ou realizar leitura dos arquivos. Inicialmente, está declarado o cadastro manual.

- **Prioridades:**
  - **1:** Alta
  - **2:** Média
  - **3:** Baixa

## 📝 Funcionalidades

- **Cadastro de Clientes:** Possibilidade de cadastrar clientes, fornecendo seu nível de prioridade e o caixa que deseja ser atendido.
- **Atender cliente:** Remover cliente da fila (com a prioridade maior) para ser atendido, no caixa escolhido.
- **Gerenciamento de Caixas:** Abertura e fechamento de caixas.
- **Distribuição de Clientes:** Realocação automática de clientes entre caixas, quando um deles é fechado, levando para o com a menor fila.
- **Imprimir a Lista de Clientes em Espera:** Mostrar clientes em espera em cada fila, de acordo com a prioridade.
- **Imprimir o Status dos Caixas:** Exibir o estado (aberto ou fechado) de cada caixa e o número de clientes em espera.


## 💻 Ambiente de Desenvolvimento

Este projeto foi desenvolvido e testado no seguinte ambiente:

- **Sistema Operacional:** Ubuntu 24.04.1 LTS
- **Arquitetura:** x86_64
- **Compilador C:** GCC 13.3.0
- **Ferramenta de Build:** GNU Make 4.3
- **Editor de Código:** Visual Studio Code
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



