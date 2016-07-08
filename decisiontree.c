//Program to find the Decision Tree

#include<stdio.h>
#include<stdlib.h>
int n,y=0,no=0,def,max=0;
int new[3],atcnt;
float gin[3];
static int gName=0;
FILE *outputFile;

void run();
void run1();
void gini(float sun,float rain,float high,float norm,float str,float weak);

//tree definition
struct node
{
	int data;
	struct node *left, *right;
}*root=NULL,*dfault;

//Array of structures to input examples
struct 
{
	int outlook,humid,wind;
	int play;
}day[20];

//function to input the examples and display them
void enter()
{
	float sun=0,rain=0,high=0,norm=0,str=0,weak=0;
	int i;
	printf("Enter the data\n\nOutlook= 0-Sunny 1-Rain\n");
	printf("Humidity= 0-Normal 1-High\n Wind= 0-Weak 1-Strong\n");
	printf("Play= 1-yes 0-no\n\n");  
	for(i=0;i<n;i++)
	{
		printf("Enter %dth day's record\n",i+1);
		scanf("%d%d%d%d",&day[i].outlook, &day[i].humid, &day[i].wind, &day[i].play);
	}

	printf("\nTable is:\n");
	printf("Day  Outlook  Humidity  Wind  Play\n\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t",i+1);
		if(day[i].outlook==0) 
		{
			sun++;
			printf("Sunny\t");
		}
		else if(day[i].outlook==1) 
		{
			rain++;
			printf("Rainy\t");
		}

		if(day[i].humid==1) 
		{
			high++;
			printf("High\t");
		}
		else if(day[i].humid==0) 
		{
			norm++;
			printf("Normal\t");
		}

		if(day[i].wind==1) 
		{
			str++;
			printf("Strong\t");
		}
		else if(day[i].wind==0) 
		{
			weak++;
			printf("Weak\t");
		}

		if(day[i].play==1) 
		{
			y++;
			printf("Yes\n");
		}
		else if(day[i].play==0) 
		{
			no++;
			printf("No\n"); 
		}
	}
	gini(sun,rain,high,norm,str,weak);
}

//function to calculate gini values
void gini(float sun,float rain,float high,float norm,float str,float weak)
{
	int i;
	float suny=0,rainy=0,highy=0,nory=0,stry=0,weaky=0; 
	float s[2],h[2],w[2];
	for(i=0;i<n;i++)
	{
		if(day[i].outlook==0 && day[i].play==1)
		{
			suny++;
		}
		else if(day[i].outlook==1 && day[i].play==1)
		{
			rainy++;
		}

		if(day[i].humid==1 && day[i].play==1)
		{
			highy++;
		}
		else if(day[i].humid==0 && day[i].play==1)
		{
			nory++;
		}

		if(day[i].wind==1 && day[i].play==1)
		{
			stry++;
		}
		else if(day[i].wind==0 && day[i].play==1)
		{
			weaky++;
		}
	}

	s[0]=(float)(((suny/sun)*(suny/sun))+(((sun-suny)/sun)*((sun-suny)/sun)));
	s[1]=(float)(((rainy/rain)*(rainy/rain))+(((rain-rainy)/rain)*((rain-rainy)/rain)));
	h[0]=(float)(((highy/high)*(highy/high))+(((high-highy)/high)*((high-highy)/high)));
	h[1]=(float)(((nory/norm)*(nory/norm))+(((norm-nory)/norm)*((norm-nory)/norm)));
	w[0]=(float)(((stry/str)*(stry/str))+(((str-stry)/str)*((str-stry)/str)));
	w[1]=(float)(((weaky/weak)*(weaky/weak))+(((weak-weaky)/weak)*((weak-weaky)/weak)));

	//printf("%f%f%f%f%f%f\n",s[0],s[1],h[0],h[1],w[0],w[1]);

	printf("no of yes=%d\nno of no=%d\n",y,no);
	gin[0]=s[0]*(float)(sun/n)+s[1]*(float)(rain/n);
	gin[1]=h[0]*(float)(high/n)+h[1]*(float)(norm/n);
	gin[2]=w[0]*(float)(str/n)+w[1]*(float)(weak/n);

	for(i=0;i<3;i++)
		printf("\n%f\n",gin[i]);

	run1();

}

//to create a node of tree
struct node* create()
{
	struct node* temp=(struct node *) malloc(sizeof(struct node));
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}

//function to calculate the best split using the gini values
void split()
{
	int i;
	float x=0;
	for(i=0;i<3;i++)
	{
		if(gin[i]>x)
		{
			x=gin[i];
			max=i;

		}
	}

	//return num;
}

