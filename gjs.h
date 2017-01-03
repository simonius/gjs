#define MAT_TYPE float

int main();
void fill_mat(MAT_TYPE *mat, int n);
void e_mat(MAT_TYPE *mat, int n);
int malloc_mat(MAT_TYPE **mat, MAT_TYPE ***rows, int n);
void print_mat(MAT_TYPE **mat, int n);

void gja(MAT_TYPE *A, MAT_TYPE **A_rows, MAT_TYPE *B, MAT_TYPE **B_rows, int n);
void pivot(MAT_TYPE **A_rows, MAT_TYPE **B_rows, int subrows, int n);
void mult_row(MAT_TYPE *row, MAT_TYPE f, int n);
void add_row(MAT_TYPE *A_row, MAT_TYPE *B_row, MAT_TYPE f, int n);
void swap_f(MAT_TYPE **A_rows, int i, int j);
void save_binary(char *filename, MAT_TYPE **rows, int n);
