#include<stdio.h>
#include<stdlib.h>
typedef struct{
	int row, column, value;
}Term;
#define MAX_TERMS 1024
int check=1;
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[],Term b[],Term c[]);
int main()
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp=fopen("a.txt","r");
	readMatrix(fp,a);
	fclose(fp);

	fp=fopen("b.txt","r");
	readMatrix(fp,b);
	fclose(fp);

	matrixAdd(a,b,c);
	printMatrix(c);
	return 0;
}
void readMatrix(FILE *fp, Term a[])
{
	int m,n,i,j,num,count=1;
	fscanf(fp,"%d %d\n",&m,&n);
	if(check==1)
	{
		printf("%d %d ",m,n);
		check=0;
	}
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(fp,"%d ",&num);
			if(num!=0)
			{
				a[count].row=i;
				a[count].column=j;
				a[count++].value=num;
			}
		}
	}
}
void printMatrix(Term a[])
{
	int i=1;
	while(a[i].value!=0)
	{
		i++;
	}
	printf("%d\n",i-1);
	i=1;
	while(a[i].value!=0)
	{
		printf("%d %d %d\n",a[i].row,a[i].column,a[i].value);
		i++;
	}
}
void matrixAdd(Term a[],Term b[],Term c[])
{
	int i=1,j=1,k=1,op;
	while(a[i].value!=0 && b[j].value!=0)
	{
		if(a[i].row==b[j].row)
		{
			if(a[i].column==b[j].column)
			{
				c[k].row=a[i].row;
				c[k].column=a[i].column;
				c[k].value=a[i].value+b[j].value;
				if(a[i+1].value!=0)
				{
					i++;
				}
				else
				{
					k++;
					op=1;
					break;
				}
				if(b[j+1].value!=0)
				{
					j++;
				}
				else
				{
					k++;
					op=2;
					break;
				}
				k++;
			}
			else if(a[i].column<b[j].column)
			{
				c[k].row=a[i].row;
				c[k].column=a[i].column;
				c[k].value=a[i].value;
				if(a[i+1].value!=0)
				{
					i++;
				}
				else
				{
					k++;
					op=1;
					break;
				}
				k++;
			}
			else
			{
				c[k].row=b[j].row;
				c[k].column=b[j].column;
				c[k].value=b[j].value;
				if(b[j+1].value!=0)
				{
					j++;
				}
				else
				{
					k++;
					op=2;
					break;
				}
				k++;
			}
		}
		else if(a[i].row<b[j].row)
		{
			c[k].row=a[i].row;
			c[k].column=a[i].column;
			c[k].value=a[i].value;
			if(a[i+1].value!=0)
			{
				i++;
			}
			else
			{
				k++;
				op=1;
				break;
			}
			k++;
		}
		else
		{
			c[k].row=b[j].row;
			c[k].column=b[j].column;
			c[k].value=b[j].value;
			if(b[j+1].value!=0)
			{
				j++;
			}
			else
			{
				k++;
				op=2;
				break;
			}
			k++;
		}
	}
	if(op==1)
	{
		while(b[j].value!=0)
		{
			c[k].row=b[j].row;
			c[k].column=b[j].column;
			c[k].value=b[j].value;
			j++;
			k++;
		}
	}
	else if(op==2)
	{
		while(a[i].value!=0)
		{
			c[k].row=a[i].row;
			c[k].column=a[i].column;
			c[k].value=a[i].value;
			i++;
			k++;
		}
	}
}
