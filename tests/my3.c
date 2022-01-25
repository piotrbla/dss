#include <stdlib.h>

int main()
{
    int n;
    int a[n][n];

#pragma scop
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 2; j <= n; j++)
        {
            a[i][j] = a[i][j - 2];
        }
    }
#pragma endscop

    return 0;
}
