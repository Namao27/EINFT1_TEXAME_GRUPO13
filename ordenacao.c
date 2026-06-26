#include <string.h>
#include "ordenacao.h"
/*#include "tipos.h"*/


int compararPalavra(const char *a, const char *b){
return _stricmp(a,b);

}

void quickSort(Palavra *lista, int inicio, int fim ){
	if (inicio>= fim) return;
	
	int esq= inicio;
	int dir= fim;
	Palavra pivo = lista[(inicio + fim)/2];
	
	while (esq<=dir){
		while(compararPalavra(lista[esq].palavra, pivo.palavra)<0) esq++;
		while(compararPalavra(lista[dir].palavra, pivo.palavra)>0) dir--;	

if(esq<=dir){
	Palavra temp =lista[esq];
	lista[esq]= lista[dir];
	lista[dir]= temp;
	esq++;
	dir--;
}
}
quickSort(lista, inicio,dir);
quickSort(lista, esq, fim);	
	}