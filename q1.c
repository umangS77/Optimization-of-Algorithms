#include<stdio.h>
#include<stdlib.h>
// #include <time.h>

typedef struct Matrix
{
	int matrix[1004][1004];
	int n,m; // for n x m matrix
} Matrix;


int take_input(Matrix * restrict arr[])
{
	register int i;
	register int j;
	register int k;

	int n;
	int x;
	int y;

	// FILE *fptr;
	// fptr = fopen("./sample/Q1/90.txt", "r");
	// fscanf(fptr,"%d",&n);
	scanf("%d",&n);

	for(i=0;i<n;++i)
	{
		// fscanf(fptr,"%d %d",&x,&y);
		scanf("%d %d",&x,&y);
		Matrix * restrict mat = malloc(sizeof(Matrix));
		mat->n = x;
		mat->m = y;
		for(j=0;j<x;++j)
		{
			for(k=0;k<y;++k)
			{
				// fscanf(fptr,"%d",&mat->matrix[j][k]);
				scanf("%d", &mat->matrix[j][k]);
			}
		}
		arr[i] = mat;
	}
	// fclose(fptr);

	return n;
}


void print_matrix(Matrix * restrict result)
{
	// FILE *fptr;
	// fptr = fopen("./sample/Q1_test/90.txt", "w");

	// fprintf(fptr,"%d %d\n",result->n,result->m);
	printf("%d %d\n",result->,result->m);

	register int i;
	register int j;

	for(i=0;i<result->n;++i)
	{
		for(j=0;j<result->m;++j)
		{
			// fprintf(fptr,"%d ", result->matrix[i][j]);
			printf("%d ",result->matrix[i][j]);
		}
		// fprintf(fptr,"\n");
		printf("\n");
	}
	// fclose(fptr);
}


Matrix * multiply(Matrix * restrict A, Matrix * restrict B)
{
	// register int p = A->n;
	register int q = A->m;
	// register int r = B->m;
	Matrix * restrict result = malloc(sizeof(Matrix));
	result->n = A->n;
	result->m = B->m;




	register int max = q ^ ((q ^ (B->m)) & -(q < (B->m)));
	// register int i;
	// register int j;
	// register int k;
	// register int l;

	int block_size = 16;

	
	for(register int i=0;i<max;++i)
	{
		for(register int j=0;j<i;++j)
		{
			B->matrix[i][j] = B->matrix[i][j] ^ B->matrix[j][i];
			B->matrix[j][i] = B->matrix[j][i] ^ B->matrix[i][j];
			B->matrix[i][j] = B->matrix[i][j] ^ B->matrix[j][i];
		}
	}

	register int * restrict x;
	register int * restrict y;
	register int * restrict z;


	

	
	register int k;
	for(register int i=0;i<A->n;++i)
	{
		x = *(A->matrix + i);
		z = *(result->matrix + i);
		for(register int j=0;j<B->m;++j)
		{
			y = *(B->matrix + j);
			register int temp = 0;
			q-=block_size;
			for(k=0;k<q;k+=block_size)
			{
				// for(l=0;l<block_size;++l)
				// {
				// 	temp += *(x + k + l) * *(y + k + l);
				// }
				temp += *(x + k) * *(y + k) + *(x + k+1) * *(y + k+1) + *(x + k+2) * *(y + k+2)+ *(x + k+3) * *(y + k+3) + *(x + k+4) * *(y + k+4) + *(x + k+5) * *(y + k+5) + *(x + k+6) * *(y + k+6) + *(x + k+7) * *(y + k+7) + *(x + k+8) * *(y + k+8) + *(x + k+9) * *(y + k+9) + *(x + k+10) * *(y + k+10) + *(x + k+11) * *(y + k+11) + *(x + k+12) * *(y + k+12) + *(x + k+13) * *(y + k+13) + *(x + k+14) * *(y + k+14) + *(x + k+15) * *(y + k+15);

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



int main()
{
	// clock_t start, end;
 //    double cpu_time_used;
 //    start = clock();

	Matrix * restrict arr[5];
	
	int n = take_input(arr);

	Matrix * restrict result;

	result = multiply(arr[0], arr[1]);

	if(n==5)
	{
		result = multiply(result,arr[2]);
		result = multiply(result,arr[3]);
		result = multiply(result,arr[4]);
	}
	else if (n==4)
	{
		result = multiply(result,arr[2]);
		result = multiply(result,arr[3]);
	}
	else if (n==3)
	{
		result = multiply(result,arr[2]);
	}

	print_matrix(result);

	// end = clock();
 //    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	// printf("Time taken: %lf\n", cpu_time_used);

	return 0;

}