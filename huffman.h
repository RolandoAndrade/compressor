typedef struct Node Node;

struct Node
{
	char character;
	unsigned long frecuency;
	struct Node *left, *right, *next;
};

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

void sort(Node *letters, int size)
{
	Node *p = letters;
	while(p->next->next)
	{
		Node *q = p->next;
		Node *min = p;
		while(q->next)
		{
			if(q->frecuency<min->frecuency)
			{
				*min = *q;
			}
		}

	}
}

Node * huffmanTree(char letters[], unsigned long frecuency[])
{

}