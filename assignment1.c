#include<stdio.h>
#include<stdlib.h>

//==============================================================================


struct node
{
	int start;
	unsigned int a[4];
	struct node* link;
}*head1=NULL,*head2=NULL;
//-------------------------------------------------------------------------------

void display(unsigned int a[],int start);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~INSERT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

struct node* insert(struct node* head,int prodno)
{
	int nodeno,bit,part,x;

	nodeno=prodno/128;
	x=prodno-(nodeno*128);
	bit=x%32;
	part=x/32;

	struct node* new=(struct node*)malloc(sizeof(struct node));

	if(head==NULL)
	{

		new->start=nodeno;
		new->link=NULL;

		new->a[part]=new->a[part] | (1<<(bit));

		head=new;

		return head;
	}

	else
	{
		struct node* temp=head;

z:if(temp->start==nodeno)
  {
	  temp->a[part]=temp->a[part] | (1<<bit);
	  return head;
  }
  while(temp->link!=NULL)
  {
	  temp=temp->link;
	  goto z;
  }

  new->start=nodeno;
  new->link=NULL;

  new->a[part]=new->a[part] | (1<<bit);

  temp->link=new;
  return(head);
	}
}
//-----------------------------DISPLAY-------------------------------------------------
void disp(struct node* z)
{       struct node* tempa=z;
	for(;tempa;tempa=tempa->link)
	{
		display(tempa->a,tempa->start);
	}
}

void display(unsigned int a[],int start)
{       
	unsigned int arr[4]={0,0,0,0};
	int k=0,i=0,p;
	{       
		for(i=0;i<4;i++)
		{      
			arr[i]=a[i];
			k=0;
			while(arr[i]>0)
			{       p=arr[i]%2;
				if(p==1)
					printf("%u\t", (start*128+(i*32)+(k)));
				k++;
				arr[i]=arr[i]>>1;
			}
		}
	}
}
//``````````````````````````````````UNION````````````````````````````````````````````````
void unions(struct node* x, struct node* y)
{	
	int i,start,j,k;
	unsigned int arr[4]={0,0,0,0};
	struct node *root,*head; 
	struct node* tempa,*tempb;
	for(tempa=x; tempa; tempa=tempa->link)
	{
		for(tempb=y; tempb; tempb=tempb->link)
		{	
			if(tempa->start==tempb->start)
			{	
				for(i=0; i<=3; i++)
				{
					arr[i]=tempa->a[i]|tempb->a[i];
				}
				start=tempa->start;
				display(arr,start);
				break;
			}
		}
	}

   for(tempa=x;tempa;tempa=tempa->link)
        {
		j=1;
                for(tempb=y;tempb;tempb=tempb->link)
                {
                        if(tempa->start == tempb->start)
                        {
                            j=0;
			break;
                        }
                }
		if(j)
		display(tempa->a,tempa->start);
        }


	for(tempb=y;tempb;tempb=tempb->link)
	{      
		k=1;
		for(tempa=x;tempa;tempa=tempa->link)
		{       
			if(tempa->start==tempb->start)
			{    
				k=0;
				break;
			}
		}
		if(k)
		display(tempb->a,tempb->start);
	}
}

void intersection(struct node* x, struct node* y)
{
        int i,start;
        unsigned int arr[4]={0,0,0,0};
        struct node *root,*head;
        struct node* tempa,*tempb;
        for(tempa=x; tempa; tempa=tempa->link)
        {
                for(tempb=y; tempb; tempb=tempb->link)
                {
                        if(tempa->start==tempb->start)
                        {
                                for(i=0; i<=3; i++)
                                {
                                        arr[i]=tempa->a[i] & tempb->a[i];
                                }
                                start=tempa->start;
                                display(arr,start);
                                break;
                        }
                }
        }

}

void difference1(struct node *x, struct node *y)
{
  int i,start,j,k;
        unsigned int arr[4]={0,0,0,0};
        struct node *root,*head;
        struct node* tempa,*tempb;

 for(tempa=x;tempa;tempa=tempa->link)
        {
                j=1;
                for(tempb=y;tempb;tempb=tempb->link)
                {
                        if(tempa->start == tempb->start)
                        {
                            j=0;
                        break;
                        }
                }
                if(j)
                display(tempa->a,tempa->start);
        }

}

void difference2(struct node *x, struct node *y)
{
  int i,start,j,k;
        unsigned int arr[4]={0,0,0,0};
        struct node *root,*head;
        struct node* tempa,*tempb;
    for(tempb=y;tempb;tempb=tempb->link)
        {
                k=1;
                for(tempa=x;tempa;tempa=tempa->link)
                {
                        if(tempa->start==tempb->start)
                        {
                                k=0;
                                break;
                        }
                }
                if(k)
                display(tempb->a,tempb->start);
        }
}

//=================================MAIN==============================================
int main()
{
	int prod,ch,FLAG;

	while(FLAG)
	{
		printf("\nEnter your choice:\n1.Insert for CUSTOMER-1\n2.Insert for CUSTOMER-2\n3.DISPLAY\n4.UNION\n5.INTERSECTION\n");
		printf("6.DIFFERENCE(1-2)\n7.DIFFERENCE(2-1)\n8.EXIT\n");
		scanf("%d",&ch);

		switch(ch)
		{

			case 1: printf("\nEnter product no of CUST-1:\n");
				scanf("%d",&prod);
				head1=insert(head1,prod);
				printf("\n---------------------INSERTED SUCCESSFULLY---------------------------\n");
				break;
			case 2: printf("\nEnter product no of CUST-2:\n");
				scanf("%d",&prod);
				head2=insert(head2,prod);
				printf("\n---------------------INSERTED SUCCESSFULLY---------------------------\n");
				break;
			case 3: printf("\nProducts of CUST-1:\n");
				disp(head1);
				printf("\nProducts of CUST-2:\n");
				disp(head2);
				break;
			case 4: unions(head1,head2);
				break;
			case 5: intersection(head1,head2);
                                break;
			case 6:difference1(head1,head2);
				break;
			case 7:difference2(head1,head2);
                                break;
			case 8:FLAG=0;
				break;
			default:printf("\nEnter correct choice....!!\n");
				break;

		}
	}
	return 0;
}
