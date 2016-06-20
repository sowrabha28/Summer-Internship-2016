#include<stdio.h>
int main()
{

	int arr[10][10];
	int m,n,i=0,j=0,count=1,a,b,z;
	printf("enter the no of rows n cols\n");
	scanf("%d%d",&n,&m);
	printf("\n enter the elements\n");
	for(a=0;a<n;a++)
	{
		for(b=0;b<m;b++)
			scanf("%d",&arr[a][b]);
	}

	printf("\n\n");
	z=m*n;
       rec(m,n,i,j,count,z,arr);
return 0;
}

void rec(int m, int n, int i, int j, int count, int z, int arr[][10])
{


	

		for(;j<m;j++)
		{
			if(count<=z)
			{
				printf("%d\n",arr[i][j]);
				count++;	
			}
		}
		j--;
		i++;

		for(;i<n;i++)
		{
			if(count<=z)
			{
				printf("%d\n",arr[i][j]);
				count++;
			}
		}
		i--;
		j--;

		for(;j>=0;j--)
		{
			if(count<=z)
			{
				printf("%d\n",arr[i][j]);
				count++;
			}
		}
		j++;
		i--;

		for(;i>0;i--)
		{
			if(count<=z)
			{
				printf("%d\n",arr[i][j]);
				count++;
			}
		}
		j++;
		i++;
		m--;
		n--;
 	if (count<=z)
	rec(m,n,i,j,count,z,arr);
	}


