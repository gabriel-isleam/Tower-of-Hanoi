/* ISLEAM Gabriel-Mihai 315 CB */
#include "header.h"

void IntrQ(TCoada coada, TLista element_nou)
{
	if (coada->inceput == coada->sfarsit && coada->sfarsit == NULL)
		coada->inceput = coada->sfarsit = element_nou;

	else
	{
		coada->sfarsit->urm = element_nou;
		coada->sfarsit = element_nou;
	}
}

TLista ExtrQ(TCoada coada)
{
	TLista aux = coada->inceput;
	if (coada->inceput->urm == NULL)
		coada->inceput = coada->sfarsit = NULL;
	else 
		coada->inceput = coada->inceput->urm;
	return aux;	
}

void ConcatQ(TCoada coada_sursa, TCoada coada_dest)
{
	if (coada_dest->inceput == coada_dest->sfarsit && coada_dest->inceput == NULL)
		coada_dest->inceput = coada_sursa->inceput;
		
	else
		coada_dest->sfarsit->urm = coada_sursa->inceput;
	coada_dest->sfarsit = coada_sursa->sfarsit;
	coada_sursa->inceput = coada_sursa->sfarsit = NULL;
}

TLista Pop(TStiva stiva)
{
	if (stiva->varf == NULL)
		return NULL;
	TLista aux = stiva->varf;
	stiva->varf = stiva->varf->urm;
	if (stiva->varf == NULL)
		stiva->baza = NULL;
	return aux;
}

void Push(TStiva stiva, TLista element)
{
	TLista aux = stiva->varf;
	stiva->varf = element;
	stiva->varf->urm = aux;
	if (aux == NULL)
		stiva->baza = element;
}

void Overlay(TStiva stiva_sursa, TStiva stiva_destinatie)
{
	stiva_sursa->baza->urm = stiva_destinatie->varf;
	stiva_destinatie->varf = stiva_sursa->varf;
	if (stiva_destinatie->baza == NULL)
		stiva_destinatie->baza = stiva_sursa->baza;
	stiva_sursa->baza = stiva_sursa->varf = NULL;
}

void FreeStack(TStiva stiva)
{
	TLista p = stiva->varf, aux = NULL;
	if (stiva->varf == NULL)
	{
		free(stiva);
		return;
	}
	while (p != stiva->baza)
	{
		aux = p->urm;
		free(p->info);
		free(p);
		p = aux;
	}
	free(((TLista)(stiva->baza))->info);
	free(stiva->baza);
	free(stiva);
}

void FreeQueue(TCoada coada)
{
	TLista p = coada->inceput, aux = NULL;
	if (p == NULL)
	{
		free(coada);
		return;
	}
	while (p != coada->sfarsit)
	{
		aux = p->urm;
		free(p->info);
		free(p);
		p = aux;
	}
	free(((TLista)(coada->sfarsit))->info);
	free(coada->sfarsit);
	free(coada);
}

void Overturn(TStiva stiva)
{
	if (stiva->varf == NULL || stiva->varf == stiva->baza)
		return;
	TStiva stiva_aux = (TStiva)malloc(sizeof(Stiva));
	if (!stiva_aux)
		return;
	stiva_aux->varf = stiva_aux->baza = NULL;
	TLista aux = NULL;
	while (stiva->varf != NULL)
	{
		aux = Pop(stiva);
		Push(stiva_aux, aux);
	}

	Overlay(stiva_aux, stiva);
	FreeStack(stiva_aux);
}

void Display(TStiva stiva, FILE *output)
{
	if (stiva->varf != NULL)
	{
		TStiva stiva_aux = (TStiva)malloc(sizeof(Stiva));
		stiva_aux->varf = stiva_aux->baza = NULL;
		TLista varf = NULL;
		while (1)
		{
			varf = Pop(stiva);
			Push(stiva_aux, varf);
			fprintf(output, " %d", *(int*)varf->info);
			if (stiva->varf == NULL)
			{
				fprintf(output, "\n");									
				Overlay(stiva_aux, stiva);
				free(stiva_aux);
				return;
			}				
		}
	}
	else
		fprintf(output, "\n");
}

