#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct {
char cart[4];
}Cartas;
typedef struct {
char cart[48][4];
int quantia;
}JoBot;
void DfineCarta(Cartas ca[]){
	int na=0,pn=1;
	char naipe[4]={'%','@','#','&'};
	for(int i=0; i<52; i++){
		if(pn<10){
			ca[i].cart[0]=pn+'0';
			ca[i].cart[1]=naipe[na];
			ca[i].cart[2]='\0';
			pn+=1;
			}else{
				ca[i].cart[0]='1';
				ca[i].cart[1]=(pn-10)+'0';
				ca[i].cart[2]=naipe[na];
				ca[i].cart[3]='\0';
				pn+=1;
				if(pn==14){
					na+=1;
					pn=1;
					}
			}
	}
}
void printar(int quem,JoBot jb[]){
	printf("\n\nCartas do ");
	if(!quem){
		printf("Jogador\n");
	}else{
		printf("Bot\n");
		}
	for(int i=0; i<jb[quem].quantia; i++){
		printf("%s  ",jb[quem].cart[i]);
		}
	printf("\n\n");
}

int PosiMaior(int quem,JoBot jb[]){
	int pm,valor=0;
	for(int i=0; i<jb[quem].quantia; i++){
		int val=(strlen(jb[quem].cart[i])==3)?10+(jb[quem].cart[i][1]-'0'):
		jb[quem].cart[i][0]-'0';
		if(val>valor){
			valor=val;
			pm=i;
			}
	}
	return pm;
}
void DistribuiCart(int quem,int quantas,int *cartares,JoBot jb[],Cartas ca[]){
	for(int i=jb[quem].quantia; i<(jb[quem].quantia+quantas); i++){
		int sr=rand()%(*cartares);
		*cartares-=1;
		strcpy(jb[quem].cart[i],ca[sr].cart);
		strcpy(ca[sr].cart,ca[*cartares].cart);
		strcpy(ca[*cartares].cart,"0");
		}
	jb[quem].quantia+=quantas;
}
void Descart(int quem,int posi,JoBot jb[]){
	for(int i=posi; i<jb[quem].quantia-1; i++){
		char aux[4];
		strcpy(aux,jb[quem].cart[i+1]);
		strcpy(jb[quem].cart[i+1],jb[quem].cart[i]);
		strcpy(jb[quem].cart[i],aux);
		}
	jb[quem].quantia-=1;
	if(!quem){
		printf("\nJogador ");
	}else{
		printf("\nBot ");
	}
	printf("descartou a carta : %s\n\n",jb[quem].cart[jb[quem].quantia]);
}
int SePossivel(int quem,int pos[],char utc[],JoBot jb[]){
	int p=-1;
	char n1=(strlen(utc)==3) ? utc[2] : utc[1];
	for(int i=jb[quem].quantia-1; i>=0; i--){
		char n2=(strlen(jb[quem].cart[i])==3) ? jb[quem].cart[i][2] : jb[quem].cart[i][1];
		if(n1==n2){
			pos[++p]=i;
		}
	}
	return p;
}
void EscolhCart(int quem,char utc[],JoBot jb[]){
	if(!quem){
		printf("Escolha uma carta : \n");
		printar(quem,jb);
		while(1){
			printf("C> ");
			scanf(" %s",utc);
			for(int i=0; i<jb[quem].quantia; i++){
				if(strcmp(utc,jb[quem].cart[i])==0){
					Descart(quem,i,jb);
					return;
					}
				}
			printf("\nCarta invalida!!\n\n");
			}
	}
	int pm=PosiMaior(quem,jb);
	strcpy(utc,jb[quem].cart[pm]);
	Descart(quem,pm,jb);
}
void JogarBurro(int quem,int repet,int *cartares,char utc[],JoBot jb[],Cartas ca[]){
	int posi[52],poss=SePossivel(quem,posi,utc,jb);
	printar(1,jb);	
	if(!quem){
		if(poss>=0){
			printar(quem,jb);
			printf("Voce pode jogar as cartas :\n");
			for(int i=poss; i>=0; i--){
				printf("%s  ",jb[quem].cart[posi[i]]);
				}
			while(1){
				printf("\nC> ");
				scanf(" %s",utc);
				for(int i=poss; i>=0; i--){
					if(strcmp(utc,jb[quem].cart[posi[i]])==0){
						Descart(quem,posi[i],jb);
						quem=1;
						repet+=1;
					}
				}
			if(quem){
				break;
				}
			}
		}else{
			DistribuiCart(quem,1,cartares,jb,ca);
		}
	}else{	
		if(poss>=0){
			int po=posi[0];
			if(poss>0){
				for(int i=0; i<poss; i++){
					int val=(strlen(jb[quem].cart[posi[i]])==3) ? jb[quem].cart[posi[i]][1]-'0'+10 : 
					jb[quem].cart[posi[i]][0]-'0';
					int val1=(strlen(jb[quem].cart[posi[i+1]])==3) ? jb[quem].cart[posi[i+1]][1]-'0'+10 : 
					jb[quem].cart[posi[i+1]][0]-'0';
					if(val>val1){
						po=posi[i];
						}
					if(val<val1){
						po=posi[i+1];
						}
				}
			}
			Descart(quem,po,jb);
			quem=0;
			repet+=1;
		}else{
			DistribuiCart(quem,1,cartares,jb,ca);
			}
	}
	if(repet==2){
		int pm1=jb[0].quantia,pm2=jb[1].quantia,m1,m2;
		m1=(strlen(jb[0].cart[pm1])==3) ? 10+(jb[0].cart[pm1][1]-'0') : jb[0].cart[pm1][0]-'0';
		m2=(strlen(jb[1].cart[pm2])==3) ? 10+(jb[1].cart[pm2][1]-'0') : jb[1].cart[pm2][0]-'0';
		if(m1>m2){
			EscolhCart(0,utc,jb);
			quem=1;
			repet=1;
			}else{
			EscolhCart(1,utc,jb);
			quem=0;
			repet=1;
		}
	}
	if(poss>=0){
		printf("\n\nCartas restantes no monte : %d\n",*cartares);
		printf("Quantidade de carta Bot : %d\n",jb[1].quantia);
		printf("Quantidade de carta Jogador : %d\n\n",jb[0].quantia);
	}
	if(jb[0].quantia==0 || jb[1].quantia==0){
		return;
	}
	if(*cartares==0){
		return;
	}
	return JogarBurro(quem,repet,cartares,utc,jb,ca);	
}
int main(){
	//0 Jogador >1 Bot;
	srand(time(NULL));
	Cartas ca[52];
	JoBot jb[5];	
	while(1){
		jb[0].quantia=(jb[1].quantia=0);
		int cartares=52;
		DfineCarta(ca);
		DistribuiCart(0,3,&cartares,jb,ca);
		DistribuiCart(1,3,&cartares,jb,ca);
		char utc[4];
		Descart(1,PosiMaior(1,jb),jb);
		strcpy(utc,jb[1].cart[jb[1].quantia]);
		JogarBurro(0,1,&cartares,utc,jb,ca);
		if(jb[0].quantia<jb[1].quantia){
			printf("\nJogador ganhou !!\n");	
		}else{
			printf("\nBot ganhou !!\n");
		}
		printf("\nQue continua jogando (s)?\n");
		char sn;
		scanf(" %c",&sn);
		if(sn=='n'){
			return 0;
			}
		system("clear");	
	}

	return 0;
}
