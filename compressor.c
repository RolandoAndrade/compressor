#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"


void zip(char * inputFileName, char * outputFileName)
{
	FILE * fileIn, *fileOut;
    fileIn = fopen(inputFileName, "r");
    fileOut = fopen(outputFileName, "wb");
    Node *letters = buildTree(&fileIn);
    Table * table = buildTable(letters);
    writeTable(&fileOut, table, letters->frecuency);
    fileIn = fopen(inputFileName, "r");
    code(table, &fileIn, &fileOut);
    fclose(fileIn);
    fclose(fileOut);
}


unsigned long readWord(FILE ** in)
{
	unsigned long bits = 0;
	fread(&bits, sizeof(unsigned long), 1, *in);
	unsigned long maskA = bits&0x000000FFUL;
	unsigned long maskB = bits&0x0000FF00UL;
	unsigned long maskC = bits&0x00FF0000UL;
	unsigned long maskD = bits&0xFF000000UL;
	maskA<<=24;
	maskB<<=8;
	maskC>>=8;
	maskD>>=24;
	return (maskA)+(maskB)+(maskC)+maskD;
}

void unzip(char * inputFileName, char * outputFileName)
{
	FILE * fileIn, *fileOut;
	fileIn = fopen(inputFileName, "r");
    fileOut = fopen(outputFileName, "wb");
	char s;
	unsigned long len;
	fread(&s, 1, 1, fileIn);
	fread(&len, sizeof(unsigned long), 1, fileIn);
	if(s>0)
	{
		char character;
		unsigned char size;
		unsigned long bits;
		Node * letters = NULL;
		while(s--)
		{
			fread(&character, 1, 1, fileIn);
			fread(&size, 1, 1, fileIn);
			fread(&bits, sizeof(unsigned long), 1, fileIn);
			bitTree(&letters, character, size, bits);
		}
		bits = readWord(&fileIn);
		size = 8;
		while(len-->0)
		{
			decode(letters,&size,&bits,&fileIn,&fileOut);
		}
	}
	fclose(fileIn);
    fclose(fileOut);
}

char * clean(char * in)
{
	int l = strlen(in)-1;
}

int main(int argc, char const *argv[])
{
	if(argc<3)
	{
		printf("\nPor favor introduzca alguno de los siguientes parametros\n");
		printf("\tzip <file>: comprime el archivo\n");
		printf("\tunzip <file>: descomprime el archivo\n\n");
	}
	else
	{
		char * in = argv[2];
		char* out; 
		if(!strcmp(argv[1],"zip"))
		{
			printf("Comprimiendo...\n");
			out = malloc(strlen(in)+4);
			strcpy(out, in);
			strcat(out, ".rol"); 
			zip(in, out);
		}
		else if(!strcmp(argv[1],"unzip"))
		{
			printf("Desomprimiendo...\n");
			out = malloc(strlen(in));
			strcpy(out, in);
			unzip(in, out);
		}
	}

	return 0;
}