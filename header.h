/* ISLEAM Gabriel-Mihai - 315CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _LISTA_H_
#define _LISTA_H_

typedef struct celulag
{
	void *info;
	struct celulag *urm;
} Celula, *TLista, **ALista;

typedef struct 
{
	char from;
	char to;
} Mutari, *TMutari;

typedef struct
{ 
	TLista baza;		/* baza stivei */
	TLista varf; 		/* varful stivei */
} Stiva, *TStiva;


typedef struct
{ 			
	TLista inceput; 		// adresa primului element din coada 		
	TLista sfarsit; 		// adresa de sfarsit a cozii 				
	int numar_mutari;
} Coada, *TCoada;

typedef struct
{
	char *culoare;
	int numar_discuri;
	TStiva A, B, C;
	TCoada mutari;
} Sistem, *TSistem;

#endif

void Read(ALista Lista_sisteme, FILE *input, FILE *output);