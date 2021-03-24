#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define N 1001
#define BS 16

typedef struct Matrix
{
	int matrix[N][N];
	int n,m;
} Matrix;


Matrix * multiply(Matrix * restrict A, Matrix * restrict B, register int p, register int q, register int r)
{
	register int max = q ^ ((q ^ r) & -(q < r));
	register int i;
	register int j;
	register int k;
	register int l;

	int block_size = BS;

	
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

	register int * restrict x;
	register int * restrict y;
	register int * restrict z;

	Matrix * restrict result;
	result = malloc(sizeof(Matrix));
	result->n = p;
	result->m = r;

	for(i=0;i<p;++i)
	{
		x = *(A->matrix + i);
		z = *(result->matrix + i);
		for(j=0;j<r;++j)
		{
			y = *(B->matrix + j);
			temp = 0;
			q-=block_size;
			for(k=0;k<q;k+=block_size)
			{
				for(l=0;l<block_size;++l)
				{
					temp += *(x + k + l) * *(y + k + l);
				}
				// temp += *(x + k) * *(y + k) + *(x + k+1) * *(y + k+1) + *(x + k+2) * *(y + k+2)+ *(x + k+3) * *(y + k+3) + *(x + k+4) * *(y + k+4) + *(x + k+5) * *(y + k+5) + *(x + k+6) * *(y + k+6) + *(x + k+7) * *(y + k+7) + *(x + k+8) * *(y + k+8) + *(x + k+9) * *(y + k+9) + *(x + k+10) * *(y + k+10) + *(x + k+11) * *(y + k+11) + *(x + k+12) * *(y + k+12) + *(x + k+13) * *(y + k+13) + *(x + k+14) * *(y + k+14) + *(x + k+15) * *(y + k+15);
			}
			q+=block_size;
			for(;k<q;++k)
			{
				temp += *(x + k) * *(y + k);
			}
			*(z + j) = temp;
		}
	}
	return result;
}

int take_input(Matrix * restrict arr[])
{
	register int i;
	register int j;
	register int k;

	int n;
	int x;
	int y;

	FILE *fptr;
	fptr = fopen("./sample/Q1/85.txt", "r");

	fscanf(fptr,"%d",&n);

	for(i=0;i<n;++i)
	{
		fscanf(fptr,"%d %d",&x,&y);
		Matrix * restrict mat = malloc(sizeof(Matrix));
		mat->n = x;
		mat->m = y;
		for(j=0;j<x;++j)
		{
			for(k=0;k<y;++k)
			{
				fscanf(fptr,"%d",&mat->matrix[j][k]);
			}
		}
		arr[i] = mat;
	}
	fclose(fptr);

	return n;
}

void print_matrix(Matrix * restrict result)
{
	FILE *fptr;
	fptr = fopen("./sample/Q1_test/85.txt", "w");

	fprintf(fptr,"%d %d\n",result->n,result->m);

	register int i;
	register int j;

	for(i=0;i<result->n;++i)
	{
		for(j=0;j<result->m;++j)
		{
			fprintf(fptr,"%d ", result->matrix[i][j]);
		}
		fprintf(fptr,"\n");
	}
	fclose(fptr);
}


int main()
{
	Matrix * restrict arr[5];
	
	int n = take_input(arr);

	Matrix * restrict result;

	result = multiply(arr[0], arr[1], arr[0]->n, arr[0]->m, arr[1]->m);

	register int i;

	for(i=2;i<n;++i)
	{
		result = multiply(result, arr[i], result->n, result->m, arr[i]->m);
	}
	print_matrix(result);

}