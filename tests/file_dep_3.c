#define max(x,y)    ((x) > (y) ? (x) : (y))

void dep_3(int k1, int k2, int k3, int n)
{
    int ***a;
#pragma scop
    int i, j, k;
    for (i = max(0, k1); i < n; i++)
    {
        for (j = max(0, k2); j < n; j++)
        {
            for (k = max(0, k3); k < n; k++)
            {

                a[i][j][k] = a[i - k1][j][k] + a[i][j - k2][j] + a[i][j][k - k3];
            }
        }
    }
#pragma endscop
    return;
}
