#include "gjs.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
		return printf("no matrix size"), -1;

	int n = atoi(argv[1]);
	MAT_TYPE *A, **A_rows, *B, **B_rows;
	malloc_mat(&B, &B_rows, n);
	malloc_mat(&A, &A_rows, n);
	e_mat(B, n);
	fill_mat(A, n);

	gja(A, A_rows, B, B_rows, n);

	if(argc > 2)
		save_binary(argv[2], B_rows, n);
}


int malloc_mat(MAT_TYPE **mat, MAT_TYPE ***rows, int n)
{
	int i;
	*mat = malloc(n*sizeof(MAT_TYPE)*n);
	*rows = malloc(n*sizeof(MAT_TYPE*));
	for(i=0; i < n; i++){
		*(*rows+i) = *mat+i*n;
	}
}

void e_mat(MAT_TYPE *mat, int n)
{
	int i;
	for (i = 0;i < n; i++)
		*(mat+i*n+i) = 1;

}

void fill_mat(MAT_TYPE *mat, int n)
{
	int i;
	for (i = 0; i < n*n; i++)
		mat[i] = 1;
	for (i = 0;i < n; i++)
		*(mat+i*n+i) = i+1;
}

void print_row(MAT_TYPE *row, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%f  ", *(row+i));
	printf("\n");
}

void print_mat(MAT_TYPE **rows, int n)
{
	int i;
	for (i = 0; i < n; i++)
		print_row(*(rows+i), n);
	printf("\n");
}

void gja(MAT_TYPE *A, MAT_TYPE **A_rows, MAT_TYPE *B, MAT_TYPE **B_rows, int n)
{
	int i, subrow;
	float row_f;
	for (subrow = 0; subrow < n; subrow++){

		pivot(A_rows, B_rows, subrow, n);
		row_f = 1.0/(*(*(A_rows+subrow)+subrow));
		mult_row(*(A_rows+subrow), row_f, n);
		mult_row(*(B_rows+subrow), row_f, n);
		for (i = subrow + 1; i < n; i++){
			row_f = -*(A_rows[i]+subrow);
			add_row(*(A_rows+i), *(A_rows+subrow), row_f, n);
			add_row(*(B_rows+i), *(B_rows+subrow), row_f, n);
		}
	}

	for(subrow = n - 1;subrow > 0; subrow--){
		for (i = 0; i < subrow; i++){
			row_f = -*(*(A_rows+i)+subrow);
			add_row(*(A_rows+i), *(A_rows+subrow), row_f, n);
			add_row(*(B_rows+i), *(B_rows+subrow), row_f, n);
		}
	}

}

void pivot(MAT_TYPE **A_rows, MAT_TYPE **B_rows, int subrow, int n)
{
	int i;
	for (i = subrow; i < n; i++)
		if(*(*(A_rows+i)+subrow)!=0){
			swap_f(A_rows, subrow, i);
			swap_f(B_rows, subrow, i);
			return;
		}
}

void mult_row(MAT_TYPE *row, MAT_TYPE f,int n)
{
	int i;
	for (i = 0; i < n; i++)
		*(row+i) = *(row+i)*f;
}

void add_row(MAT_TYPE *A_row, MAT_TYPE *B_row, MAT_TYPE f, int n)
{
	int i;
	for (i = 0; i < n; i++)
		A_row[i] = A_row[i] + B_row[i] * f;
}

void swap_f(MAT_TYPE **A_rows, int i, int j)
{
	MAT_TYPE *t = A_rows[i];
	A_rows[i] = A_rows[j];
	A_rows[j] = t;
	return;
}


void save_binary(char *filename, MAT_TYPE **rows, int n)
{
	FILE *fp;
	int i, magic=1701;
	fp = fopen(filename, "w");
	if(fp == NULL)
		return (void) printf("open failed :( !");

	fwrite(&magic, sizeof(int), 1, fp);
	fwrite(&n, sizeof(int),1, fp);
	for(i = 0; i<n; i++)
		fwrite(*(rows+i), sizeof(MAT_TYPE)*n, 1, fp);
	fclose(fp);
	return;
}
