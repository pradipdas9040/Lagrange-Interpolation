#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x)
{
	return 1/(1+25*x*x);
}

double X(int i,int n)
{
	return -1+(double)(2*i)/(n-1);
}

double interpol(int n, double xp, double x[], double y[])
{
	int i,j;
	double p,yp=0;
	for(i=0;i<n;i++)
	{
		p=1;
		for(j=0;j<n;j++)
		{
			if(i!=j)
			{
		    	p = p* (xp - x[j])/(x[i] - x[j]);
			}
		}
		yp = yp + p * y[i];
	}
	return yp;
}

int main()
{
	FILE *fp;
	int n,i,j,m=1001;
	printf("Enter the number of interpolating point: ");
	scanf("%d",&n);
	double x[n],y[n],z[m],xp,max=0,dif,c,d,xt;
	fp=fopen("d:/prunge.dat","w");
	for(i=0;i<n;i++)
	{
		x[i]=X(i,n);
		y[i]=f(X(i,n));
	}
	for(i=0;i<m;i++)
	{
		z[i]=X(i,m);
	}
	for(i=0;i<m;i++)
	{
		c=f(z[i]);
		d=interpol(n, z[i], x, y);
		dif=fabs(c-d);
		if(max<dif)
		{
			xt=z[i];
			max=dif;
		}
		fprintf(fp,"%lf  %lf  %lf\n",z[i],c,d);	
	}
	printf("||f-P_%d||=%.4lf at %.4lf",n-1,max,xt);
	fclose(fp);
	return 0;
}
