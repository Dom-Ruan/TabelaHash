#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
typedef struct Hash{
	char curso[10],nome[100],nummatr[10];
	struct Hash *prox;
}hash;

main(){
	setlocale(LC_ALL, "Portuguese");
	int opt,i;
	hash *h[31];
    for(i=0;i<31;i++)
    	h[i] = NULL;
		do{
        printf("\n\n1-Inserir aluno;\n2-Mostrar tabela;\n3-Buscar aluno\n4-Deletar aluno\n0-Fechar programa\n");
        scanf("%d",&opt);
        switch(opt){
        case 0: break;
        	case 1: 
				inserir(h);
        			break;
        case 2:	mostrar(h);
        		break;
        case 3: buscar(h);
        		break;
        case 4: deletar(h);
        		break;
        default: printf("Opção inválida\n");
        			break;
        }
	}while(opt!=0);
}
int funcaohash(char x[]){
	int i,a=0;
	for(i=0;i<strlen(x);i++){
		a+=x[i];
	}
	return a%31;
}
void inserir(hash *h[]){
	int pos;
	hash *s = malloc(sizeof(hash));
	printf("Digite o código do curso: ");
	fflush(stdin);
	scanf("%s",s->curso);
	printf("Digite o nome: ");
	fflush(stdin);
	fgets(s->nome, sizeof(s->nome), stdin);
	s->nome[strlen(s->nome)-1] = '\0';
	printf("Digite o número de matrícula: ");
	fflush(stdin);
	scanf("%s",s->nummatr);
	pos = funcaohash(s->nome);
	
if(h[pos]==NULL){
		h[pos] = s;
		h[pos]->prox = NULL;
	}
	else{
		hash *aux = h[pos];
		while(aux->prox!=NULL)
			aux = aux->prox;
		aux->prox = s;
		aux->prox->prox = NULL;
	}
}
void mostrar(hash *h[]){
	int i,j=1;
	printf("\n\nCurso nº Nome do Aluno Matr\n\n");
	for(i=0;i<31;i++){
		if(h[i]!=NULL){
		if(h[i]->prox==NULL){
		printf("%s %d %s %s\n\n",h[i]->curso,j,h[i]->nome,h[i]->nummatr);
		j++;
	}
		else{
			hash *aux;
			for(aux=h[i];aux!=NULL;aux=aux->prox){
				printf("%s %d %s %s\n\n",aux->curso,j,aux->nome,aux->nummatr);
				j++;
			}
		}
	}
	}
}
void buscar(hash *h[]){
	char x[100];
	int pos;
	printf("Digite o nome do aluno a ser buscado: ");
		fflush(stdin);
	fgets(x, sizeof(x), stdin);
	x[strlen(x)-1] = '\0';
	int i = funcaohash(x);
	if(h[i]==NULL)
		printf("Aluno não encontrado\n");
	else if(strcmp(h[i]->nome,x)==0)
		printf("\n\nCurso Nome do Aluno Matr\n\n%s %s %s\n",h[i]->curso,h[i]->nome,h[i]->nummatr);
	else{
		hash *aux;
		for(aux=h[i];aux!=NULL;aux=aux->prox){
			if(strcmp(aux->nome,x)==0){
				printf("\n\nCurso Nome do Aluno Matr\n\n%s %s %s\n",aux->curso,aux->nome,aux->nummatr);
				return;
			}
		}
		printf("Aluno não encontrado\n");
	}
}
void deletar(hash *h[]){
	char x[100];
		printf("Digite o nome do aluno que deseja deletar: ");
	fflush(stdin);
	fgets(x, sizeof(x), stdin);
	x[strlen(x)-1] = '\0';
	int i = funcaohash(x);
	if(h[i]==NULL)
		printf("Aluno não encontrado\n");
	else if(strcmp(h[i]->nome,x)==0){
		hash *aux = h[i];
		h[i] = h[i]->prox;
		free(aux);
		printf("Aluno deletado com sucesso\n");
	}
	else{
		hash *aux;
		for(aux=h[i];aux->prox!=NULL;aux=aux->prox){
			if(strcmp(aux->prox->nome,x)==0){
				hash *aux1 = aux->prox;
				aux->prox = aux->prox->prox;
				free(aux1);
				printf("Aluno deletado com sucesso\n");
				return;
			}
		}
		printf("Aluno não encontrado\n");
	}
}
