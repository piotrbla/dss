void dep_1(int k, int n)
{
 int *a;
#pragma scop
  int i;
    for (i = 3; i < n; i++) {
        a[i] = a[i-1] + a[i-3] + a[i-k];
    }
#pragma endscop  
  return;
}

