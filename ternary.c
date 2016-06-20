#include<stdio.h>

void search( int a[], int i,int j, int k)
{

int x,y;
if(i<=j)
{

x=i+(j-i)*1/3;
y=i+(j-i)*2/3;

if(a[x]==k)
printf("%d found at position %d\n",k,x+1);

else if(a[y]==k)
printf("%d found at position %d\n",k,y+1);

else if(k<a[x])
search(a,i,x-1,k);

else if(k>a[y])
search(a,y+1,j,k);

else if(k>a[x] && k<a[y])
search(a,x+1,y-1,k);
}

else printf("%d not found\n",k);
}

int main()
{
int a[20],n,i,k;
printf("Enter the no of elements\n");
scanf("%d",&n);
printf("\n Enter the elements in ascending order\n");
for(i=0;i<n;i++)
scanf("%d",&a[i]);
printf("Enter the element to be searched\n");
scanf("%d",&k);
search(a,0,n-1,k);

return 0;
}


