#include "gjs.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
	int i, n, magic;
	MAT_TYPE f;
	FILE *fp;
	if(argc < 2)
		return printf("no filename"), -1;
	fp = fopen(argv[1], "r");
	if(fp == NULL)
		return printf("can't open"), -2;
	fread(&magic, sizeof(int), 1, fp);
	if(magic != 1701)
		return printf("not a matrix file"), -3;

	fread(&n, sizeof(int), 1, fp);
	for (i = 0; i < n*n; i++) {
		fread(&f, sizeof(MAT_TYPE), 1, fp);
		printf("%f ", (float) f);
		if (i%n == n-1)
			printf("\n");
	}
}
