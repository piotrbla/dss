void LMKernel6_01_Base(int loop, int n, int *input_w, int **input_b)
{
  int* a;// = get_vector_copy(input_w, n);
#pragma scop
  
  int j, i;
    for (i = 1; i < n; i++) {
      for (j = 0; j < i; j++) {
        a[i][j] = a[i-1][j]  + a[i][j-1];
      }
    }
#pragma endscop  
  return;
}

