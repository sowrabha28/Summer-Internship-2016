#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void regression()
{
	int n,x[100],y[100],i,j;
	float Yplot[100],xmean=0,ymean=0,slope,yinter,a,b,numer=0,den=0,e=0,yline;
	FILE *file;
	FILE *pipe = popen("gnuplot -persist", "w");
	file=fopen("points","w");

	printf("Enter the no of points\n");
	scanf("%d",&n);
	printf("Enter the points\n");
	for(i=0;i<n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
	}
	printf("Points are\n");
	printf("Point number\tX-ordinate\tY-ordinate\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t\t%d\t\t%d\n",i,x[i],y[i]);
	}

	for (i=0; i < n; i++)
	{
		fprintf(file,"%d %d \n",x[i],y[i]);
	}
	fclose(file);

	for(i=0;i<n;i++)
	{
		xmean=xmean+x[i];
		ymean=ymean+y[i];
	}

	xmean=xmean/n;
	ymean=ymean/n;

	for(i=0;i<n;i++)
	{
		a=x[i]-xmean;
		b=y[i]-ymean;
		numer=numer+(a*b);
		den=den+(a*a);
	}

	slope=numer/den;

	yinter=ymean-(slope*xmean);

	printf("Slope=%.3f\nY-Intercept=%.3f\n",slope,yinter);

	for(i=0;i<n;i++)
	{
		yline=(slope*x[i])+yinter;
		e=e+((y[i]-yline)*(y[i]-yline));
	}
	e=e/n;
	printf("Squared error=%.3f\n\n",e);

	printf("Equation of the line is: Y=%.3fx+%.3f+%.3f\n",slope,yinter,e);


	for(i=0;i<n;i++)
	{
		Yplot[i]=(slope*x[i])+yinter;
	}

	file=fopen("data","w");

	for (i=0; i < n; i++)
	{
		fprintf(file,"%d\t%.2f \n",x[i],Yplot[i]);
	}
	fclose(file);
	fprintf(pipe,"set title \"LINEAR REGRESSION\"\n");
	fprintf(pipe,"set style data lines\n");
	fprintf(pipe,"plot 'data' with lines, 'points' with points\n");

}

int main()
{
	regression();
	return 0;
}

