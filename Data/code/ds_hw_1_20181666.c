#include <stdio.h>
#include <stdlib.h>
typedef struct{
	int row,col,value;
}Term;
#define MAX_TERMS 1024
void readMatrix(FILE *fp,Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main(){
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	
	FILE *fp = fopen("A.txt","r");
	readMatrix(fp,a);
	fclose(fp);
	
	fp = fopen("B.txt","r");
	readMatrix(fp,b);
	fclose(fp);

	matrixAdd(a,b,c);
	printMatrix(c);

	return 0;
}
void readMatrix(FILE *fp,Term a[]){
	int n,m,i,j,tmp,cnt=0;
	
	fscanf(fp,"%d%d",&n,&m);
	a[0].row = n;
	a[0].col = m;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			fscanf(fp,"%d",&tmp);
			if(tmp != 0){
				cnt++;
				a[cnt].value=tmp;
				a[cnt].row=i;
				a[cnt].col=j;
			}
		}
	}
	a[0].value = cnt;
	return;
}
void printMatrix(Term a[]){
	int i;
	for(i=0;i<=a[0].value;i++){
		printf("%d %d %d\n",a[i].row,a[i].col,a[i].value);
	}
	return;
}
void matrixAdd(Term a[], Term b[], Term c[]){
	int i=1,j=1,cnt=0,sum;
	c[0].row = a[0].row;
	c[0].col = a[0].col;
	while(i<=a[0].value && j<=b[0].value){
		if(a[i].row == b[j].row){
			if(a[i].col == b[j].col){
				sum = a[i].value + b[j].value;
				if(sum!=0){
					cnt++;
					c[cnt].row = a[i].row;
					c[cnt].col = a[i].col;
					c[cnt].value = sum;
				}
				i++;
				j++;
			}
			else if(a[i].col > b[j].col){
				cnt++;
				c[cnt].value = b[j].value;
				c[cnt].row = b[j].row;
				c[cnt].col = b[j].col;
				j++;
			}
			else{
				cnt++;
				c[cnt].row = a[i].row;
				c[cnt].col = a[i].col;
				c[cnt].value = a[i].value;
				i++;
			}
		}
		else if (a[i].row > b[j].row){
			cnt++;
			c[cnt].value = b[j].value;
			c[cnt].row = b[j].row;
			c[cnt].col = b[j].col;
			j++;
		}
		else {
			cnt++;
			c[cnt].value = a[i].value;
			c[cnt].row = a[i].row;
			c[cnt].col = a[i].col;
			i++;
		}
	}
	while(i<=a[0].value){
		cnt++;
		c[cnt].row = a[i].row;
		c[cnt].col = a[i].col;
		c[cnt].value = a[i].value;
		i++;
	}
	while(j<=b[0].value){
		cnt++;
		c[cnt].row = b[j].row;
		c[cnt].col = b[j].col;
		c[cnt].value = b[j].value;
		i++;
	}

	c[0].value = cnt;
	return;
}
