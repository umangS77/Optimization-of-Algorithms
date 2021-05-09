#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define INF 1000000000
#define BS 8 // block_size

void take_input(int ** restrict matrix, register int e, register int v)
{
	int x;
	int y;
	int w;
	
	for(register int i=0;i<e;++i)
	{
		scanf("%d %d %d", &x, &y, &w);
		--x;
		--y;
		if(w < matrix[x][y])
			matrix[x][y] = w;

	}
}

void print_matrix(int **  mat, int v, int e)
{
	// FILE *fptr;
	// fptr = fopen("./sample/Q2_test/t29", "w");
	register int i;
	register int j;
	for(i=0;i<v;++i)
	{
		for(j=0;j<v;++j)
		{
			if(mat[i][j] < INF)
			{
				// fprintf(fptr,"%d ", mat[i][j]);
				printf("%d ",mat[i][j]);
			}
			else
			{
				// fprintf(fptr,"%d ", -1);
				printf("%d ", -1);
			}


		}
		// fprintf(fptr,"\n");
		printf("\n");
	}
	// fclose(fptr);
}

int ** fw_block(int ** restrict matrix,register int n)
{
    #pragma omp for
	for (register int k = 0; k < n; ++k) 
	{
		int * restrict C = *(matrix + k);
		for (register int i = 0; i < n; ++i) 
		{
			int * restrict B = *(matrix + i);
			if (*(B + k) != INF)
			{
				register int j;
				for (j=0;j<n-BS;j+=BS) 
				{
					register int val = *(B + k) + *(C + j);     
					if (val < *(B + j)) 
					{
						*(B + j) = val;
					}

					val = *(B + k) + *(C + j + 1);     
					if (val < *(B + j + 1)) 
					{
						*(B + j + 1) = val;
					}

					val = *(B + k) + *(C + j + 2);     
					if (val < *(B + j + 2)) 
					{
						*(B + j + 2) = val;
					}

					val = *(B + k) + *(C + j + 3);     
					if (val < *(B + j + 3)) 
					{
						*(B + j + 3) = val;
					}

					val = *(B + k) + *(C + j + 4);     
					if (val < *(B + j + 4)) 
					{
						*(B + j + 4) = val;
					}

					val = *(B + k) + *(C + j + 5);     
					if (val < *(B + j + 5)) 
					{
						*(B + j + 5) = val;
					}

					val = *(B + k) + *(C + j + 6);     
					if (val < *(B + j + 6)) 
					{
						*(B + j + 6) = val;
					}

					val = *(B + k) + *(C + j + 7);     
					if (val < *(B + j + 7)) 
					{
						*(B + j + 7) = val;
					}
				}
				for(;j<n;++j) 
				{
						register int val = *(B + k) + *(C + j);     
						if (*(B + j) == INF || val < *(B + j)) 
						{
							*(B + j) = val;
						}
				}
			}
		}
	}

	return matrix;
}

int main()
{

	// clock_t start, end;
 //    double cpu_time_used;
 //    start = clock();

	// FILE *fptr;
	// fptr = fopen("./sample/Q2/t29", "r");
	int v,e;
	// fscanf(fptr,"%d %d", &v, &e);
	scanf("%d %d",&v,&e);
	int ** restrict matrix = (int **)malloc(v * sizeof(int *));
	int ** restrict output;
	for(int i=0;i<v;i++)
	{
		matrix[i] = (int*)malloc(v * sizeof(int)); 
	}

	for(int i=0;i<v;++i)
	{
		for(int j=0;j<v;++j)
		{
			matrix[i][j] = INF;
		}
		matrix[i][i] = 0;
	}

	// int x;
	// int y;
	// int w;
	
	// for(register int i=0;i<e;++i)
	// {
	// 	fscanf(fptr,"%d %d %d", &x, &y, &w);
	// 	--x;
	// 	--y;
	// 	if(w < matrix[x][y])
	// 		matrix[x][y] = w;

	// }
	// fclose(fptr);

	take_input(matrix,e,v);

	output = fw_block(matrix,v);

	print_matrix(output,v,e);

	// end = clock();
 //    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	// printf("Time taken: %lf\n", cpu_time_used);

	return 0;

}
