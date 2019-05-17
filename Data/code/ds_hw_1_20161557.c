#include<stdio.h>
#include<stdlib.h>
typedef struct{
	int row, column, value;
}Term;
#define MAX_TERMS 2014

void readMatrix(FILE* fp, Term a[]);//read Matrix from file
void printMatrix(Term a[]);//print Matrix
void matrixAdd(Term a[], Term b[], Term c[]);//make c matrix adding a and b matrix
int main(){
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp=fopen("A[4].txt","r");
	readMatrix(fp,a);
	fclose(fp);
	
	fp=fopen("B[3].txt","r");
	readMatrix(fp,b);
	fclose(fp);

	matrixAdd(a,b,c);
	printMatrix(c);
	return 0;
}
void readMatrix(FILE* fp, Term a[]){
	int i=0, j=0, avail=1,d;
	int col;
	fscanf(fp,"%d %d",&(a[0].row),&(a[0].column));
	while(fscanf(fp,"%d",&d)!=EOF){
		if(d!=0){//if d is not 0, add A matrix
			a[avail].row=i;
			a[avail].column=j;
			a[avail].value=d;
			avail++;
		}
		j++;
		if(j==(a[0].column)){//if j== column num, i++;
			j=0;
			i++;
		}
	}
	a[0].value=avail;
}
void printMatrix(Term a[]){
	int i;
	for(i=0;i<=a[0].value;i++)
		printf("%d %d %d\n",a[i].row,a[i].column,a[i].value);
}
void matrixAdd(Term a[],Term b[], Term c[]){
	int i, j, k;
	int temp=0;
	int col=a[0].column;
	i=1;j=1;k=1;
	while(1){
		if(a[i].row==b[j].row && a[i].column==b[j].column){//Add A value and B value
			c[k].row=a[i].row;
			c[k].column=a[i].column;
			c[k].value=a[i].value+b[j].value;
			i++;j++;k++;
		}
		else if((a[i].row*col+a[i].column < b[j].row*col+b[j].column) || temp==1){//Add A value
			c[k].row=a[i].row;
			c[k].column=a[i].column;
			c[k++].value=a[i++].value;
		}
		else{//Add B value
			c[k].row=b[j].row;
			c[k].column=b[j].column;
			c[k++].value=b[j++].value;
		}
		if(i>=a[0].value && j>=b[0].value)
			break;
		if(j>=b[0].value)
			temp=1;
	}
	c[0].row=a[0].row;
	c[0].column=a[0].column;
	c[0].value=k-1;
}
