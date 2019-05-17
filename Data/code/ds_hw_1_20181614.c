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

    FILE* fp = fopen("A.txt", "r");
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
    fscanf(fp, "%d %d", &a[0].row, &a[0].column);

    int num;
    int cnt=1, row=0, col=0, value=0;
    while(1){
        fscanf(fp, "%d", &num);
        if(feof(fp)) break;
        if(num){
            a[cnt].row = row;
            a[cnt].column = col;
            a[cnt++].value = num;
            value++;
        }
        col++;
        if(col==a[0].column){
            col %= a[0].column;
            row++;
        }
    }
    a[0].value = value;
}

void printMatrix(Term a[]){
    for(int i=0; i<=a[0].value; i++){
        printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
    }
}

void matrixAdd(Term a[], Term b[], Term c[]){
    int chk;
    c[0].row = a[0].row;
    c[0].column = a[0].column;
    int idxa=1, idxb=1, cnt=1, value=0;
    int nowidxa, nowidxb;
    int vala=a[0].value, valb=b[0].value;
    while(a[0].value && b[0].value){
        nowidxa = a[idxa].row*a[0].column+a[idxa].column;
        nowidxb = b[idxb].row*b[0].column+b[idxb].column;
        chk = (nowidxa < nowidxb)? -1 : (nowidxa == nowidxb)? 0 : 1;
        switch(chk){
            case -1:{
                        c[cnt].row = a[idxa].row;
                        c[cnt].column = a[idxa].column;
                        c[cnt++].value = a[idxa++].value;
                        value++;
                        a[0].value--;
                        break;
                    }
            case 0:{
                       c[cnt].row = a[idxa].row;
                       c[cnt].column = a[idxa].column;
                       c[cnt++].value = a[idxa++].value + b[idxb++].value;
                       value++;
                       a[0].value--; b[0].value--;
                       break;
                   }
            case 1:{
                       c[cnt].row = b[idxb].row;
                       c[cnt].column = b[idxb].column;
                       c[cnt++].value = b[idxb++].value;
                       value++;
                       b[0].value--;
                       break;
                   }
        }
    }
    for(int i=idxa; i<=vala;i++){
        c[cnt].row = a[idxa].row;
        c[cnt].column = a[idxa].column;
        c[cnt++].value = a[idxa++].value;
        value++;
    }
    for(int i=idxb; i<=valb; i++){
        c[cnt].row = b[idxb].row;
        c[cnt].column = b[idxb].column;
        c[cnt++].value = b[idxb++].value;
        value++;
    }
    c[0].value = value;
}
