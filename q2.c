#include <stdio.h>
#include <stdlib.h>
// #include <time.h>

#define INF -1
#define BS 16 // block_size

void take_input(int A[], register int e, register int n_oversized)
{

	register int i;
	int x;
	int y;
	int w;

	for(i=0;i<e;++i)
	{
		scanf("%d %d %d", &x, &y, &w);
		--x;
		--y;
		A[x*n_oversized + y] = w;
		// A[y*n_oversized + x] = w;
	}

}


void fw_solve(int C[], int A[], int B[], int b, int n)
{
    for (int k = 0; k < b; ++k)
    {
        for (int i = 0; i < b; ++i)
        {
        	if(A[i*n + k] != INF)
        	{
	        	for(int j = 0; j < b; ++j)
	        	{
	        		if(B[k*n + j] != INF)
	        		{
			        	int temp = A[i*n + k] + B[k*n + j];
			            if (C[i*n + j] == INF || C[i*n + j] > temp)
			            {
					        C[i*n + j] = temp;
			            }
			        }
		        }
		    }
        }
    }
}


void fw_init(int input[], int n_oversized)
{
	for(int i=0;i<n_oversized;++i)
	{
		for(int j=0;j<n_oversized;++j)
		{
			if(i==j)
			{
				input[i*n_oversized + j] = 0;
			}
			else if(input[i*n_oversized + j] == 0)
			{
				input[i*n_oversized + j] = INF;
			}

		}
	}
	// return output;
}

void fw_block(int* output, int n, int b)
{
	int blocks = n/b;
	// printf("block = %d\n",blocks);

	for(int k=0;k<blocks;++k)
	{
		fw_solve(&output[k*b*n + k*b], &output[k*b*n + k*b], &output[k*b*n + k*b], b, n);
	
		for(int j=0;j<blocks;++j)
		{
			if(j==k)
			{
				continue;
			}

			fw_solve(&output[k*b*n + j*b], &output[k*b*n + k*b], &output[k*b*n + j*b], b, n);
		}

		for(int i=0;i<blocks;++i)
		{
			if(i==k)
			{
				continue;
			}
			
			fw_solve(&output[i*b*n + k*b], &output[i*b*n + k*b], &output[k*b*n + k*b], b, n);
			
			for(int j=0;j<blocks;++j)
			{
				if(j==k)
				{
					continue;
				}

				fw_solve(&output[i*b*n + j*b], &output[i*b*n + k*b], &output[k*b*n + j*b], b, n);

			}

		}

	}

}


void print_matrix(int mat[], int n_oversized, int n)
{
	FILE *fptr;
	fptr = fopen("./sample/Q2_test/t43", "w");
	register int i;
	register int j;

	for(i=0;i<n;++i)
	{
		for(j=0;j<n;++j)
		{
			fprintf(fptr,"%d ", mat[i*n_oversized+j]);
		}
		fprintf(fptr,"\n");
	}
	fclose(fptr);
}


int main()
{
	FILE *fptr;
	fptr = fopen("./sample/Q2/t43", "r");
	int v,e;
	fscanf(fptr,"%d %d", &v, &e);


	int n_oversized = v;
	int block_remainder = v % BS;
	if(block_remainder != 0)
	{
		n_oversized = v + BS - block_remainder;
	}

	int * restrict matrix = malloc(sizeof(int) * n_oversized * n_oversized);
	
	// take_input(matrix,e,n_oversized);

	register int i;
	int x;
	int y;
	int w;

	for(i=0;i<e;++i)
	{
		fscanf(fptr,"%d %d %d", &x, &y, &w);
		--x;
		--y;
		matrix[x*n_oversized + y] = w;
		// A[y*n_oversized + x] = w;
	}
	fclose(fptr);


	// print_matrix(matrix,n_oversized,v);
	// printf("\n");

	
	// int * output = nullptr;

	fw_init(matrix,n_oversized);
	// print_matrix(matrix,n_oversized,v);
	// printf("\n");



	// int n_blocked = v;
	// int block_remainder = v%BS;

	// if(block_remainder != 0)
	// {
	// 	n_blocked = v + block_size - block_remainder;
	// }

	// output = new int[n_blocked * n_blocked];

	fw_block(matrix, n_oversized, BS);

	print_matrix(matrix,n_oversized,v);

}