int sigma(int a, int b)
{
	return a>b;
}

void LMKernel6_01_Base(int n, int **S)
{

#pragma scop
  for (int c0 = 1; c0 < n; c0 += 1)
  {
    for (int c1 = 0; c1 < n - c0; c1 += 1)
    {
      for (int c2 = c0 + c1; c2 < min(n, 2 * c0 + c1); c2 += 1)
      {
        if (2 * c0 + c1 >= c2 + 2)
	{
	  S[c1][c2] = max(S[c1][-c0 + c2] + S[-c0 + c2 + 1][c2], S[c1][c2]); // s1
	  if (c2 == c0 + c1){
		S[c1][c2] = max(S[c1][c2], S[c1 + 1][c2 - 1] + sigma(c1, c2)); //s2
	  }
	}
	S[c1][c2] = max(S[c1][c0 + c1 - 1] + S[c0 + c1 - 1 + 1][c2], S[c1][c2]); // s1
	if (c2 == c0 + c1)
	{
		S[c1][c2] = max(S[c1][c2], S[c1 + 1][c2 - 1] + sigma(c1, c2)); //s2
	}
    }
  }
}
#pragma endscop  

  return;
}

