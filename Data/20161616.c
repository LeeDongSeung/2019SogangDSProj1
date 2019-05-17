#include <stdio.h>

int main(void){
		FILE*fp = fopen("input.txt");
		int d;
		fscanf(fp,"%d",&d);
		printf("%d\n",d);
		return 0;
}
