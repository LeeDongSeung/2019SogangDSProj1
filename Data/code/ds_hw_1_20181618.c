#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024

void readMatrix(FILE* fp,Term a[]){
	int n,m,i,j,k,t;

	fscanf(fp, "%d %d",&n, &m);

	a[0].row = n;
	a[0].column = m;
	a[0].value = 0;

	k = 1;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			fscanf(fp, "%d", &t);
			if (t != 0){
				a[0].value++;
				a[k].row = i;
				a[k].column = j;
				a[k].value = t;
				k++;
			}
		}
	}

	for(i = k; i < MAX_TERMS; i++){
		a[i].row = 0;
		a[i].column = 0;
		a[i].value = 0;
	}
}

void printMatrix(Term a[]){
	int i;
	for(i=0;i<=a[0].value;i++){
		printf("%d %d %d\n", a[i].row,a[i].column,a[i].value);
	}
}

void matrixAdd(Term a[],Term b[],Term c[]){
	int i,j,k;
	i=1;
	j=1;
	k=1;

	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = 0;

	while(1){
		while(a[i].row == b[j].row){

			if(a[i].column == b[j].column){
				c[k].row = a[i].row;
				c[k].column = a[i].column;
				c[k].value = a[i].value + b[j].value;
				i++;j++;
				c[0].value++;
			}
			else if(a[i].column < b[j].column){
				c[k].row = a[i].row;
				c[k].column = a[i].column;
				c[k].value = a[i].value;
				i++;
				c[0].value++;

			}
			else{
				c[k].row = b[j].row;
				c[k].column = b[j].column;
				c[k].value = b[j].value ;	
				j++;
				c[0].value++;
			}
			k++;	

			if(b[j].column == 0 && b[j].row == 0) break;
		}
		while(a[i].row > b[j].row ){
			if(b[j].column == 0 && b[j].row == 0) break;
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j].value ;	
			j++;k++;
			c[0].value++;

		}
		while(a[i].row < b[j].row || b[j].row == 0){
			if(a[i].column == 0 && a[i].row == 0) break;
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i].value;
			i++;k++;
			c[0].value++;
		}

		if(a[i].column == 0 && a[i].row == 0) break;
	}

}

int main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	FILE *fp = fopen("a[4].txt","r");
	readMatrix(fp,a);
	fclose(fp);

	fp = fopen("b[3].txt","r");
	readMatrix(fp,b);
	fclose(fp);

	matrixAdd(a,b,c);
	printMatrix(c);
	return 0;
}