void Show(TLista L, char *culoare, FILE *output)
{
	while (L != NULL)
	{
		if (strcmp(((TSistem)(L->info))->culoare, culoare) == 0)
			break;
		L = L->urm;
	}

	if(L != NULL)
	{
		fprintf(output, "A_%s:", culoare);
		TStiva stiva_A = ((TSistem)(L->info))->A;
		Overturn(stiva_A);
		Display(stiva_A, output);

		fprintf(output, "B_%s:", culoare);
		TStiva stiva_B = ((TSistem)(L->info))->B;
		Overturn(stiva_B);
		Display(stiva_B, output);

		fprintf(output, "C_%s:", culoare);
		TStiva stiva_C = ((TSistem)(L->info))->C;
		Overturn(stiva_C);
		Display(stiva_C, output);
	}

	else
		fprintf(output, "A_%s:\nB_%s:\nC_%s:\n", culoare, culoare, culoare);
}

void AddDisk(TLista L, void *dimensiune, size_t d)
{
	TLista element_nou = (TLista)malloc(sizeof(Celula));
	if (!element_nou)
		return;
	element_nou->info = malloc(d);
	if (!element_nou->info)
	{
		free(element_nou);
		return;
	}
	memcpy(element_nou->info, dimensiune, d);

	TStiva stiva_aux = (TStiva)malloc(sizeof(Stiva));
	if (!stiva_aux)
	{
		free(element_nou->info);
		free(element_nou);
		return;
	}
	stiva_aux->varf = stiva_aux->baza = NULL;

	((TSistem)(L->info))->numar_discuri ++;
	TStiva stiva_A = ((TSistem)(L->info))->A;
	TLista aux = NULL;
	if (*(int*)dimensiune < *(int*)stiva_A->varf->info)
		Push(stiva_A, element_nou);
	else if ((*(int*)dimensiune > *(int*)stiva_A->baza->info))
	{
		Overlay(stiva_A, stiva_aux);
		Push(stiva_A, element_nou);
		Overlay(stiva_aux, stiva_A);
	}
	else
	{
		while (*(int*)dimensiune > *(int*)stiva_A->varf->info)
		{
			aux = Pop(stiva_A);
			Push(stiva_aux, aux);
		}
		Push(stiva_A, element_nou);
		Overturn(stiva_aux);
		Overlay(stiva_aux, stiva_A);
	}
	FreeStack(stiva_aux);
}

TLista SystemAllocation(char *culoare, void *dimensiune, size_t d)
{
	TLista primul_element = (TLista)malloc(sizeof(Celula));				//primul element din stiva A	
	if (!primul_element)
		return NULL;					
	primul_element->info = malloc(d); 
	if (!primul_element->info)
	{
		free(primul_element);
		return NULL;
	}									
	memcpy(primul_element->info, dimensiune, d);
	primul_element->urm = NULL;

	TStiva stiva_A = (TStiva)malloc(sizeof(Stiva));
	if (!stiva_A)
	{
		free(primul_element->info);
		free(primul_element);
		return NULL;
	}	
	stiva_A->baza = primul_element;
	stiva_A->varf = primul_element;

	TStiva stiva_B = (TStiva)malloc(sizeof(Stiva));
	if (!stiva_B)
	{
		free(stiva_A);
		free(primul_element->info);
		free(primul_element);
		return NULL;
	}	
	stiva_B->baza = stiva_B->varf = NULL;

	TStiva stiva_C = (TStiva)malloc(sizeof(Stiva));
	if (!stiva_C)
	{
		free(stiva_B);
		free(stiva_A);
		free(primul_element->info);
		free(primul_element);
		return NULL;
	}	
	stiva_C->baza = stiva_C->varf = NULL;

	TCoada coada = (TCoada)malloc(sizeof(Coada));
	if (!coada)
	{
		free(stiva_C);
		free(stiva_B);
		free(stiva_A);
		free(primul_element->info);
		free(primul_element);
		return NULL;
	}
	coada->inceput = coada->sfarsit = NULL;
	coada->numar_mutari = 0;

	TSistem hanoi = (TSistem)malloc(sizeof(Sistem));
	if (!hanoi)
	{
		free(coada);
		free(stiva_C);
		free(stiva_B);
		free(stiva_A);
		free(primul_element->info);
		free(primul_element);
		return NULL;
	}
	hanoi->culoare = strdup(culoare);
	if (!hanoi->culoare)
	{
		free(hanoi);
		free(coada);
		free(stiva_C);
		free(stiva_B);
		free(stiva_A);
		free(primul_element->info);
		free(primul_element);
		return NULL;
	}
	hanoi->numar_discuri = 1;
	hanoi->A = stiva_A;
	hanoi->B = stiva_B;
	hanoi->C = stiva_C;
	hanoi->mutari = coada;

	TLista nou = (TLista)malloc(sizeof(Celula));
	if (!nou)
	{
		free(hanoi->culoare);
		free(hanoi);
		free(coada);
		free(stiva_C);
		free(stiva_B);
		free(stiva_A);
		free(primul_element->info);
		free(primul_element);
		return NULL;
	}
	nou->info = hanoi;
	nou->urm = NULL;

	return nou;	
}

