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
	unsigned short size;
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

Table * createRecord(char character, int size, int bits)
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

void insertRecord(Table ** table, char character, int size, int bits)
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

void createTable(Node * tree, Table ** table, int size, int bits)
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

void printTable(Table *table)
{
	while(table->next)
	{
		printf("%c->%i->%li\n", table->character, table->size, table->bits);
		table = table->next;
	}
}