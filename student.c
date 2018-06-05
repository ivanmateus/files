#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "files.h"
#include "student.h"

stdnt *InitStudent(stdnt *Student){	//Função que inicializa um nó

	int i = 0;

	Student = (stdnt *)malloc(sizeof(stdnt));
	if(Student == NULL){
		printf("Memory allocation error.\n");
		return Student;
	}

	while(i < MAXCHAR){
		Student->Name[i] = 'x';
		Student->RegNum[i] = 'x';
		if(i < MAXTESTS){
			Student->TestGrade[i] = -1.0;
		}
		if(i < MAXPROJS){
			Student->ProjGrade[i] = -1.0;
			Student->PositInGroup[i] = -1;
			Student->NofMembers[i] = -1;
		}
		++i;
	}
	Student->Next = NULL;

	return Student;
}

stdnt *Insert(stdnt *Head, stdnt *NewStudent){	//Função que insere um novo aluno em ordem alfabética

	stdnt *Aux = NULL;

	if(Head == NULL){
		return NewStudent;
	}
	Aux = Head;
	if(strcmp(Aux->Name, NewStudent->Name) < 0){
		Aux->Next = Insert(Aux->Next, NewStudent);
		return Aux;
	}else{
		Head = NewStudent;
		NewStudent->Next = Aux;
		return Head;
	}

	Head->Next = Insert(Head->Next, NewStudent);
	return Head;
}

stdnt *IncludeStudent(stdnt *Head){	//Função que recolhe o nome e nº de matrícula e insere um novo aluno

	stdnt *NewStudent = NULL;
	NewStudent = InitStudent(NewStudent);

	printf("Type in his/her full name: ");
	fgets(NewStudent->Name, MAXCHAR, stdin);
	printf("Type in his/her registration number: ");
	fgets(NewStudent->RegNum, MAXCHAR, stdin);

	Head = Insert(Head, NewStudent);

	return Head;
}

float IndividualGrade(float Grade, int Position, int NumberofMembers){	//Calcula o valor da nota individual do trabalho

	float Indiv = Grade*(1 + (0.05*(NumberofMembers - 1)))*(pow(0.9, Position));

	return Indiv;
}

stdnt *PrintStudent(stdnt *Head, char RegNum[]){	//Função que mostra os dados de um aluno em específico

	int i = 0;

	if(Head == NULL){
		printf("Student not found!\n");
		return Head;
	}
	if(strcmp(Head->RegNum, RegNum) == 0){
		printf("Student: \n");
		fputs(Head->Name, stdout);
		printf("Reg. #: \n");
		fputs(Head->RegNum, stdout);
		printf("\n");
		while(i < MAXTESTS){
			if(Head->TestGrade[i] != -1.0){
				printf("Test %d:\n", i + 1);
				printf("Test grade: %.2f\n", Head->TestGrade[i]);
			}
			++i;
		}
		i = 0;
		printf("\n");
		while(i < MAXPROJS){
			if(Head->ProjGrade[i] != -1.0){
				printf("Project %d:\n", i + 1);
				printf("Project grade: %.2f\n", Head->ProjGrade[i]);
				printf("Position in the group: %d\n", Head->PositInGroup[i]);
				printf("Number of members in the group: %d\n", Head->NofMembers[i]);
				printf("Individual grade: %.2f\n", IndividualGrade(Head->ProjGrade[i], Head->PositInGroup[i], Head->NofMembers[i]));
			}
			++i;
		}
		return Head;
	}

	Head->Next = PrintStudent(Head->Next, RegNum);
	return Head;
}

stdnt *RemoveStudent(stdnt *Head, char RegNum[]){	//Função que remove um aluno

	stdnt *Aux = NULL;

	if(Head == NULL){
		printf("Student not found!\n");
		return Head;
	}

	if(strcmp(Head->RegNum, RegNum) == 0){
		Aux = Head->Next;
		free(Head);
		return Aux;
	}

	Head->Next = RemoveStudent(Head->Next, RegNum);
	return Head;
}

stdnt *ShowStudentInfo(stdnt *Head){	//Função que recolhe o nome de um aluno e mostra seus dados

	char RegNum[MAXCHAR];

	printf("Type in student's registration number: ");
	fgets(RegNum, MAXCHAR, stdin);
	Head = PrintStudent(Head, RegNum);
	return Head;
}

stdnt *EraseStudentInfo(stdnt *Head){	//Função que recolhe o nome de um aluno e remove seus dados

	char RegNum[MAXCHAR];

	printf("Type in student's registration number: ");
	fgets(RegNum, MAXCHAR, stdin);
	Head = RemoveStudent(Head, RegNum);
	return Head;
}

stdnt *PrintAll(stdnt *Head){	//Função que mostra os dados de todos os alunos

	if(Head == NULL){
		return Head;
	}
	Head = PrintStudent(Head, Head->RegNum);
	printf("\n");
	Head->Next = PrintAll(Head->Next);
	return Head;
}

