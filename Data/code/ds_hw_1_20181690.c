#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024
#define MAX_INT 2147483647
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main(){
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp = fopen("A.txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("B.txt", "r");
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a,b,c);
	printMatrix(c);
	return 0;
}

void readMatrix(FILE* fp, Term a[]){
	int n, m;
	int num_terms = 0;

	fscanf(fp, "%d %d", &n, &m);

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			int k;
			fscanf(fp, "%d", &k);
			if(k){
				num_terms++;
				a[num_terms].row = i;
				a[num_terms].column = j;
				a[num_terms].value = k;
			}
		}
	}
	
	a[0].row = n;
	a[0].column = m;
	a[0].value = num_terms;
	num_terms++;

	a[num_terms].row = MAX_INT;
	a[num_terms].column = MAX_INT;
	return;
} 

void printMatrix(Term a[]){
	for(int i = 0; i<=a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);

	return;
}

void matrixAdd(Term a[], Term b[], Term c[]){
	int i = 1;	//for A
	int j = 1;	//for B
	int num_terms = 0;
	c[0].row = a[0].row;
	c[0].column = a[0].column;

	while(i<=a[0].value || j<=b[0].value){
		if(a[i].row == b[j].row && a[i].column == b[j].column){
			num_terms++;
			c[num_terms].row = a[i].row;
			c[num_terms].column = a[i].column;
			c[num_terms].value = a[i].value + b[j].value;
			i++; j++; 
		}//both row and col are correct
		
		else{
			if(a[i].column <= b[j].column){
				if(a[i].row <=  b[j].row){
					num_terms++;
					c[num_terms].row = a[i].row;
					c[num_terms].column = a[i].column;
					c[num_terms].value = a[i].value;
					i++;
				}
				else{
					num_terms++;
					c[num_terms].row = b[j].row;
					c[num_terms].column = b[j].column;
					c[num_terms].value = b[j].value;
					j++;
				}
			}
			else{
				if(a[i].row <  b[j].row){
					num_terms++;
					c[num_terms].row = a[i].row;
					c[num_terms].column = a[i]. column;
					c[num_terms].value = a[i].value;
					i++;
				}
				else{
					num_terms++;
					c[num_terms].row = b[j].row;
					c[num_terms].column = b[j].column;
					c[num_terms].value = b[j].value;
					j++;
				}
			}
		}
	}
	
	c[0].value = num_terms;
	
	return;
}
