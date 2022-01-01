void LMKernel6_01_Base(int loop, int n, int *input_w, int **input_b)
{
  int** b;// = get_full_copy(input_b, n);
  int* w;// = get_vector_copy(input_w, n);
#pragma scop
  
  for (int l = 1; l <= loop; l++) {
    for (int i = 1; i < n; i++) {
      for (int k = 0; k < i; k++) {
        w[i] += b[k][i] * w[(i - k) - 1];
      }
    }
  }
#pragma endscop  
  return;
}

