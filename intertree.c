  #include<stdio.h>
  #include<stdlib.h>

struct node
{
	int key;
	struct node *left, *right;
};

struct node* newnode(int k)
{
	struct node* new1=(struct node*)malloc(sizeof(struct node));
	new1->key=k;
	new1->left=NULL;
	new1->right=NULL;
	return new1;
}

void inorder(struct node* z)
{
if(z)
{
inorder(z->left);
printf("%d\t",z->key);
inorder(z->right);
}
}


main()
{
	int n, x, i,j;
	printf("\n Enter no of nodes\n");
	scanf("%d", &n);
	printf("\n Enter key value for the root\n");
	scanf("%d",&x);
	struct node* root=newnode(x);

	a:while(i<n)
 { 
	printf("\nenter the key of %dth node\n",i);
	scanf("%d",&x);
	struct node* head=root;
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	temp->key=x;
	x: if(x<head->key)
	{
	 if(head->left==NULL)
	{
	   head->left=temp;
	   break;
	}
        else
	{
	  head=head->left;
	  goto x;
	}
	}

	else
	{
	if(head->right==NULL)
	{
	head->right=temp;
	break;
	}
	else
	{
	head=head->right;
	goto x;
	}
	}
}  
if(i<n)
{
i++;
goto a;
}

inorder(root);
}


