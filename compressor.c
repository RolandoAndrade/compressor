#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

int main(int argc, char const *argv[])
{
	FILE * fileIn, *fileOut;
    fileIn = fopen("input.txt", "r");
    char c;
    Node *letters = NULL;
    int i = 0;
    while((c=fgetc(fileIn))!=EOF)
    {
    	printf("%c", c);
    	add(&letters, c);
    }

    while(letters)
    {
    	printf("%c ", letters->character);
    	letters=letters->next;
    }
	printf("Hola\n");
	printf("Chao\n");
	/* code */
	return 0;
}