#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

void zip(Table * table, FILE ** in, FILE ** out)
{
	char c;
	unsigned long data;
	short size = 0;
	while((c=fgetc(*in))!=EOF)
    {
    	Table *t = find(c, table);
    	while((size + table->size) > 32)
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

void unzip()
{
	
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
    writeTable(&fileOut, table);
    fileIn = fopen("input.txt", "r");
    zip(table, &fileIn, &fileOut);


	/* code */
	return 0;
}