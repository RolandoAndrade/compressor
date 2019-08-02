typedef struct Node Node;
typedef struct Table Table;

struct Node
{
	char character;
	unsigned long frecuency;
	struct Node *left, *right, *next;
};

struct Table
{
	char character;
	unsigned long bits;
	unsigned char size;
	struct Table *next; 
};

void swap(unsigned long *a, unsigned long *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

Node * createNode(char character)
{
	Node * p = (Node*)malloc(sizeof(Node));
	p->character = character;
	p->frecuency = 1;
	p->left = NULL;
	p->right = NULL;
	p->next = NULL;
	return p;
}

Table * createRecord(char character, char size, unsigned long bits)
{
	Table * p = (Table*)malloc(sizeof(Table));
	p->character = character;
	p->bits = bits;
	p->size = size;
	p->next = NULL;
	return p;
}

void add(Node **letters, char character)
{
	Node *p = *letters, *q;
	q = NULL;
	while(p)
	{
		q = p;
		if(p->character==character)
		{
			(p->frecuency)++;
			return;
		}
		p = p->next;
	}
	if(q)
	{
		q->next = createNode(character);
	}
	else
	{
		*letters = createNode(character); 
	}
	
}

int size(Node * letters)
{
	int i = 0;
	while(letters)
	{
		i++;
		letters=letters->next;
	}
	return i;
}

int sizeT(Table * table)
{
	int i = 0;
	while(table)
	{
		i++;
		table=table->next;
	}
	return i;
}

void sort(Node **letters)
{
	Node *p = *letters, *q, *min;
	while(p&&p->next)
	{
		q = p->next;
		min = p;
		while(q)
		{
			if(q->frecuency< min->frecuency)
			{
				min = q;
			}
			q = q->next;
		}

		swap(&(p->frecuency), &(min->frecuency));
		swap(&(p->character), &(min->character));
		p = p->next;
	}
}

void printBinary(unsigned long num, int it)
{
	if(it<32)
	{
		printBinary(num/2, it+1);
		printf("%i", num%2!=0);
	}
}

Node * insertNode(Node ** priorityQueue, Node * node)
{
	if(!(*priorityQueue))
	{
		*priorityQueue = node;
		(*priorityQueue)->next = NULL;
	}
	else
	{
		Node *p = *priorityQueue, *q;
		q = NULL;
		while(p && p->frecuency < node->frecuency)
		{
			q = p;
			p=p->next;
		}
		node->next = p;
		if(q)
		{
			q->next = node;
		}
		else
		{
			*priorityQueue = node;
		}
	}
}

Node * huffmanTree(Node * letters)
{
	while(letters&&letters->next)
	{
		Node *p = createNode('$');
		p->left = letters;
		p->right = letters->next;
		p->frecuency = p->left->frecuency + p->right->frecuency;
		letters=letters->next->next;
		insertNode(&letters,p);
	}
	return letters;
}

Node * buildTree(FILE ** file)
{
	Node * node = NULL;
	char c;
	while((c=fgetc(*file))!=EOF)
    {
    	add(&node, c);
    }
    sort(&node);
    return huffmanTree(node);
}

void printOut(Node * letters)
{
	if(letters)
	{
		if(letters->left)
		{
			printOut(letters->left);
			printOut(letters->right);
		}
		else
		{
			printf("%c/%lu; ", letters->character,letters->frecuency);
		}
	}
}

void insertRecord(Table ** table, char character, char size, unsigned long bits)
{
	Table *p = createRecord(character, size, bits);
	if(!(*table))
	{
		*table = p;
	}
	else
	{
		Table *q = *table;
		while(q->next)
		{
			q = q->next;
		}

		q->next = p;
	}
}

void createTable(Node * tree, Table ** table, char size, unsigned long bits)
{
	if(tree)
	{
		if(tree->left)
		{
			createTable(tree->left, table, size + 1, bits<<1); //X*2
		}
		if(tree->right)
		{
			createTable(tree->right, table, size + 1, bits<<1|1);//X*2+1 
		}
		if(!(tree->left) && !(tree->right))
		{
			insertRecord(table, tree->character, size, bits);
		}
	}
}

Table * buildTable(Node * tree)
{
	Table * table = NULL;
    createTable(tree, &table, 0, 0);
    return table;
}

void printTable(Table *table)
{
	while(table->next)
	{
		printf("%c = ", table->character);
		printBinary(table->bits,32-table->size);
		printf("\n");
		table = table->next;
	}
}


void writeTable(FILE ** file, Table * table)
{
	char s = sizeT(table);
	fwrite(&s, sizeof(char), 1, *file);
	while(table)
	{
		fwrite(&table->character, sizeof(char), 1, *file);
		fwrite(&table->size, sizeof(unsigned char), 1, *file);
		fwrite(&table->bits, sizeof(unsigned long), 1, *file);
		table = table->next;
	}
}

Table * find(char character, Table * table)
{
	while(table)
	{
		if(character==table->character)
		{
			return table;
		}
		table = table->next;
	}
	return NULL;
}


void bitTree(Node ** node, char character, unsigned char size, unsigned long bits)
{
	if(!size)
	{
		if(*node)
		{
			(*node)->character = character;
			(*node)->frecuency = bits;
		}
		else
		{
			*node = createNode(character);
			(*node)->frecuency = bits;
		}
	}
	else
	{
		unsigned long mask = 1 << (size-1);
		if(!(*node))
		{
			*node = createNode('$');
		}
		if(mask & bits)
		{
			if(!((*node)->right))
			{
				(*node)->right = createNode('$');
			}
			bitTree(&(*node)->right, character, size-1, bits);
		}
		else
		{
			if(!((*node)->left))
			{
				(*node)->left = createNode('$');
			}
			bitTree(&(*node)->left, character, size-1, bits);
		}
	}
}

int decode(Node * tree, char *size, unsigned long *bits, FILE ** in, FILE ** out)
{

	if(!(tree->left)&&!(tree->right))
	{
		fwrite(&tree->character, sizeof(char), 1, *out);
	}
	else
	{
		unsigned long mask = 2147483648;
		int b = (*bits)&mask;
		(*bits)<<=1;
		*size = *size -1;
		if(!(*size))
		{
			unsigned char bi;
			fread(&bi, 1, 1, *in);
			(*bits)|=bi;
			*size = 8;
		}
		if(b)
		{
			decode(tree->right, size, bits, in, out);
		}
		else
		{
			decode(tree->left, size, bits, in, out);
		}
	}
	return 0;
}