#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


struct node         //STRUCTURE DEFINITION 
{

	int key[3];
	struct node *child[4];
	bool leaf;
	int count;
}*root=NULL;

void insert1(struct node *x, int key);

//----------------------------------------------------------------------------

struct node* create()   //CREATION OF AN EMPTY NODE
{ 
	int i;
	struct node* new=(struct node*)malloc(sizeof(struct node));
	new->leaf=true;
	new->count=0;
	for(i=0;i<3;i++)
		new->key[i]=-1;

	for(i=0;i<4;i++)
		new->child[i]=NULL;
	return new;
}

//---------------------------------------------------------------------------
struct node* split(struct node* x,int i, struct node* y)           
{
	int j;
	struct node* z=create();

	z->leaf=y->leaf;
	z->count=1;

	for(j=0;j<=z->count;j++)
	{
		z->key[j]=y->key[j+2];
		//		z->count++;
	}
	if(y->leaf==false)
	{
		for(j=0;j<4;j++)
			z->child[j]=y->child[j+2];
	}

	y->count=1;

	for(j=x->count;j>=i+1;j--)
		x->child[j+1]=x->child[j];

	x->child[i+1]=z;

	for(j=x->count;j>=i;j--)
		x->key[j+1]=x->key[j];
	x->key[i]=y->key[1];
	x->count++;
	return x;
}
//---------------------------------------------------------------

void insert(int key)
{
	int i;
	struct node* r=root;

	if(r==NULL)
	{
		root=create();
		r=root;
	}
	if(r->count>2)
	{
		struct node* s=create();
		root=s;
		s->leaf=false;
		s->count=0;
		s->child[0]=r;
		s=split(s,0,r);
		root=s;
		insert1(s,key);
	}
	else
	{
		insert1(r,key);
	}
}

//----------------------------------------------------

void insert1(struct node* x,int key)
{
	int i=x->count;

	if(x->leaf==true)
	{
		while(i>=1 && key< x->key[i-1])
		{
			x->key[i]=x->key[i-1];
			i=i-1;
		}
		x->key[i]=key;
		x->count++;
	}
	else
	{
		while(i>=1 && key < x->key[i-1])
		{
			i=i-1;
		}
	//	i=i+1;

		if(x->child[i]->count>2)
		{
			x=split(x,i,x->child[i]);
			if(key > x->key[i])
				i++;
		}
		insert1(x->child[i],key);
	}
}

//------------------------------------------------------------



void traversal(struct node* t)
{
	int i;
	for(i=0;i<t->count;i++)
	{
		if(t->leaf==false)
		{
			traversal(t->child[i]);
		}	
		if(t->key[i]>=0)
			printf("\n%d\t",t->key[i]);
	}
	if(t->leaf ==false)
	{
		traversal(t->child[i]);
	}

}

//---------------------------------------------------------
int main()
{
	int key,i,n;
	FILE *pipe;
	printf("Enter the no of elements\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		key=rand()%5000;
//		printf("Enter the keys\n");
//		scanf("%d",&key);
		insert(key);
	}
	printf("Inserted successfully--------------------\n");
	traversal(root);
	return 0;
}
