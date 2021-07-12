#define max(x,y)    ((x) > (y) ? (x) : (y))

void dep_2(int k1, int k2, int n)
{
 int **a;
#pragma scop
    int i, j;
    for (i = max(2, k2); i < n; i++)
    {
        for (j = max(2, k1); i < n; i++)
        {
            a[i][j] = a[i][j - 1] + a[i][j - 2] + a[i][j - k1] + a[i - 2][j] + a[i - k2][j];
        }
    }
#pragma endscop  
  return;
}