stdnt *PutTestGrade(stdnt *Head, char RegNum[], int Test, float Grade){	//Função que adiciona a nota de uma prova

	if(Head == NULL){
		printf("Student not found!\n");
		return Head;
	}
	if(strcmp(Head->RegNum, RegNum) == 0){
		Head->TestGrade[Test] = Grade;
		return Head;
	}

	Head->Next = PutTestGrade(Head->Next, RegNum, Test, Grade);
	return Head;

}

stdnt *SetStdtTestGrade(stdnt *Head){	//Função que recolhe o nome de um aluno e insere a nota de uma prova

	char RegNum[MAXCHAR];
	int Test;
	float Grade;

	printf("Type in student's registration number: ");
	fgets(RegNum, MAXCHAR, stdin);
	printf("Type in which test you want to add the grade (e.g 1, 2): ");
	scanf(" %d", &Test);
	clean_stdin();
	printf("Type in the grade (e.g 9.5, 8.0): ");
	scanf(" %f", &Grade);
	clean_stdin();
	Head = PutTestGrade(Head, RegNum, Test - 1, Grade);
	return Head;
}

stdnt *PutProjGrade(stdnt *Head, char RegNum[], int Proj, float Grade, int Position, int NumberofMembers){	//Função que adiciona a nota de um trabalho

	if(Head == NULL){
		printf("Student not found!\n");
		return Head;
	}
	if(strcmp(Head->RegNum, RegNum) == 0){
		Head->ProjGrade[Proj] = Grade;
		Head->PositInGroup[Proj] = Position;
		Head->NofMembers[Proj] = NumberofMembers;
		return Head;
	}

	Head->Next = PutProjGrade(Head->Next, RegNum, Proj, Grade, Position, NumberofMembers);
	return Head;

}

stdnt *SetStdtProjGrade(stdnt *Head){	//Função que recolhe o nome de um aluno e insere a nota de um trabalho

	char RegNum[MAXCHAR];
	int Proj;
	float Grade;
	int Posit;
	int NumberofMembers;

	printf("Type in student's registration number: ");
	fgets(RegNum, MAXCHAR, stdin);
	printf("Type in which project you want to add the grade (e.g 1, 2): ");
	scanf(" %d", &Proj);
	clean_stdin();
	printf("Type in the grade (e.g 9.5, 8.0): ");
	scanf(" %f", &Grade);
	clean_stdin();
	printf("Type in the position in the group: ");
	scanf(" %d", &Posit);
	clean_stdin();
	printf("Type in the number of members in the group: ");
	scanf(" %d", &NumberofMembers);
	clean_stdin();
	Head = PutProjGrade(Head, RegNum, Proj - 1, Grade, Posit, NumberofMembers);
	return Head;
}

stdnt *Menu(stdnt *Head){	//Função que exibe as opções do menu e as executam

	int Exit = 1;
	int Option = 0;

	while(Exit){

		Option = 0;

		printf("Menu\n\n");
		printf("Choose an option: \n");
		printf("1. Register student;\n");
		printf("2. Add student's test grade;\n");
		printf("3. Add student's project grade;\n");
		printf("4. Remove a register;\n");
		printf("5. Consult student's info;\n");
		printf("6. Consult all students;\n");
		printf("7. Save the data in a file.\n\n");
		printf("Type in the option: ");

		while(Option < 1 || Option > 7){
			scanf("%d", &Option);
			clean_stdin();
			if(Option < 1 || Option > 7){
				printf("Invalid option, type in again: ");
			}
		}
		printf("\n");

		switch(Option) {
			case 1:
				while(Exit){
					Head = IncludeStudent(Head);
					printf("\nIf you'd like to register another student, enter 1; else, 0: ");
					scanf("%d", &Exit);
					printf("\n");
					clean_stdin();
				}
				break;
			case 2:
				while(Exit){
					Head = SetStdtTestGrade(Head);
					printf("\nIf you'd like to add another grade, enter 1; else, 0: ");
					scanf("%d", &Exit);
					printf("\n");
					clean_stdin();
				}
				break;
			case 3:
				while(Exit){
					Head = SetStdtProjGrade(Head);
					printf("\nIf you'd like to add another grade, enter 1; else, 0: ");
					scanf("%d", &Exit);
					printf("\n");
					clean_stdin();
				}
				break;
			case 4:
				while(Exit){
					Head = EraseStudentInfo(Head);
					printf("\nIf you'd like to remove another register, enter 1; else, 0: ");
					scanf("%d", &Exit);
					printf("\n");
					clean_stdin();
				}
				break;
			case 5:
				while(Exit){
					Head = ShowStudentInfo(Head);
					printf("\nIf you'd like to consult another student, enter 1; else, 0: ");
					scanf("%d", &Exit);
					printf("\n");
					clean_stdin();
				}
				break;
			case 6:
				Head = PrintAll(Head);
				break;
			case 7:
				Head = SaveInFile(Head);
				break;
		}

		printf("If you'd like to choose an option in the menu again, enter 1; else, 0: ");
		scanf("%d", &Exit);
		printf("\n");
		clean_stdin();
	}

	Head = SaveInFile(Head);
	Head = Destroy(Head);

	return Head;
}
