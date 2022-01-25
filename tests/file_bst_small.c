void computeSEQ0(int* p, int n)
{
  int** w, **c ;//= allocateMatrix(n + 1);
#pragma scop
  for (int i=n-1 ; i>=1 ; i--)
  for (int j = i+1 ; j<=n ; j+= 1)
    for (int k = i+1 ; k<j; k += 1) {
      c[i][j] = min(c[i][j], w[i][j]+c[i][k]+c[k][j]);
    }
#pragma endscop
}



