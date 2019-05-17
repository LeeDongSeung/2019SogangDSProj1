#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int insertsort(int *num, int i);
int main()
{
	FILE* data = fopen("lab1.data", "r");
	int *num;
	int i = 0;
	int a;
	num = (int*)malloc(sizeof(int) * 100);
	while (1)
	{
		int t = fscanf(data, "%d", &num[i]);
		if (t == EOF)
			break;
		i++;
	}
	printf("input : ");
	for (a = 0; a < i; a++)
	{
		printf("%d ", num[a]);
	}
	printf("\n");
	clock_t start = clock();
	insertsort(num, i);
	printf("%lf\n", (double)(clock() - start));
	printf("input : ");
	for (a = 0; a < i; a++)
	{
		printf("%d ", num[a]);
	}
	printf("\n");
	fclose(data);
	free(num);
	printf("   n   repetitions    time\n");
	int *test;
	int j, n, step = 10;
	test = (int*)malloc(sizeof(int) * 101);
	double duration;
	for (n = 0; n <= 100; n += step)
	{
		long repetitions = 0;
		clock_t start = clock();
		do {
			repetitions++;
			for (j = 0; j < n; j++)
			{
				test[j] = n - j;
			}
			insertsort(test, n);
		} while (clock() - start < 1000);
		duration = ((double)(clock() - start));
		duration /= repetitions;
		printf("%6d  %9d    %f\n", n, repetitions, duration);
	}
	free(test);
	return 0;
}
int insertsort(int *num, int i)
{
	int j, k;
	int temp;

	for (j = 1; j < i; j++)
	{
		temp = num[j];
		k = j - 1;

		while ((k >= 0) && (temp < num[k]))
		{
			num[k + 1] = num[k];
			k = k - 1;
		}

		num[k + 1] = temp;
	}
}