void add(ALista Lista_sisteme, char *culoare, int dimensiune)
{
	TLista L = *Lista_sisteme, ant = NULL;
	int primul_null = 1;												//presupunem lista nulla
	while (L != NULL)
	{
		primul_null = 0;
		if (strcmp(((TSistem)(L->info))->culoare, culoare) == 0)
			break;
		ant = L;
		L = L->urm;
	}

	if (L == NULL)
	{
		TLista nou = SystemAllocation(culoare, &dimensiune, sizeof(int*));
		if (primul_null == 1)
			*Lista_sisteme = nou;
		else
			ant->urm = nou;
	}

	else
		AddDisk(L, &dimensiune, sizeof(int*));
}

void QueueInseration(TLista p, char from, char to)
{
	TMutari mutare = (TMutari)malloc(sizeof(Mutari));
	if (!mutare)
		return;
	mutare->from = from;
	mutare->to = to;

	TLista element_nou = (TLista)malloc(sizeof(Celula));
	if (!element_nou)
	{
		free(mutare);
		return;
	}
	element_nou->info = mutare;
	element_nou->urm = NULL;

	TCoada coada = ((TSistem)(p->info))->mutari;
	coada->numar_mutari++;

	IntrQ(coada, element_nou);
}

void Hanoi(TLista p, char from, char to, char other, int n)
{
	if (n == 1)
		QueueInseration(p, from, other);
	if (n > 1)
	{
		Hanoi(p, from, other, to, n-1);
		Hanoi(p, from, to, other, 1);
		Hanoi(p, to, from, other, n-1);
	}
}

void DisplayQueue(TLista p, char* culoare, int numar_mutari, FILE *output) //------------------------------------------------------
{
	while (p != NULL)
	{
		if (strcmp(((TSistem)(p->info))->culoare, culoare) == 0)
			break;
		p = p->urm;
	}

	fprintf(output, "M_%s:", culoare);
	TCoada coada = ((TSistem)(p->info))->mutari;
	if (coada->numar_mutari < 0)
	{
		fprintf(output, "\n");
		return;
	}
	TLista mutare = NULL;
	TCoada coada_aux = (TCoada)malloc(sizeof(Coada));
	coada_aux->inceput = coada_aux->sfarsit = NULL;

	if (numar_mutari > coada->numar_mutari)
		numar_mutari = coada->numar_mutari;

	while (numar_mutari > 0)
	{
		mutare = ExtrQ(coada);
		IntrQ(coada_aux, mutare);
		fprintf(output, " %c->%c", ((TMutari)(mutare->info))->from, ((TMutari)(mutare->info))->to);
		if (coada->inceput == NULL)
		{
			fprintf(output, "\n");
			ConcatQ(coada_aux, coada);
			free(coada_aux);
			return;
		}
		numar_mutari--;
	}

	fprintf(output, "\n");
	while (coada->inceput != NULL)						//muatarea cozii in continuare pentru a putea recupera coada initiala
	{
		mutare = ExtrQ(coada);
		IntrQ(coada_aux, mutare);
	}

	ConcatQ(coada_aux, coada);
	free(coada_aux);
}

