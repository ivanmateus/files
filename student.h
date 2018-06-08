#ifndef STUDENT_H_
#define STUDENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "files.h"

#define MAXCHAR 100
#define MAXTESTS 2
#define MAXPROJS 4

struct student_type{	//Um nó que guarda os dados de um aluno
	char Name[MAXCHAR];	//Nome do aluno
	char RegNum[MAXCHAR];	//Número de matrícula do aluno
	float TestGrade[MAXTESTS];	//Nota das provas
	float ProjGrade[MAXPROJS];	//Nota dos trabalhos
	int PositInGroup[MAXPROJS];	//Posição do aluno em um grupo
	int NofMembers[MAXPROJS];	//Numero de membros no grupo
	struct student_type *Next;	//Ponteiro para o próximo aluno
};
typedef struct student_type stdnt;

stdnt *InitStudent(stdnt *Student);	//Função que inicializa um nó
stdnt *Insert(stdnt *Head, stdnt *NewStudent);	//Função que insere um novo aluno em ordem alfabética
stdnt *IncludeStudent(stdnt *Head);	//Função que recolhe o nome e nº de matrícula e insere um novo aluno
float IndividualGrade(float Grade, int Position, int NumberofMembers);	//Calcula o valor da nota individual do trabalho
stdnt *PrintStudent(stdnt *Head, char RegNum[]);	//Função que mostra os dados de um aluno em específico
stdnt *RemoveStudent(stdnt *Head, char RegNum[]);	//Função que remove um aluno
stdnt *ShowStudentInfo(stdnt *Head);	//Função que recolhe o nome de um aluno e mostra seus dados
stdnt *EraseStudentInfo(stdnt *Head);	//Função que recolhe o nome de um aluno e remove seus dados
stdnt *PrintAll(stdnt *Head);	//Função que mostra os dados de todos os alunos
stdnt *PutTestGrade(stdnt *Head, char RegNum[], int Test, float Grade);	//Função que adiciona a nota de uma prova
stdnt *SetStdtTestGrade(stdnt *Head);	//Função que recolhe o nome de um aluno e insere a nota de uma prova
stdnt *PutProjGrade(stdnt *Head, char RegNum[], int Proj, float Grade, int Position, int NumberofMembers);	//Função que adiciona a nota de um trabalho
stdnt *SetStdtProjGrade(stdnt *Head);	//Função que recolhe o nome de um aluno e insere a nota de um trabalho
stdnt *ShowTest(stdnt *Head, int Test);	//Função que mostra os dados de uma prova em específico
stdnt *ShowProj(stdnt *Head, int Proj);	//Função que mostra os dados de um trabalho em específico
stdnt *EraseTest(stdnt *Head, int Test);	//Função que recolhe o nome de um aluno e remove seus dados
stdnt *EraseProj(stdnt *Head, int Proj);	//Função que recolhe o nome de um aluno e remove seus dados
stdnt *Menu(stdnt *Head); 	//Função que exibe as opções do menu e as executam

#endif
