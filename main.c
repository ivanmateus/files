#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "files.h"
#include "student.h"

int main(){

	stdnt *Head = NULL;

	Head = GetFromFile(Head);
	Head = Menu(Head);
	return 0;
}
