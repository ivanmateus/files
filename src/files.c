#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "files.h"
#include "student.h"

void clean_stdin(void){		//Função que limpa stdin
	int c;
	while(c != '\n' && c != EOF){
		c = getchar();
	}
}

stdnt *SaveInFile(stdnt *Head){		//Função que salva os dados já coletados no arquivo de texto

	FILE *Students = fopen("students.txt", "wt");
	stdnt *Aux = Head;
	int i;

	while(Aux != NULL){
		fprintf(Students, "%s", Aux->Name);
		fprintf(Students, "%s", Aux->RegNum);
		i = 0;
		while(i < MAXTESTS){
			fprintf(Students, "%f ", Aux->TestGrade[i]);
			++i;
		}
		fprintf(Students, "\n");
		i = 0;
		while(i < MAXPROJS){
			fprintf(Students, "%f ", Aux->ProjGrade[i]);
			fprintf(Students, "%d ", Aux->PositInGroup[i]);
			fprintf(Students, "%d\n", Aux->NofMembers[i]);
			++i;
		}
		Aux = Aux->Next;
	}
	fclose(Students);
	return Head;
}

stdnt *Destroy(stdnt *Head){ //Função que apaga toda a lista
	if(Head == NULL){
		return Head;
	}

	Head->Next = Destroy(Head->Next);
	free(Head);
	return NULL;
}

stdnt *GetFromFile(stdnt *Head){	//Função que pega os dados do arquivo texto

	FILE *Students = fopen("students.txt", "rt");
	if(Students == NULL){
		Students = fopen("students.txt", "wt");
	}
	stdnt *Aux = NULL;
	Aux = InitStudent(Aux);
	int i;

	while(fgets(Aux->Name, MAXCHAR, Students)){
		fgets(Aux->RegNum, MAXCHAR, Students);
		i = 0;
		while(i < MAXTESTS){
			fscanf(Students, "%f ", &Aux->TestGrade[i]);
			++i;
		}
		i = 0;
		while(i < MAXPROJS){
			fscanf(Students, "%f ", &Aux->ProjGrade[i]);
			fscanf(Students, "%d ", &Aux->PositInGroup[i]);
			fscanf(Students, "%d ", &Aux->NofMembers[i]);
			++i;
		}
		Head = Insert(Head, Aux);
		Aux = InitStudent(Aux);
	}
	fclose(Students);
	free(Aux);
	return Head;
}
