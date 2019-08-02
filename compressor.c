#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

void zip(Table * table, FILE ** in, FILE ** out)
{
	char c;
	unsigned long data = 0;
	int size = 0;
	while((c=fgetc(*in))!=EOF)
    {
    	Table *t = find(c, table);
    	while((t->size + size) > 32)
    	{
    		c = data >> (size-8);
    		fwrite(&c, sizeof(char), 1, *out);
    		size -= 8 ;
    	}
    	data <<= t->size;
    	data |= t->bits;
    	size += t->size;
    }
    while(size>0)
    {
    	if(size>=8)
    	{
    		c = data >> (size-8);
    	}
    	else
    	{
    		 c = data << (8-size);
    	}
    	fwrite(&c, sizeof(char), 1, *out);
      	size -= 8;
    }
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

void unzip(FILE ** in, FILE ** out)
{
	char s;
	unsigned long len;
	fread(&s, 1, 1, *in);
	fread(&len, sizeof(unsigned long), 1, *in);
	printf("descomprimiendo...\n");
	if(s>0)
	{
		char character;
		unsigned char size;
		unsigned long bits;
		Node * letters = NULL;
		while(s--)
		{
			fread(&character, 1, 1, *in);
			fread(&size, 1, 1, *in);
			fread(&bits, sizeof(unsigned long), 1, *in);
			bitTree(&letters, character, size, bits);
		}
		bits = readWord(in);
		printOut(letters);
		printf("\n");
		printBinary(bits,0);
		size = 8;
		printf("\n");
		while(len-->0)
		{
			decode(letters,&size,&bits,in,out);
		}
	}
}


int main(int argc, char const *argv[])
{
	FILE * fileIn, *fileOut;
    fileIn = fopen("input.txt", "r");
    fileOut = fopen("output.txt", "wb");
    char c;
    Node *letters = buildTree(&fileIn);
    printOut(letters);
    Table * table = buildTable(letters);
    printTable(table);
    writeTable(&fileOut, table, letters->frecuency);
    fileIn = fopen("input.txt", "r");
    zip(table, &fileIn, &fileOut);
    fclose(fileIn);
    fclose(fileOut);
    fileIn = fopen("output.txt", "r");
    fileOut = fopen("unzip.txt", "wb");
    unzip(&fileIn,&fileOut);
	/* code */
	return 0;
}