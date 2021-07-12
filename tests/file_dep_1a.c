#define max(x,y)    ((x) > (y) ? (x) : (y))

void dep_1(int k, int n)
{
 int *a;
#pragma scop
  int i;
    for (i = max(3,k); i < n; i++) {
        a[i] = a[i-1] + a[i-3] + a[i-k];
    }
#pragma endscop  
  return;
}

