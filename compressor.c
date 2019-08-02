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
      	/*
      	Aenean porttitor diam ac mi congue placerat. Pellentesque habitant morbi tristique
      	01111001 1 = A 
      	001 = e
      	0100 = n
      	001 =e
      	1100 = a
      	0100 = n
      	101 = 
      	110110 = p
      	01101 = o
      	0000 = r
      	1000 = t
      	1000 = t
      	111 11000011 
      	01000010 10001011 11110011 01010111 00011101 01110101 11110101 11001101 
      	01001101 11110010 01101110 11001011 10001110 00100001 10010000 11111101 
      	01111000 = P
      	001 = e
      	0101 = l
      	0101 = l
      	001 = e
      	0100 = n
      	1000 = t
      	001 = e
      	1110 = s
      	1100110 = q
      	1001 = u 
      	001 = e
      	 = 101
      	h = 01100110
      	11 
      	00011110 11111100 01100010 01000101 11010011 01000001 11101111 11011000 
      	00001111 11101000 11111101 11010010 01101111 00010100 00101110 10001001 
      	11101010 01100010 10100001 10001001 11101010 01100010 11101011 00010100 
      	11110100 11100000 10110010 10001101 11001101 00011110 00111000 11101011 
      	00010010 00011011 01111111 01010011 10111100 00010100 01100111 00111111 
      	01011001 01010010 00011000 11110111 11100010 01000010 11100101 01001001 
      	01010101 11001011 11111010 11011000 10000000 10111100 11000000 11110100 
      	01101111 10100111 10111101 10011110 10110000 01010101 */
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
	fread(&s, 1, 1, *in);
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
		for(int i = 0;i<100;i++)
		{
			decode(letters,&size,&bits,in,out);
		}
		//121, 20, 56, 151
		//01111001 00010100 00111000 10010111        01100110
		//11110011
		//1111001000101000011100010010111
		//1111001000101000011100010010111
		//10010111 00111000 00010100 01111001
		
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
    writeTable(&fileOut, table);
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