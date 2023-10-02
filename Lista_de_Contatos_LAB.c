#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 32
#define MAX_NOME 50

void cabeca();
void erro();

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
	
 return(key % size);
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

void painel(){
	system("color 02");
	printf("\n   /////////////////////////////// \n");
	printf("\n  ///    AGENDA TELEFONICA    /// \n");
	printf("\n /////////////////////////////// \n\n");
}

void mostrarMenu(){
	painel();
	printf("+_+ Escolha uma opcao +_+ \n");
	printf("[1] -> Inserir Contato\n");
	printf("[2] -> Buscar Contato\n");
	printf("[3] -> Remover Contato\n");
	printf("[4] -> Listar Contatos\n");
	printf("[5] -> Sair\n");
	printf("digite sua opcao aqui >|  ");
}

int main(){
	cabeca();
	agendaDeContatos Hash;
	iniciarAgenda(Hash);

	int opcao, cont = 0;
	char nomeBusca[50];

	do{
		mostrarMenu();
		scanf("%d", &opcao);
		
		Contato *novoContato = (Contato *) malloc(sizeof(Contato));
		
		switch (opcao){
				case 1:
					
					cont++;
					system("cls");
					
					if (novoContato != NULL){
						
						novoContato->nome = (char *)malloc(MAX_NOME);
						novoContato->tel = (char *)malloc(50);
						novoContato->email = (char *)malloc(50);
						novoContato->nome[0] = '\0';
						novoContato->tel[0] = '\0';
						novoContato->email[0] = '\0';

						painel();
						
						printf("-> Digite o nome do contato: ");
						fflush(stdin);
						fgets(novoContato->nome, MAX_NOME, stdin);
						novoContato->nome[strcspn(novoContato->nome, "\n")] = '\0';

						printf("-> Digite o telefone do contato: ");
						fflush(stdin);
						fgets(novoContato->tel, 50, stdin);
						novoContato->tel[strcspn(novoContato->tel, "\n")] = '\0';

						printf("-> Digite o email do contato: ");
						fflush(stdin);
						fgets(novoContato->email, 50, stdin);
						novoContato->email[strcspn(novoContato->email, "\n")] = '\0';

						int resultado = inserir(Hash, novoContato);
						
						if(resultado != -1){
							printf("Contato inserido. :)\n");
							system("pause");
							system("cls");
						}
						else{
							erro();
							printf("Nao foi possivel inserir o contato. :(\n");
							system("pause");
							system("cls");
						}
					}
					else{
						erro();
						printf("Erro ao alocar memoria para o novo Contato.\n");
						system("pause");
						system("cls");
					}
					break;

				case 2:
					
					system("cls");
					painel();
					
					printf("-> Digite o nome do contato a ser buscado: ");
					fflush(stdin); 
					fgets(nomeBusca, sizeof(nomeBusca), stdin);
					nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

					Contato *contatoEncontrado = buscarContato(Hash, nomeBusca);
					
					if (contatoEncontrado != NULL){
						printf("Contato encontrado:\n");
						printf("\nNome: %s \n", contatoEncontrado->nome);
						printf("Telefone: %s \n", contatoEncontrado->tel);
						printf("Email: %s\n", contatoEncontrado->email);
						system("pause");
					}
					else{
						printf("Contato nao encontrado.\n");
						system("pause");
					}
					break;

				case 3:
					
					system("cls");
					painel();
					
					printf("-> Digite o nome do contato a ser removido: ");
					fflush(stdin);
					fgets(nomeBusca, sizeof(nomeBusca), stdin);
					nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

					if (removerContato(Hash, nomeBusca)){
						printf("Contato removido.\n");
	  	  	  	    }	
					else{
						printf("Contato nao encontrado para remover.\n");
					}
					break;
				case 4:
					
					system("cls");
					painel();
					
					printf("///////////////////////////////// \n");
					printf("//     LISTA DOS CONTATOS      // \n");
					printf("///////////////////////////////// \n\n");
					
					if(cont == 0){
						erro();
						printf("////////////////////////////// \n");
						printf("// NENHUM CONTATO INSERIDO  // \n");
						printf("////////////////////////////// \n\n");
						system("pause");
						system("cls");
					}
					else{
						listarContatos(Hash);
						printf("\n\n");
						system("pause");
						system("cls");
					}
					break;
				case 5:
					printf("+++ PROGRAMA ENCERRADO +++\n");
					break;
				default:
					
					system("cls");
					erro();
					
					printf("+++++++++++++++++++++  // OPCAO INVALIDA //  +++++++++++++++++++++\n");
					system("pause");
					system("color 02");
					system("cls");
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

void cabeca(){
	system("color 02");
	printf("        Universidade Federal Rural do Semi-arido (UFERSA)         \n");
	printf("            Bacharelado em Tecnologia da Informacao               \n");
	printf("   Disciplina: LABORAToRIO DE ALGORITMOS E ESTRUTURAS DE DADOS II  \n");
	printf("              Professor: KENNEDY REURISON LOPES                   \n\n");
	printf("          _+_+_+_  PROJETO LISTA TELEFONICA   _+_+_+_             \n");
	printf("           Discente: ROBERTO FERNANDES ROCHA                      \n");
	printf("           Discente: HILDI DANTE OLIVEIRA DE QUEIROZ              \n");
	printf("           Discente: RENATO ALVES PESSOA DE MEDEIROS              \n");
	system("pause");
	system("cls");
}

// ZOAS

void erro(){
	system("color 04");
	printf("\n !!!!!!!!!!     !!!!!!!!!!     !!!!!!!!!!     !!!!!!!!!!     !!!!!!!!!! \n");
	printf(" !!!!!!!!!!     !!!!!!!!!!     !!!!!!!!!!     !!!!!!!!!!     !!!!!!!!!! \n");
	printf(" !!!            !!!    !!!     !!!    !!!     !!!    !!!     !!!    !!! \n");
	printf(" !!!!!!         !!!    !!!     !!!    !!!     !!!    !!!     !!!    !!! \n");
	printf(" !!!!!!         !!!!!!!!!!     !!!!!!!!!!     !!!    !!!     !!!!!!!!!! \n");
	printf(" !!!            !!!  !!!       !!!  !!!       !!!    !!!     !!!  !!!   \n");
	printf(" !!!!!!!!!!     !!!   !!!      !!!   !!!      !!!!!!!!!!     !!!   !!!  \n");
	printf(" !!!!!!!!!!     !!!    !!!     !!!    !!!     !!!!!!!!!!     !!!    !!! \n\n");
}