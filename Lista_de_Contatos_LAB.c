#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 32

typedef struct contato{
    char *nome;
    char *tel;
    char *email;
}Contato;

struct lista{
    Contato *contato;
    struct lista *prox;
};

Contato *criaContato(char *nome, char *tel, char *email){
    Contato *novo = (Contato *) malloc(sizeof(Contato)); 
    
    novo->nome = (char *) malloc(strlen(nome) + 1);
    novo->tel = (char *) malloc(strlen(tel) + 1);
    novo->email = (char *) malloc(strlen(email) + 1);
    
    strcpy(novo->nome, nome);
    strcpy(novo->tel, tel);
    strcpy(novo->email, email);
    
 return (novo);
}

typedef struct lista *agendaDeContatos[size];

void iniciarAgenda(agendaDeContatos Hash){
    int i;
    for(i = 0; i < size; i++){
        Hash[i] = NULL;
    }
}

int funHashDiv(char *chave){
    int key = 0, i = 0;
    while(chave[i] != '\0'){
        key += chave[i];
        i++;
    }
 return (key % size);
}

int inserir(agendaDeContatos Hash, Contato *c){
    int key = funHashDiv(c->nome);
    int tentativas = 0;
    int indice = key;

    while(Hash[indice] != NULL){
        tentativas++;
        indice = (key + tentativas * tentativas) % size;
        if (indice == key){
            printf("Tabela de hash cheia. Nao foi possovel inserir.\n");
            return -1;
        }
    }
    
    struct lista *novo = (struct lista *)malloc(sizeof(struct lista));
    if(novo == NULL){
        return -1;
    }

    novo->contato = c;
    novo->prox = NULL;
    Hash[indice] = novo;

return (indice);
}

Contato *buscarContato(agendaDeContatos Hash, char *nome){
    int key = funHashDiv(nome);
    int tentativas = 0;
    int indice = key;

    while(Hash[indice] != NULL){
        if(strcmp(Hash[indice]->contato->nome, nome) == 0){
            return Hash[indice]->contato;
        }
        tentativas++;
        indice = (key + tentativas * tentativas) % size;
        if(indice == key){
            break;
        }
    }
    
 return (NULL);
}

int removerContato(agendaDeContatos Hash, char *nome){
    int key = funHashDiv(nome);
    int tentativas = 0;
    int indice = key;

    while(Hash[indice] != NULL){
        if(strcmp(Hash[indice]->contato->nome, nome) == 0){
            free(Hash[indice]->contato->nome);
            free(Hash[indice]->contato->tel);
            free(Hash[indice]->contato->email);
            free(Hash[indice]->contato);
            free(Hash[indice]);
            Hash[indice] = NULL;
            return 1;
        }
        tentativas++;
        indice = (key + tentativas * tentativas) % size;
        if(indice == key){
            break;
        }
    }

 return (0);
}

void listarContatos(agendaDeContatos Hash){
    int i;
    for(i = 0; i < size; i++){
        struct lista *aux = Hash[i];
        while(aux != NULL){
            printf("\nNome: %s \n", aux->contato->nome);
            printf("Telefone: %s \n", aux->contato->tel);
            printf("Email: %s\n", aux->contato->email);
            aux = aux->prox;
        }
    }
}

void mostrarMenu(){
    printf("\nMenu:\n");
    printf("1. Inserir Contato\n");
    printf("2. Buscar Contato\n");
    printf("3. Remover Contato\n");
    printf("4. Listar Contatos\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

int main(){
    agendaDeContatos Hash;
    iniciarAgenda(Hash);

    int opcao;
    char nomeBusca[50];

    do{
        mostrarMenu();
        scanf("%d", &opcao);
		Contato *novoContato = (Contato *) malloc(sizeof(Contato));
        switch (opcao){
            case 1:
                if(novoContato != NULL){
                    novoContato->nome = (char *)malloc(50); 
                    novoContato->tel = (char *)malloc(50);
                    novoContato->email = (char *)malloc(50);
                    novoContato->nome[0] = '\0';
                    novoContato->tel[0] = '\0';
                    novoContato->email[0] = '\0';

                    printf("Digite o nome do contato: ");
                    scanf("%s", novoContato->nome);

                    printf("Digite o telefone do contato: ");
                    scanf("%s", novoContato->tel);

                    printf("Digite o email do contato: ");
                    scanf("%s", novoContato->email);

                    int resultado = inserir(Hash, novoContato);

                    if(resultado != -1){
                        printf("Contato inserido.\n");
                    } 
					else{
                        printf("Nao foi possivel inserir o contato.\n");
                    }
    			} 
				else{
                    printf("Erro ao alocar memoria para o novo Contato.\n");
                }
                break;

            case 2:
                printf("Digite o nome do contato a ser buscado: ");
                scanf("%s", nomeBusca);

                Contato *contatoEncontrado = buscarContato(Hash, nomeBusca);
                if(contatoEncontrado != NULL){
                    printf("Contato encontrado:\n");
                    printf("\n Nome: %s \n", contatoEncontrado->nome);
                    printf("Telefone: %s \n", contatoEncontrado->tel);
                    printf("Email: %s\n", contatoEncontrado->email);
                } 
				else{
                    printf("Contato nao encontrado.\n");
                }
                break;

            case 3:
                printf("Digite o nome do contato a ser removido: ");
                scanf("%s", nomeBusca);
                if(removerContato(Hash, nomeBusca)){
                    printf("Contato removido.\n");
                } 
				else{
                    printf("Contato nao encontrado para remover.\n");
                }
                break;

            case 4:
                listarContatos(Hash);
                break;
            case 5:
            	printf("Encerrar o Programa \n");
            	break;
            default:
                printf("Opcao invalida.\n");
        }
    }while(opcao != 5);
    
	int i;
    for(i = 0; i < size; i++){
        struct lista *aux = Hash[i];
        while(aux != NULL){
            struct lista *temp = aux;
            aux = aux->prox;
            free(temp->contato->nome);
            free(temp->contato->tel);
            free(temp->contato->email);
            free(temp->contato);
            free(temp);
        }
    }

return (0);
}