#include <stdio.h>
typedef struct {
	int row;
	int col;
	int value;
} term;

#define MAX_TERMS 1024
term a[MAX_TERMS];
term b[MAX_TERMS];
term c[MAX_TERMS];
void readMatrix(FILE* fp, term a[]);
void printMatrix(term a[]);
void matrixAdd(term a[], term b[], term c[]);

int main(){
	FILE *fp = NULL;
	fp = fopen("a[4].txt", "r");
	readMatrix(fp, a);
	fp = fopen("b[3].txt", "r");
	readMatrix(fp, b);
	matrixAdd(a, b, c);
	printMatrix(c);
	return 0;
}
void readMatrix(FILE *fp, term a[]) {
	int f = 0;
	int k = 1;

	fscanf(fp, "%d %d", &a[0].row, &a[0].col);
	for (int i = 0; i < a[0].row; i++) {
		for (int j = 0; j < a[0].col; j++) {
			fscanf(fp, "%d", &f);
			if (f != 0) {
				a[k].value = f;
				a[k].col = j;
				a[k].row = i;
				k++;
			}
		}
	}
	a[0].value = k - 1;
	fclose(fp);

}
void matrixAdd(term a[], term b[], term c[]) {
	int k = 0;
	int i = 1;
	int indexa = 1;
	int indexb = 1;
	while(indexa <= a[0].value && indexb <= b[0].value){
		if(1000*a[indexa].row+a[indexa].col<1000*b[indexb].row+b[indexb].col){
			c[i].row = a[indexa].row;
			c[i].col = a[indexa].col;
			c[i].value = a[indexa].value;
			i++;indexa++;
		}
		else if(1000*a[indexa].row+a[indexa].col>1000*b[indexb].row+b[indexb].col){
			c[i].row = b[indexb].row;
			c[i].col = b[indexb].col;
			c[i].value = b[indexb].value;
			i++;indexb++;
			
		}
		else{
			k = a[indexa].value + b[indexb].value;
			if(k){
				c[i].row = b[indexb].row;
				c[i].col = b[indexb].col;
				c[i].value = k;
				i++;indexb++;indexa++;
			}
				
		}
	}
	for(;indexa<=a[0].value;indexa++,i++){
		c[i].row = a[indexa].row;
		c[i].col = a[indexa].col;
		c[i].value = a[indexa].value;
	}
	for(;indexb<=b[0].value;indexb++,i++){
		c[i].row = b[indexb].row;
		c[i].col = b[indexb].col;
		c[i].value = b[indexb].value;
	}
	c[0].row = a[0].row;
	c[0].col = a[0].col;
	c[0].value = i-1;
}

void printMatrix (term a[]){
	for (int i = 0; i <= a[0].value; i++){
		printf("%d %d %d \n", a[i].row, a[i].col, a[i].value);
	}
}
