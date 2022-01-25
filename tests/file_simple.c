void LMKernel6_01_Base(int loop, int n, int *w, int **a)
{
#pragma scop
  
  int j, i;
    for (i = 1; i < n; i++) {
      for (j = 1; j < n; j++) {
        a[i][j] = a[i-1][j]  + a[i][j-1];
      }
    }
#pragma endscop  
  return;
}

