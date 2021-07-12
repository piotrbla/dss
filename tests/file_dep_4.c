#define max(x,y)    ((x) > (y) ? (x) : (y))
#define min(x,y)    ((x) < (y) ? (x) : (y))

void dep_3(int k1, int k2, int n)
{
    int **a;
#pragma scop
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < min(i-k1, j-k2); k++)
            {

                a[i][j] = a[i - k - k1][j] + a[i][j - k - k2];
            }
        }
    }
#pragma endscop
    return;
}
