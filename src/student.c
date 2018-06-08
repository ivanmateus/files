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

	int Test;
	float Grade;
	stdnt *Aux = Head;

	printf("Type in which test you want to add(e.g 1, 2): ");
	scanf(" %d", &Test);
	clean_stdin();
	printf("\n");
	while(Aux != NULL){
		printf("Type in %s's grade (e.g 9.5, 8.0): ", Aux->Name);
		scanf(" %f", &Grade);
		clean_stdin();
		Head = PutTestGrade(Head, Aux->RegNum, Test - 1, Grade);
		printf("\n");
		Aux = Aux->Next;
	}
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

	int Proj;
	float Grade;
	int Posit;
	int NumberofMembers;
	stdnt *Aux = Head;

	printf("Type in which project you want to add the grade (e.g 1, 2): ");
	scanf(" %d", &Proj);
	clean_stdin();
	printf("\n");
	while(Aux != NULL){
		printf("Type in %s's grade (e.g 9.5, 8.0): ", Aux->Name);
		scanf(" %f", &Grade);
		clean_stdin();
		printf("\n");
		printf("Type in %s's position in the group: ", Aux->Name);
		scanf(" %d", &Posit);
		clean_stdin();
		printf("\n");
		printf("Type in the number of members in %s's group: ", Aux->Name);
		scanf(" %d", &NumberofMembers);
		clean_stdin();
		printf("\n");
		Head = PutProjGrade(Head, Aux->RegNum, Proj - 1, Grade, Posit, NumberofMembers);
		Aux = Aux->Next;
	}
	return Head;
}

stdnt *ShowTest(stdnt *Head, int Test){	//Função que mostra os dados de uma prova em específico

	if(Head == NULL){
		return Head;
	}
	printf("Student: ");
	fputs(Head->Name, stdout);
	printf("Reg. #: ");
	fputs(Head->RegNum, stdout);
	if(Head->TestGrade[Test] != -1.0){
		printf("Test grade: %.2f\n\n", Head->TestGrade[Test]);
	}else{
		printf("Grade not added yet.\n\n");
	}

	Head->Next = ShowTest(Head->Next, Test);
	return Head;
}

stdnt *ShowProj(stdnt *Head, int Proj){	//Função que mostra os dados de um trabalho em específico

	if(Head == NULL){
		return Head;
	}
	printf("Student: ");
	fputs(Head->Name, stdout);
	printf("Reg. #: ");
	fputs(Head->RegNum, stdout);
	if(Head->ProjGrade[Proj] != -1.0){
		printf("Project grade: %.2f\n", Head->ProjGrade[Proj]);
		printf("Position in the group: %d\n", Head->PositInGroup[Proj]);
		printf("Number of members in the group: %d\n", Head->NofMembers[Proj]);
		printf("Individual grade: %.2f\n\n", IndividualGrade(Head->ProjGrade[Proj], Head->PositInGroup[Proj], Head->NofMembers[Proj]));
	}else{
		printf("Grade not added yet.\n\n");
	}

	Head->Next = ShowProj(Head->Next, Proj);
	return Head;
}

stdnt *EraseTest(stdnt *Head, int Test){	//Função que recolhe o nome de um aluno e remove seus dados

	if(Head == NULL){
		return Head;
	}
	Head->TestGrade[Test] = -1.0;
	Head->Next = EraseTest(Head->Next, Test);
	return Head;
}

stdnt *EraseProj(stdnt *Head, int Proj){	//Função que recolhe o nome de um aluno e remove seus dados

	if(Head == NULL){
		return Head;
	}

	Head->ProjGrade[Proj] = -1.0;
	Head->PositInGroup[Proj] = -1;
	Head->NofMembers[Proj] = -1;
	Head->Next = EraseProj(Head->Next, Proj);
	return Head;
}

stdnt *Menu(stdnt *Head){	//Função que exibe as opções do menu e as executam

	int Exit = 1;
	int Option = 0;
	int Aux = 0;

	while(1){
		
		Exit = 1;
		Option = 0;

		printf("============================================\n");
		printf("                    Menu\n");
		printf("============================================\n\n");
		printf("Choose an option: \n");
		printf("1. Register students;\n");
		printf("2. Add/update a test;\n");
		printf("3. Consult a test;\n");
		printf("4. Remove a test;\n");
		printf("5. Add/update a project;\n");
		printf("6. Consult a project;\n");
		printf("7. Remove a project;\n");
		printf("8. Remove a student;\n");
		printf("9. Consult a student;\n");
		printf("10. Consult all students;\n");
		printf("11. Save the data in a file.\n");
		printf("0. Exit the program.\n");
		printf("Type in the option: ");
		scanf("%d", &Option);
		printf("\n\n");
		clean_stdin();

		switch(Option) {
			case 1:
				while(Exit){
					Head = IncludeStudent(Head);
					printf("Done!\n");
					printf("\nIf you'd like to register another student, enter 1; else, 0: ");
					scanf("%d", &Exit);
					printf("\n");
					clean_stdin();
				}
				break;
			case 2:
				while(Exit){
					Head = SetStdtTestGrade(Head);
					printf("Done!\n");
					printf("\nIf you'd like to add another test, enter 1; else, 0: ");
					scanf("%d", &Exit);
					printf("\n");
					clean_stdin();
				}
				break;
			case 3:
				printf("Type in the test you want to consult: ");
				scanf("%d", &Aux);
				printf("\n");
				clean_stdin();
				Head = ShowTest(Head, Aux - 1);
				printf("Done!\n");
				break;
			case 4:
				printf("Type in the test you want to erase: ");
				scanf("%d", &Aux);
				printf("\n");
				clean_stdin();
				Head = EraseTest(Head, Aux - 1);
				printf("Done!\n");
				break;
			case 5:
				while(Exit){
					Head = SetStdtProjGrade(Head);
					printf("Done!\n");
					printf("\nIf you'd like to add another test, enter 1; else, 0: ");
					scanf("%d", &Exit);
					printf("\n");
					clean_stdin();
				}
				break;
			case 6:
				printf("Type in the project you want to consult: ");
				scanf("%d", &Aux);
				printf("\n");
				clean_stdin();
				Head = ShowProj(Head, Aux - 1);
				printf("Done!\n");
				break;
			case 7:
				printf("Type in the project you want to erase: ");
				scanf("%d", &Aux);
				printf("\n");
				clean_stdin();
				Head = EraseProj(Head, Aux - 1);
				printf("Done!\n");
				break;
			case 8:
				while(Exit){
					Head = EraseStudentInfo(Head);
					printf("Done!\n");
					printf("\nIf you'd like to remove another register, enter 1; else, 0: ");
					scanf("%d", &Exit);
					printf("\n");
					clean_stdin();
				}
				break;
			case 9:
				while(Exit){
					Head = ShowStudentInfo(Head);
					printf("Done!\n");
					printf("\nIf you'd like to consult another student, enter 1; else, 0: ");
					scanf("%d", &Exit);
					printf("\n");
					clean_stdin();
				}
				break;
			case 10:
				Head = PrintAll(Head);
				printf("Done!\n");
				break;
			case 11:
				Head = SaveInFile(Head);
				printf("Done!\n");
				break;
			case 0:
				Head = SaveInFile(Head);
				Head = Destroy(Head);
				return Head;
		}
	}
}
