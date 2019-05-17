#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 1024

typedef struct{
	int row, column, value;
}Term;
void readMatrix(FILE* fp, Term a[]){
	int temp, res, i, j, idx = 1;
	fscanf(fp, "%d %d", &a[0].row, &a[0].column);
	for(i = 0; i < a[0].row; i++){
		for(j = 0; j < a[0].column; j++){
			res = fscanf(fp, "%d", &temp);
			if(res != EOF){
				if(temp != 0){
					a[idx].row = i;
					a[idx].column = j;
					a[idx++].value = temp;
				}	
			}
			else{
				break;
			}
		}
		if(res == EOF){
			break;
		}
	}
	a[0].value = --idx;
	return;
}
void printMatrix(Term a[]){
	int i;
	printf("%d %d %d\n", a[0].row, a[0].column, a[0].value);
	for(i = 1; i <= a[0].value; i++){
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
	return;
}
void matrixAdd(Term a[], Term b[], Term c[]){
	int a_idx, b_idx, flag, idx = 1;
	a_idx = 1; b_idx = 1;
	while(a_idx <= a[0].value && b_idx <= b[0].value){
		if(a[a_idx].row > b[b_idx].row){
			flag = 1;
		}
		else if(a[a_idx].row < b[b_idx].row){
			flag = 2;
		}
		else{
			if(a[a_idx].column > b[b_idx].column){
				flag = 1;
			}
			else if(a[a_idx].column < b[b_idx].column){
				flag = 2;
			}
			else{
				flag = 0;
			}
		}
		switch(flag){
			case 0 : c[idx].row = a[a_idx].row; c[idx].column = b[b_idx].column;
				 c[idx++].value = a[a_idx++].value + b[b_idx++].value; break;
			case 1 : c[idx].row = b[b_idx].row; c[idx].column = b[b_idx].column;
				 c[idx++].value = b[b_idx++].value; break;
			case 2 : c[idx].row = a[a_idx].row; c[idx].column = a[a_idx].column;
				 c[idx++].value = a[a_idx++].value; break;
		}
	}
	for(; a_idx <= a[0].value;){
		c[idx].row = a[a_idx].row; c[idx].column = a[a_idx].column;
		c[idx++].value = a[a_idx++].value;
	}
	for(; b_idx <= b[0].value;){
		c[idx].row = b[b_idx].row; c[idx].column = b[b_idx].column;
		c[idx++].value = b[b_idx++].value;
	}
	c[0].row = a[0].row; c[0].column = a[0].column; c[0].value = --idx;
	return;
}

int main(){
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp = fopen("A.txt","r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("B.txt","r");
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a, b, c);
	printMatrix(c);

	return 0;
}
