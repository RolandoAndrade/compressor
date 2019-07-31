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
    printf("F1\n");
    while((c=fgetc(fileIn))!=EOF)
    {
    	add(&letters, c);
    }
    printf("F2\n");
    sort(&letters);
    printf("F3\n");
    letters = huffmanTree(letters);
    printf("F4\n");
    print(letters);
	printf("Chaito\n");
	/* code */
	return 0;
}