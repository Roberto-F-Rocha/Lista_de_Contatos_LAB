# Agenda Telefônica em C

## Visão Geral

Este projeto implementa uma agenda telefônica simples em linguagem C, utilizando uma tabela hash para o armazenamento e gerenciamento de contatos. O sistema é operado via console e permite ao usuário realizar operações básicas como adicionar, buscar, remover e listar contatos.

## Funcionalidades

- **Inserir Contato:** Adiciona um novo contato à agenda, incluindo nome, telefone e e-mail.
- **Buscar Contato:** Permite encontrar um contato existente na agenda pelo nome.
- **Remover Contato:** Exclui um contato da agenda, especificado pelo nome.
- **Listar Contatos:** Exibe todos os contatos atualmente armazenados na agenda.

## Estrutura de Dados

O coração deste projeto é a implementação de uma **Tabela Hash** com tratamento de colisões (aparentemente utilizando sondagem quadrática, embora a estrutura `lista` sugira encadeamento). Cada entrada na tabela hash pode armazenar um `Contato`, que é definido pela seguinte estrutura:

```c
typedef struct contato{
	char *nome;
	char *tel;
	char *email;
}Contato;
```

## Como Compilar e Executar

Para compilar o projeto, você precisará de um compilador C (como o GCC). No terminal, navegue até o diretório onde o arquivo `.c` está salvo e execute o seguinte comando:

```bash
gcc nome_do_arquivo.c -o agenda
```

(Substitua `nome_do_arquivo.c` pelo nome do arquivo que contém o código-fonte, por exemplo, `pasted_content.c` se você salvou o conteúdo lá).

Após a compilação bem-sucedida, você pode executar o programa com:

```bash
./agenda
```

## Desenvolvedores

- ROBERTO FERNANDES ROCHA
- HILDI DANTE OLIVEIRA DE QUEIROZ
- RENATO ALVES PESSOA DE MEDEIROS

## Professor

- KENNEDY REURISON LOPES

## Instituição

- Universidade Federal Rural do Semi-árido (UFERSA)
- Disciplina: LABORATÓRIO DE ALGORITMOS E ESTRUTURAS DE DADOS II


