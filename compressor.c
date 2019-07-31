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
    	add(&letters, c);
    }
    sort(&letters);
    while(letters)
    {
    	printf("%c->%lu ", letters->character, letters->frecuency);
    	letters=letters->next;
    }
	
	printf("Chaito\n");
	/* code */
	return 0;
}