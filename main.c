#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 100
#define NUMBEROFTESTS 4
#define NUMBEROFPROJS 4

FILE *Students;

struct student_type{
	char Name[MAXCHAR];
	char RegNum[MAXCHAR];
	float TestGrade[NUMBEROFTESTS];
	float ProjGrade[NUMBEROFPROJS];
	int PositInGroup[NUMBEROFPROJS];
	int NofMembers[NUMBEROFPROJS];
	struct student_type *Next;
};
typedef struct student_type stdnt;

stdnt *InitStudent(stdnt *Student){

	int i = 0;

	while(i < MAXCHAR){
		Student->Name[i] = '0';
		Student->RegNum[i] = '0';
		if(i < NUMBEROFTESTS){
			Student->TestGrade[i] = 0.0;
		}
		if(i < NUMBEROFPROJS){
			Student->ProjGrade[i] = 0.0;
			Student->PositInGroup[i] = 0;
			Student->NofMembers[i] = 0;
		}
		++i;
	}
	Student->Next = NULL;

	return Student;
}

stdnt *Insert(stdnt *Head, stdnt *NewStudent){

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

stdnt *IncludeStudent(stdnt *Head){

	stdnt *NewStudent = malloc(sizeof(stdnt));
	if(NewStudent == NULL){
		printf("Memory allocation error.\n");
		return Head;
	}
	NewStudent = InitStudent(NewStudent);

	printf("Type in his/her full name: ");
	fgets(NewStudent->Name, MAXCHAR, stdin);
	printf("Type in his/her registration number: ");
	fgets(NewStudent->RegNum, MAXCHAR, stdin);

	Head = Insert(Head, NewStudent);

	return Head;
}

stdnt *PrintStudent(stdnt *Head, char Name[]){

	if(Head == NULL){
		printf("Student not found.\n");
		return Head;
	}
	if(strcmp(Head->Name, Name) == 0){
		printf("Student: \n");
		fputs(Head->Name, stdout);
		printf("Reg. #: \n");
		fputs(Head->RegNum, stdout);
		return Head;
	}

	Head->Next = PrintStudent(Head->Next, Name);
	return Head;
}

stdnt *RemoveStudent(stdnt *Head, char Name[]){

	stdnt *Aux = NULL;

	if(Head == NULL){
		printf("Student not found.\n");
		return Head;
	}

	if(strcmp(Head->Name, Name) == 0){
		Aux = Head->Next;
		free(Head);
		return Aux;
	}

	Head->Next = RemoveStudent(Head->Next, Name);
	return Head;
}

stdnt *ShowStudentInfo(stdnt *Head){

	char Name[MAXCHAR];

	printf("Type in student's full name: ");
	fgets(Name, MAXCHAR, stdin);
	Head = PrintStudent(Head, Name);
	return Head;
}

stdnt *EraseStudentInfo(stdnt *Head){

	char Name[MAXCHAR];

	printf("Type in student's full name: ");
	fgets(Name, MAXCHAR, stdin);
	Head = RemoveStudent(Head, Name);
	return Head;
}

stdnt *PrintAll(stdnt *Head){

	if(Head == NULL){
		return Head;
	}
	printf("Student: \n");
	fputs(Head->Name, stdout);
	printf("Reg. #: \n");
	fputs(Head->RegNum, stdout);

	Head->Next = PrintAll(Head->Next);
	return Head;
}

int main(){

	stdnt *Head = NULL;
	Head = IncludeStudent(Head);
	Head = IncludeStudent(Head);
	Head = IncludeStudent(Head);
	Head = PrintAll(Head);
	Head = EraseStudentInfo(Head);
	Head = PrintAll(Head);

	return 0;
}