void AddMoves(TLista Lista_sisteme, char *culoare, FILE *output)
{
	TLista p = Lista_sisteme;
	while (p != NULL)
	{
		if (strcmp(((TSistem)(p->info))->culoare, culoare) == 0)
			break;
		p = p->urm;
	}

	if (((TCoada)(((TSistem)(p->info))->mutari))->inceput != NULL)
		return;
																									   
	else if (((TCoada)(((TSistem)(p->info))->mutari))->numar_mutari < 0)		//--rezolva acest caz \|/
		return;

	int nr = ((TSistem)(p->info))->numar_discuri;
	Hanoi(p, 'A', 'B', 'C', nr);
}

void Play(TLista p, char *culoare, int numar_maini)
{
	while (p != NULL)
	{
		if (strcmp(((TSistem)(p->info))->culoare, culoare) == 0)
			break;
		p = p->urm;
	}

	char from, to;
	TLista aux = NULL;
	TLista element = NULL;
	TCoada mutari = ((TSistem)(p->info))->mutari;

	if (mutari->numar_mutari < 0)
		return;
	mutari->numar_mutari -= numar_maini;
	if (mutari->numar_mutari == 0)
		mutari->numar_mutari = -1;										//pentru a rezolva cazul cand coada e nula si numarul de 
	TStiva stiva_sursa = NULL, stiva_destinatie = NULL;					//mutari e 0 dupa o operatie play (caz identic cu cel dinainte
																		//de introducerea mutarilor in coada
	while (mutari->inceput != NULL && numar_maini > 0)
	{
		aux = mutari->inceput;
		from = ((TMutari)(mutari->inceput->info))->from;
		to = ((TMutari)(mutari->inceput->info))->to;
		if (from == 'A')
			stiva_sursa = ((TSistem)(p->info))->A;
		else if (from == 'B')
			stiva_sursa = ((TSistem)(p->info))->B;
		else
			stiva_sursa = ((TSistem)(p->info))->C;

		if (to == 'A')
			stiva_destinatie = ((TSistem)(p->info))->A;
		else if (to == 'B')
			stiva_destinatie = ((TSistem)(p->info))->B;
		else
			stiva_destinatie = ((TSistem)(p->info))->C;

		element = Pop(stiva_sursa);
		Push(stiva_destinatie, element);

		mutari->inceput = mutari->inceput->urm;
		free(aux->info);
		free(aux);
		numar_maini--;
	}
}

void SystemDestroy(TLista L)
{
	TLista aux = NULL;
	while (L != NULL)
	{
		aux = L->urm;
		free(((TSistem)(L->info))->culoare);

		FreeStack(((TSistem)(L->info))->A);
		FreeStack(((TSistem)(L->info))->B);
		FreeStack(((TSistem)(L->info))->C);
		FreeQueue(((TSistem)(L->info))->mutari);
		
		free(L->info);
		free(L);
		L = aux;
	}
}

void Read(ALista Lista_sisteme, FILE *input, FILE *output)
{
	int numar_comenzi, dimensiune, numar_mutari;
	char comanda[25], culoare[25];
	fscanf(input, "%d", &numar_comenzi);
	for (; numar_comenzi > 0; numar_comenzi--)
	{
		fscanf(input, "%s", comanda);
		if (strcmp(comanda, "add") == 0)
		{
			fscanf(input, "%s%d", culoare, &dimensiune);
			add(Lista_sisteme, culoare, dimensiune);
		}
		else if (strcmp(comanda, "show") == 0)
		{
			fscanf(input, "%s", culoare);
			Show(*Lista_sisteme, culoare, output);
		}
		else if (strcmp(comanda, "play") == 0)								//adaugare mutari pentru toate culorile
		{
			fscanf(input, "%s%d", culoare, &numar_mutari);
			AddMoves(*Lista_sisteme, culoare, output);
			Play(*Lista_sisteme, culoare, numar_mutari);
		}
		else if (strcmp(comanda, "show_moves") == 0)
		{
			fscanf(input, "%s%d", culoare, &numar_mutari);
			AddMoves(*Lista_sisteme, culoare, output);
			DisplayQueue(*Lista_sisteme, culoare, numar_mutari, output);
		}
	}	
	SystemDestroy(*Lista_sisteme);
}