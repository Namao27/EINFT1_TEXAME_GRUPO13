#inlude <stringh>
#include "Ordenacao.h"


int compararPalaras(onst char *a, const char *b){
return _stricmp(a,b);

}

void quickSort(Palavras *lista, int inicio, int fim ){
	if (inicio>= fim) return;
	
	int esq= inicio;
	int dir= fim;
	Conceito pivo = lista[(inicio + fim)/2];
	
	while (esq<=dir){
		while(compararPalavras(lista[esq].palavra, pivo.palavra)<0) esq++;
		while(ccompararPalavras(lista[dir].palavra, pivo.palavra)>0)
dir--;	

if(esq<=dir){
	Palavras temp =lista[esq];
	lista[esq]= lista[dir];
	lista[dir]= temp;
	esq++;
	dir--;
}
}
quickSort(lista, inicio,dir);
quickSort(lista, esq, fim);	
	}