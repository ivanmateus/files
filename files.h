#ifndef FILES_H_
#define FILES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "student.h"

void clean_stdin(void);		//Função que limpa stdin
stdnt *SaveInFile(stdnt *Head);		//Função que salva os dados já coletados no arquivo de texto
stdnt *Destroy(stdnt *Head); //Função que apaga toda a lista
stdnt *GetFromFile(stdnt *Head);	//Função que pega os dados do arquivo texto

#endif
