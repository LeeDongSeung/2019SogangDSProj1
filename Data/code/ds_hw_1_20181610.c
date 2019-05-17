#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int row, column, value;
}Term;
#define MAX_TERMS 1024
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
void matrixAdd(Term a[], Term b[], Term c[]){
    int row, col, val;
    int n=1, colN = 1, rowN = 1;
    int i=1,j=1;
    while(i<=a[0].value && j<=b[0].value){
        if(a[i].row == b[j].row){
            if(a[i].column == b[j].column){
                c[n].row = a[i].row;
                c[n].column = a[i].column;
                c[n].value = a[i].value + b[j].value;
				i++;
				j++;
                n++;
            }
			else if (a[i].column > b[j].column) {
				c[n].row = b[j].row;
				c[n].column = b[j].column;
				c[n].value = b[j].value;
				n++;
				j++;
			}
			else {
				c[n].row = a[i].row;
				c[n].column = a[i].column;
				c[n].value = a[i].value;
				n++;
				i++;
			}
			
        }
        else if(a[i].row > b[j].row){
            c[n].row = b[j].row;
            c[n].column = b[j].column;
            c[n].value = b[j].value;
            n++;
            j++;
        }
        else{
            c[n].row = a[i].row;
            c[n].column = a[i].column;
            c[n].value = a[i].value;
            n++;
            i++;
        }
    }
	for (; i <= a[0].value; i++) {
		c[n].row = a[i].row;
		c[n].column = a[i].column;
		c[n].value = a[i].value;
		n++;
	}
	for (; j <= b[0].value; j++) {
		c[n].row = b[i].row;
		c[n].column = b[i].column;
		c[n].value = b[i].value;
		n++;
	}
	c[0].value = n - 1;
	c[0].column = a[0].column;
	c[0].row = a[0].row;
}
void printMatrix(Term a[]){
    int i;
    for(i=0;i<=a[0].value;i++)
        printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
}
void readMatrix(FILE* fp, Term a[]){
    int i, j, n=1;
    int row, col, value;
    int rowN, colN;
    fscanf(fp, "%d %d\n", &rowN, &colN);
    a[0].column = colN;
    a[0].row = rowN;
    for(i=0;i<rowN;i++){
        for(j=0;j<colN-1;j++){
            fscanf(fp, "%d ", &value);
            if(value != 0){
                a[n].row = i;
                a[n].column = j;
				a[n].value = value;
                n++;
            }
        }
        fscanf(fp, "%d\n", &value);
            if (value != 0){
                a[n].row = i;
                a[n].column = j;
                a[n].value = value;
                n++;
            }
        }
        a[0].value = n-1;
}

