#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define N 1001

typedef struct Matrix
{
	int matrix[N][N];
	int n,m;
} Matrix;


Matrix * multiply(Matrix * restrict A, Matrix * restrict B, register int p, register int q, register int r)
{
	Matrix * restrict result;
	result = malloc(sizeof(Matrix));
	result->n = p;
	result->m = r;
	register int max = q ^ ((q ^ r) & -(q < r));

	register int i;
	register int j;
	

	for(i=0;i<max;++i)
	{
		for(j=0;j<i;++j)
		{
			B->matrix[i][j] ^= B->matrix[j][i];
			B->matrix[j][i] ^= B->matrix[i][j];
			B->matrix[i][j] ^= B->matrix[j][i];
		}
	}

	register int temp;
	register int k;

	register int * restrict x;
	register int * restrict y;
	register int * restrict z;

	for(i=0;i<p;++i)
	{
		x = *(A->matrix + i);
		z = *(result->matrix + i);
		for(j=0;j<r;++j)
		{
			y = *(B->matrix + j);
			temp = 0;
			q-=16;
			for(k=0;k<q;k+=16)
			{
				temp += *(x + k) * *(y + k) + *(x + k+1) * *(y + k+1) + *(x + k+2) * *(y + k+2)+ *(x + k+3) * *(y + k+3) + *(x + k+4) * *(y + k+4) + *(x + k+5) * *(y + k+5) + *(x + k+6) * *(y + k+6) + *(x + k+7) * *(y + k+7) + *(x + k+8) * *(y + k+8) + *(x + k+9) * *(y + k+9) + *(x + k+10) * *(y + k+10) + *(x + k+11) * *(y + k+11) + *(x + k+12) * *(y + k+12) + *(x + k+13) * *(y + k+13) + *(x + k+14) * *(y + k+14) + *(x + k+15) * *(y + k+15);
			}
			q+=16;
			for(;k<q;++k)
			{
				temp += *(x + k) * *(y + k);
			}
			*(z + j) = temp;
		}
	}
	return result;
}

int main()
{
	int n;
	register int i;
	register int j;
	register int k;

	int x;
	int y;


	scanf("%d",&n);
	Matrix * restrict arr[n];

	for(i=0;i<n;++i)
	{
		scanf("%d %d",&x,&y);
		Matrix * restrict mat = malloc(sizeof(Matrix));
		mat->n = x;
		mat->m = y;
		for(j=0;j<x;++j)
		{
			for(k=0;k<y;++k)
			{
				scanf("%d",&mat->matrix[j][k]);
			}
		}
		arr[i] = mat;
	}

	Matrix * restrict result;

	result = multiply(arr[0], arr[1], arr[0]->n, arr[0]->m, arr[1]->m);

	for(i=2;i<n;++i)
	{
		result = multiply(result, arr[i], result->n, result->m, arr[i]->m);
	}

	printf("%d %d\n",result->n,result->m);

	for(i=0;i<result->n;++i)
	{
		for(j=0;j<result->m;++j)
		{
			printf("%d ", result->matrix[i][j]);
		}
		printf("\n");
	}



}