//function to define the default variable
void run1()
{
	if(y>no)
		def=50;
	else
		def=49;
	dfault=create();
	dfault->data=def;

	run();
}


//function to construct the decision tree
void run()
{
	int i,noo=49,yes=50;
	struct node *temp;
	for(i=0;i<atcnt;i++)
	{
		temp=root;
		split();
		if(temp==NULL)
		{
			temp=create();
			root=temp;
		}
		else
		{
			while(temp->right!=NULL)
				temp=temp->right;
		}
		temp->data=max;
		temp->left=create();
		temp->left->data=yes;
		yes++;
		temp->right=create();
		gin[max]=0;
	}
	temp=root;
	while(temp->right != NULL)
		temp=temp->right;

	temp->data=noo;
	noo++;

}			

//function to predict the class of test case
void predictor(struct node *pre)
{

	if(pre)
	{
		if(pre->data==49)
		{
			printf("Class=No\n");
			exit(0);
		}
		else if(new[pre->data]==0 && pre->left->data==50)
		{
			printf("Class=YES\n");
			exit(0);
		}
		else
			predictor(pre->right);
	}

}	

//function to take the input of the test data set
void take()
{
	struct node *pre=root;
	printf("Enter the data\n\nOutlook= 0-Sunny 1-Rain\n");
	printf("Humidity= 0-Normal 1-High\n Wind= 0-Weak 1-Strong\n");
	scanf("%d%d%d",&new[0],&new[1],&new[2]);

	predictor(pre);
}


//dotty function
void preorderDotDump (struct node* temp3, FILE* outputFile)

{
char label[20][20]={"SUNNY","RAINY","NORMAL","HIGH","WEAK","STRONG"};


	if (temp3 != NULL) 

	{
		if(temp3->data==0)
			fprintf (outputFile, "%d [label=OUTLOOK,color=black];\n",temp3->data);
		else if(temp3->data==1)
			fprintf (outputFile, "%d [label=HUMIDITY,color=black];\n",temp3->data);
		else if(temp3->data==2)
                        fprintf (outputFile, "%d [label=WIND,color=black];\n",temp3->data);
		else if(temp3->data >=50)
			fprintf (outputFile, "%d [label=YES,color=green];\n",temp3->data);
		else if(temp3->data>=49)
			fprintf (outputFile, "%d [label=NO,color=red];\n",temp3->data);
		
		if (temp3->left != NULL)
		{ 
			fprintf (outputFile, "%d -> %d[label=", temp3->data,temp3->left->data);
			if(temp3->data==0)
				fprintf(outputFile,"SUNNY,color=black];\n");
			else if(temp3->data==1)
				fprintf(outputFile,"NORMAL,color=black];\n");
			else if(temp3->data==2)
				fprintf(outputFile,"WEAK,color=black];\n");
		}

		if (temp3->right != NULL)
		{
			fprintf (outputFile, "%d -> %d[label=", temp3->data,temp3->right->data);
			if(temp3->data==0)
                                fprintf(outputFile,"RAINY,color=black];\n");
                        else if(temp3->data==1)
                                fprintf(outputFile,"HIGH,color=black];\n");
                        else if(temp3->data==2)
                                fprintf(outputFile,"STRONG,color=black];\n");
		}

		preorderDotDump (temp3->left, outputFile);

		preorderDotDump (temp3->right, outputFile);

	}

}



void dotDump(struct node* root, FILE *outFile)

{

	gName++;

	fprintf (outFile, "digraph BST {\n",gName);



	preorderDotDump (root, outFile);

	fprintf (outFile, "}\n");

}



int main()
{
	int ch,ans,flag=1;
	FILE *pipe;
	outputFile = fopen ("decision.dot", "w");
	fclose (outputFile);
	printf("Enter no of elements\t");
	scanf("%d",&n);
	printf("Enter the attribute count\t");
	scanf("%d",&atcnt);
	enter();
	          outputFile=fopen("decision.dot","a");

                if (outputFile != NULL)
                {
                        dotDump(root,  outputFile);

                }
                fclose (outputFile);
        pipe=popen("dot -Tps decision.dot -o decision.ps","w");

                               pclose(pipe);

                               pipe=popen("evince decision.ps","r");

                               pclose(pipe);

	//to predict class for multiple test cases
	while(flag)
	{
		printf("\nEnter your choice 1.Check 2.Stop\n");		  
		
		scanf("%d",&ch);

		
		switch(ch)
		{

			case 1: take();
				break;

			case 2:flag=0;
			       break;
		}

	}
	
	 return 0;
}

