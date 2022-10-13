#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Pessoas{
	char nome[100],cpf[100],token[100][25],headline[100][100];
	int quato;
	struct Pessoas* prox;
}Pessoas;
typedef struct Evento{
	char headline[100],token[1000][25];
	int dia,quato;
	struct Evento *prox;
}Evento;
int opcao(int dia){
	if(!dia){
		system("clear");
		return 1;
			}
	printf("Digite o numero para :\n");
	printf("1-Cadastrar Dia no Line-Up\n");
	char op[100];
	printf("2-Vender Ingresso\n3-Baixar Ingressos\n4-Listar Qtde e Tokens do Dia\n0-Sair\n");
	printf("o>");
	scanf(" %s",op);
	if(strlen(op)>1){
		return 9;
		}
	setbuf(stdin,NULL);
	system("clear");
	return op[0]-'0';
}
char *token(){
	char *aux;
	aux= (char *) malloc (sizeof(char)*26);
	for(int i=0; i<24; i++){
		int sr=rand()%10;
		aux[i]=sr+'0';
		aux[i+1]='\0';
	}
	return aux;
}
void retira (Pessoas **l,Evento **ev,char cpf[],int dia,int quem) {
	switch(quem){
		case 0:
		{
			Pessoas *ant = NULL,*p = *l; /* ponteiro para elemento anterior */
		/* ponteiro para percorrer a lista*/
		/* procura elemento na lista, guardando anterior */
			while (p != NULL && strcmp(cpf,p->cpf)!=0) {
				ant = p;
				p = p->prox;
			}
			if (p == NULL){
				return;
			}
			if (ant == NULL) {
/* retira elemento do inicio */
				*l = p->prox;
			}else{
/* retira elemento do meio da lista */
				ant->prox = p->prox;
			}
			free(p);
		}
		break;
		case 1:
		{
			Evento* ant = NULL,*p = *ev;
			while (p != NULL && dia!=p->dia) {
				ant = p;
				p = p->prox;
			}
			if (p == NULL){
				return;
			}
			if (ant == NULL) {
				*ev = p->prox;
			}else{
				ant->prox = p->prox;
			}
			free(p);
		}
		break;
	}	
}
void VenderIng(Pessoas **io,Evento **ev){
	Pessoas *novo=malloc(sizeof(Pessoas)),*aux=*io;
	Evento *edieve=malloc(sizeof(Evento)),*auxe=*ev;
	while(1){
		int i=1;	
		printf("Nome : ");
		scanf(" %[^\n]s",novo->nome);
		printf("Cpf : ");
		scanf(" %[^\n]s",novo->cpf);
		novo->quato=0;
		for(aux=*io; aux!=NULL; aux=aux->prox){
			if(strcmp(aux->cpf,novo->cpf)==0){
				if(strcmp(aux->nome,novo->nome)==0){
					*novo=*aux;
					retira(io,ev,novo->cpf,0,0);
					//novo->prox=*io;
					//*io=novo;
					break;
				}
				i=0;
				printf("CPF ja cadastrado com nome diferente\n");
				break;
			}
		}
		if(i){
			for(auxe=*ev; auxe->prox!=NULL; auxe=auxe->prox){
				printf("Banda do Dia %d",auxe->dia);
				printf("\n%s\n",auxe->headline);
			}
			while(1){
				printf("Escolha o dia : ");
				int di;
				scanf(" %d",&di);
				for(auxe=*ev; auxe->prox!=NULL; auxe=auxe->prox){
					if(di==auxe->dia){
						*edieve=*auxe;
						strcpy(novo->token[novo->quato],token());
						strcpy(novo->headline[novo->quato],edieve->headline);
						strcpy(edieve->token[edieve->quato++],novo->token[novo->quato]);
						//printf("\n%s\n",pe[pas].token[pe[pas].quato-1]);
						printf("TOKEN REGISTRADO ENTER PARA CONTINUAR:\n%s\n",novo->token[novo->quato++]);
						retira(io,ev,"",auxe->dia,1);
						edieve->prox=*ev;
						*ev=edieve;
						novo->prox=*io;
						*io=novo;
						setbuf(stdin,NULL);
						getchar();
						system("clear");
						return;
					}
				}
		printf("Dia invalido\n\n");
			}
		}
	}
}
Evento* CadastraEvent(int dia,Evento *ev){
	Evento *novo=malloc(sizeof(Evento));
	printf("Evento do %dº dia\n",dia+1);
	printf("Nome da headline : ");
	scanf(" %[^\n]s",novo->headline);
	novo->quato=0;
	novo->dia=dia+1;
	novo->prox=ev;
	return novo;
}
void Baixar(Pessoas **pe){
	Pessoas *edipes=malloc(sizeof(Pessoas)),*aux=*pe;
	while(1){
		printf("Digite o CPF : ");
		char cpf[18];
		scanf(" %[^\n]s",cpf);
		for(aux=*pe; aux!=NULL; aux=aux->prox){
			if(strcmp(cpf,aux->cpf)==0){
				printf("Nome : %s\n",aux->nome);
				strcpy(edipes->nome,aux->nome);
				strcpy(edipes->cpf,aux->cpf);
				if(aux->quato==0){
					printf("Todos tokens ja baixados\n");
					printf("\nENTER para continuar");
					setbuf(stdin,NULL);
					getchar();
					free(edipes);
					return;
				}
				for(int o=0; o<aux->quato; o++){
					printf("headline : %s\n",aux->headline[o]);
					strcpy(edipes->headline[o],aux->headline[o]);
					printf("token : %s\n",aux->token[o]);
				}
				edipes->quato=0;
				retira(pe,NULL,aux->cpf,0,0);	
				edipes->prox=*pe;
				*pe=edipes;					
				printf("ENTER para continuar");
				setbuf(stdin,NULL);
				getchar();
				system("clear");
				return;	
			}
		}
		printf("CPF nao registrado\nDigite qualquer letra para digitar outro cpf\nENTER para \n\n");
		setbuf(stdin,NULL);
		if(getchar()=='\n'){
			system("clear");
			return;	
		}
		system("clear");
	}
	
}
void Listartd(Evento *ev,Pessoas *pe){
	Evento *l=ev;
	Pessoas *p=pe;
	//int i=0;
	for(l=ev;l != NULL;l = l->prox){
		printf("%s\n",l->headline);
		for(int i=0; i<l->quato; i++){
			printf("\n%s\n",l->token[i]);
		}
	}
	for(p=pe;p != NULL;p = p->prox){
		printf("\n%s\n",p->nome);
		printf("\n%s\n",p->cpf);
		for(int i=0; i<p->quato; i++){
			printf("\n%s\n",p->token[i]);
		}
	}
}
void Listar(Evento *ev){
	Evento *auxe=ev;
	for(auxe=ev; auxe->prox!=NULL; auxe=auxe->prox){
		printf("Banda do Dia %d :  ",auxe->dia);
		printf("%s\n\n",auxe->headline);
	}
	while(1){
		printf("Listar token do dia : ");
		int op;
		scanf(" %d",&op);
		for(auxe=ev; auxe->prox!=NULL; auxe=auxe->prox){
			if(op==auxe->dia){
				printf("Quantidade de tokens : %d\n\n",auxe->quato);
				for(int o=0; o<auxe->quato; o++){
					printf("%s\n\n",auxe->token[o]);
				}
				printf("ENTER para continuar");
				setbuf(stdin,NULL);
				getchar();
				system("clear");
				return;	
			}
		}
		printf("\nDia invalido\n");
	}
}
int main()
{
	srand(time(NULL));
	Evento *ev=malloc(sizeof(Evento));
	Pessoas *pe=malloc(sizeof(Pessoas));;
	ev->prox=NULL;
	pe->prox=NULL;
	int dia=0;
	while(1){
		switch(opcao(dia)){
			case 1:
				ev=CadastraEvent(dia++,ev);
			break;
			case 2:
				VenderIng(&pe,&ev);
			break;
			case 3:
				Baixar(&pe);
			break;
			case 4:
				Listar(ev);
			break;
			
			default:
				printf("Opcao invalido\n\n");
			break;
		}
	}
	free(ev);free(pe);
	return 0;
}

