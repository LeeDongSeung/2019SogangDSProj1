#include <stdio.h>
#include <stdlib.h>

int i;
int at,bt,count,inputrow,inputcol;

typedef struct {
    int row, column, value;
} Term;

#define MAX_TERMS 1024

void readMatrix(FILE* fp,Term a[]);

void printMatrix(Term a[]);

void matrixAdd(Term a[],Term b[],Term c[]);

int main() {
    Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
    count=0;

    FILE *fp = fopen("a[4].txt","r");
    readMatrix(fp,a);
    fclose(fp);
    at=count;


    fp = fopen("b[3].txt","r");
    readMatrix(fp,b);
    fclose(fp);
    bt=count-at;

    matrixAdd(a,b,c);

    printMatrix(c);
    
    return 0;
}

void readMatrix(FILE *fp,Term a[]){

    int tempvalue,i,j;
    i=0;
    j=0;
    int k=0;

    fscanf(fp,"%d %d",&inputrow,&inputcol);

    for(int p=0;p<inputrow*inputcol;p++){
        fscanf(fp,"%d",&tempvalue);
        if(tempvalue != 0){
            a[i].value = tempvalue;
            a[i].row = j;
            a[i].column = (k%inputcol);
            count++;
        }
        else{
            i--;
        }
        i++;
        if((k%inputcol) == (inputcol-1) ){
            j++;
        }
        k++;
    }
}
void matrixAdd(Term a[],Term b[],Term c[]){

    int atime=0;
    int btime=0;
    int i,j,loop,compare;
    i=0;
    j=0;
    int k=0;

    for(loop=count;loop>0;loop--){
        if(a[i].row == b[j].row && a[i].column == b[j].column)compare=0;//a+b
        if(a[i].row == b[j].row && a[i].column < b[j].column)compare=1;//a
        if(a[i].row == b[j].row && a[i].column > b[j].column)compare=2;//b
        if(a[i].row < b[j].row && a[i].column <= b[j].column)compare=3;//a
        if(a[i].row > b[j].row && a[i].column >= b[j].column)compare=4;//b
        if(a[i].row > b[j].row && a[i].column <= b[j].column)compare=5;//b
        if(a[i].row < b[j].row && a[i].column >= b[j].column)compare=6;//a
        if(atime==at && btime<bt)compare=7;//b
        if(btime==bt && atime<at)compare=8;//a
        
        switch(compare){
            case 0:
                c[k].row = a[i].row;
                c[k].column = a[i].column;
                c[k].value = a[i].value + b[j].value;
                
                loop--;
                count--;
                k++;
                i++;
                j++;

                atime++;
                btime++;
            break;
            
            case 7:
            case 2:
            case 4:    
            case 5:
            btime++;
                c[k].row = b[j].row;
                c[k].column = b[j].column;
                c[k].value =b[j].value;

                k++;
                j++;
            break;
            case 8:
            case 1:
            case 3:
            case 6:
            atime++;
                c[k].row = a[i].row;
                c[k].column = a[i].column;
                c[k].value = a[i].value;

                k++;
                i++;

            break;
        }
    }

}
void printMatrix(Term a[]){

    int i=0;
    
    printf("%d %d %d\n",inputrow,inputcol,count);
    while(count>0){
        printf("%d %d %d\n",a[i].row,a[i].column,a[i].value);
        i++;
        count--;
    }

}