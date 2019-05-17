#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int row, column, value;
} Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);

int main(void)
{
    Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

    FILE *fp = fopen("A.txt", "r");
    readMatrix(fp, a);
    fclose(fp);
    fp = fopen("B.txt", "r");
    readMatrix(fp, b);
    fclose(fp);
    matrixAdd(a, b, c);
    printMatrix(c);
    return 0;
}
void readMatrix(FILE* fp,Term a[])
{
    int t,i=-1, j=-1,n,m,count=0;
    fscanf(fp,"%d%d", &n, &m);
    int p = 1;
    a[0].row = n; a[0].column = m;
    while (count!=m*n)
    {
        count++;
        j++;
        j = j % m;
        if (j == 0)
        {
            i++;
        }
        fscanf(fp,"%d", &t);
        if (t == 0) continue;
        a[p].row = i;
        a[p].column = j;
        a[p++].value = t;
    }
    a[0].value = p - 1;
}

void printMatrix(Term a[])
{
    for (int i = 0; i <= a[0].value; i++)
    {
        if(a[i].value!=0)
            printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
    }
}


void matrixAdd(Term a[], Term b[], Term c[])
{
    int n,m,i=0,j=0,acount=1,bcount=1,ccount=1,acheck=0,bcheck=0,count=0;
    n = a[0].row;
    m = a[0].column;
	for (i = 0; i <= n * m; i++) {
		c[i].row = 0;
		c[i].column = 0;
		c[i].value = 0;
	} //initialization
	i = 0;
    c[0].row= n;
    c[0].column = m;
    c[0].value=0;
    while(count!=m*n)
    {
        if(a[acount].row==i && a[acount].column==j)
        {
            c[ccount].value=c[ccount].value+a[acount].value;
            acount++;
            acheck=1;
        }
        if(b[bcount].row==i && b[bcount].column==j)
        {
            c[ccount].value=c[ccount].value+b[bcount].value;
            bcount++;
            bcheck=1;
        }
        if(acheck==1 || bcheck==1)
        {
            c[ccount].row=i;
            c[ccount].column=j;
            ccount++;
            acheck=0;
            bcheck=0;
            c[0].value++;
        }
        count++;
        j++;
        if(j%m ==0)
        {
            j=0;
            i++;
        }
    }
}
