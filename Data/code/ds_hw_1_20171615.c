#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS	1024
#define filename1	"a[4].txt"
#define filename2	"b[3].txt"

typedef struct term{
	int row, col, value;
}term;

void readM(FILE *fp, term a[]);
void addM(term a[], term b[], term c[]);
void printM(term b[]);
void attach(term c[], int row, int col, int value);

int pointer = 1;

int main(){
	term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	FILE *fp1, *fp2;
	fp1 = fopen(filename1, "r");
	readM(fp1, a);
	fclose(fp1);

	fp2 = fopen(filename2, "r");
	readM(fp2, b);
	fclose(fp2);
	
	addM(a, b, c);
	printM(c);
	return 0;
}

void readM(FILE *fp, term a[]){
	int n, m, k, count = 1;
	fscanf(fp, "%d %d", &n, &m);
	
	a[0].row = n;
	a[0].col = m;

	for(int j = 0; j < n; j++){
		for(int i = 0; i < m; i++){
			fscanf(fp, "%d", &k);
			if(k){
				a[count].col = i;
				a[count].row = j;
				a[count++].value = k;
			}
		}
	}
	a[0].value = count - 1;
}

void attach(term c[], int row, int col, int value){
	c[pointer].row = row;
	c[pointer].col = col;
	c[pointer++].value = value;
}

void addM(term a[], term b[], term c[]){
	int count = 0;
	int i = 1;
	int j = 1;
	int sum = 0;
	
	c[0].row = a[0].row;
	c[0].col = a[0].col;
	
	while(i <= a[0].value && j <= b[0].value){
		if(a[i].row < b[j].row){//store a
			attach(c, a[i].row, a[i].col, a[i].value);
			i++; continue;
		}
		else if(a[i].row > b[j].row){//store b
			attach(c, b[j].row, b[j].col, b[j].value);	
			j++; continue;
		}
		else if((a[i].row == b[j].row) && (a[i].col < b[j].col)){//store a
			attach(c, a[i].row, a[i].col, a[i].value);	
			i++; continue;
		}
		else if((a[i].row == b[j].row) && (a[i].col > b[j].col)){//store b
			attach(c, b[j].row, b[j].col, b[j].value);	
			j++; continue;
		}
		else if((a[i].row == b[j].row) && (a[i].col == b[j].col)){//store a & b
			sum = a[i].value + b[j].value;
			if(sum){
				attach(c, a[i].row, a[i].col, sum);
			}
			i++; j++; continue;
		}
	}

	//나머지 저장
	for(; i <= a[0].value; i++){
		attach(c, a[i].row, a[i].col, a[i].value);
	}
	for(; j <= b[0].value; j++){
		attach(c, b[j].row, b[j].col, b[j].value);
	}

	c[0].value = pointer - 1;
}

void printM(term b[]){
	for(int i = 0; i <= b[0].value; i++){
		printf("%d %d %d\n", b[i].row, b[i].col, b[i].value);
	}
}
