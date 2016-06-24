#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int pos,n,h;//Global declaration

//-----------------------------------------------------------------------
struct node
{
	int key[20];
	struct node *child[21],*parent;
	bool leaf;
	int count;
}*root=NULL;

//---------------------------------------------------------------
typedef struct node *ptr;
ptr create();
void parentinsert(ptr l,int k,ptr l1);
void traversal(ptr);
int verifybplus(ptr);
//------------------------------------------------------------------

//A function to search the position and node at which an element has to be inserted

ptr find(int v)
{
	ptr c=root;
	int i=0;
	while(c->leaf ==false)
	{
		for(i=0;i < c->count;i++)
		{
			if(v <= c->key[i])
				break;
		}
		c=c->child[i];
	}

	if(c->leaf ==true)
	{
		for(i=0;i< c->count;i++)
		{
			if(v < c->key[i])
				break;
		}
	}
	pos=i;
	return c;
}
//---------------------------------------------------------------------

//Function to insert an element at the leaf node 
ptr leafinsert(ptr x, int k)
{	int i;
	for(i=x->count-1; i>=pos;i--)
	{	
		x->key[i+1]=x->key[i];
	}
	x->key[pos]=k;
	x->count++;			
	return x;
}
//----------------------------------------------------------------------------------

//	Function to decide where an element must be inserted(i.e. At which node and at 
//what position and calls leafinser() and parentinsert() recursively

void insert(int k)
{
	int i;
	if(!root)
	{
		root=create();
		root->key[0]=k;
		root->count++;
	}
	else
	{
		ptr t=root;
		ptr l=find(k);

		if(l->count < n)
		{
			l=leafinsert(l,k);
			
		}
		else
		{
			ptr l1=create();
			l=leafinsert(l,k);
			for(i=0;i <= n/2;i++)
			{
				l1->key[i]=l->key[i+((n+1)/2)];
				l->key[i+((n+1)/2)]=-1;
				l->count--;
				l1->count++;
				/*l1->child[i]=l->child[i+(n/2)];
				  l->child->[i+(n/2)]=NULL;*/
			}
			/*l1->child[i]=l->child[i+(n/2)];
			  l->child->[i+(n/2)]=NULL;*/
			i=l1->key[0];
			parentinsert(l,i,l1);
		}
	}
}
//------------------------------------------------------------------------------------

//	Function to insert an element at leaf node, and if the node is full, it calls split function which
// splits a perticular node and assigns values

void parentinsert(ptr l,int k,ptr l1)
{
	int j,FLAG=1,i,s;
	if(root->count==l->count)
	{	for(j=0;j < root->count; j++)
		{
			if(l->key[j] != root->key[j])
			{
				FLAG=0;
				break;
			}
		}
	}
	else if(root->count!=l->count)
		FLAG=0;
	if(FLAG && root==l )
	{
		ptr ch=create();
		ch->child[0]=l;
		ch->child[1]=l1;
		l->parent=ch;
		l1->parent=ch;
		ch->key[0]=k;
		ch->leaf=false;
		ch->count++;
		h++;
		root=ch;
	}
	else
	{
		ptr p=l->parent;
		if(p->count < n)
		{
			for(j=0;j<p->count;j++)
			{
				if(k<p->key[j])
					break;
			}
			for(i=p->count;i>j;i--)
			{
				p->key[i]=p->key[i-1];
				p->child[i+1]=p->child[i];
			}
			p->key[j]=k;
			p->child[i+1]=l1;
			p->child[i]=l;	
			p->count++;
			l1->parent=p;
			p->leaf=false;
		}
		else if(p->count==n)
		{
			ptr t=create();
			ptr p1=create();
			for(j=0;j<p->count;j++)
			{
				t->key[j]=p->key[j];
				t->count++;
				t->child[j]=p->child[j];
			}
			t->child[j]=p->child[j];
			
			for(j=0;j<t->count;j++)
                        {
                                if(k<t->key[j])
                                        break;
                        }
			      for(i=t->count;i>j;i--)
                        {
                                t->key[i]=t->key[i-1];
                                t->child[i+1]=t->child[i];
                        }
                        t->key[j]=k;
                      t->count++;
			t->child[j+1]=l1;
			t->child[j]=l;
			for(i=(n+1)/2; i<=n;i++)
			{
				p->child[i+1]=NULL;
				p->key[i]=-1;
				p->count--;
			}
			p->count++;
			s=t->key[(n+1)/2];
			for(i=((n+1)/2+1);i<t->count;i++)
			{
				p1->key[i-((n+1)/2+1)]=t->key[i];
				p1->count++;
			        p1->child[i-((n+1)/2+1)]=t->child[i];
				p1->child[i-((n+1)/2+1)]->parent=p1;
			}
			p1->child[i-((n+1)/2+1)]=t->child[i];
			p1->child[i-((n+1)/2+1)]->parent=p1;
			p1->leaf=false;
			parentinsert(p,s,p1);
		}

		

		
	}
	
}
//---------------------------------------------------------------------------------------------

//	A function to create a node which assigns required memory for the node and releases the extra memory, if any
//key values are initialised to -1 and child nodes are initialised to NULL
ptr create()
{
	int i;
	ptr new=(ptr)malloc(sizeof(struct node));
	for(i=0; i<=n; i++)
	{
		new->key[i]=-1;
		new->child[i]=NULL;
	}
	new->child[i+1]=NULL;
	for(;i<21;i++)
	{
		//delete(new->key[i]);
		free(new->child[i]);
	}
	free(new->child[i]);
	new->count=0;
		
	new->parent=NULL;
	new->leaf=true;
}
//-------------------------------------------------------------------------------------------------

//The main driver function
//calls the insert function for each input and passes the root 
int main()
{
	int i,total,key;
//	printf("\nENTER THE MAX NO OF KEYS IN THE NODE:\t");
	scanf("%d",&n);
//	printf("ENTER TOTAL NUMBER OF ELEMENTS:\t");
	scanf("%d",&total);
	for(i=0; i<total; i++)
	{
//		printf("Enter the key\n");
		scanf("%d",&key);
//		key=rand()%2000;
		insert(key);
	}
//	printf("\nINSERTED SUCCESSFULLY  !!!\n");
	if(verifybplus(root))
	{
//		printf("\nTHIS IS A CORRECT B+ TREE\n");
		traversal(root);
	}
	else
//		printf("\n\"INCORRECT\" B+ TREE\n");
	return 0;
}
//-----------------------------------------------------------------------------------------------------

// A vcerification code for the B+ tree.
//compares the verified height of the tree with the constructed tree.
int verifybplus(ptr root)
{	int i,c=0;
	if(root)
	{
		for(i=0;i<=root->count;i++)
		{
			while(root->leaf==false)
			{	
				root=root->child[i];
				c++;
				verifybplus(root);
			}
			if(c!=h)
				return -1;
			else if(c==h)
				return 1;
		}
	}
}
//------------------------------------------------------------------------------------------------------

//A traversal function for B+ tree
void traversal(struct node* t)
{
	int i,j;
	for(i=0;i<t->count;i++)
	{
		if(t->leaf==false)
		{
			traversal(t->child[i]);
	//		printf("\n");
		}
		else if(t->leaf==true)
		{
			if(t->key[i]>=0)
				printf("\n%d",t->key[i]);
		}
		
	}
//	printf("\n");
	if(t->leaf ==false)
	{
		traversal(t->child[i]);	
	}

}




