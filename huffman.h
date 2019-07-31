typedef struct Node Node;

struct Node
{
	char character;
	unsigned long frecuency;
	struct Node *left, *right, *next;
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

void add(Node **letters, char character)
{
	Node *p = *letters;
	while(p&&p->next)
	{
		if(p->character==character)
		{
			(p->frecuency)++;
			return;
		}
		p = p->next;
	}
	if(p)
	{
		if(p->character==character)
		{
			(p->frecuency)++;
		}
		else
		{
			p->next = createNode(character);
		}
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

Node * huffmanTree(Node * letters)
{

}