void computeDYN1Imperfect(int** table, int n, int *seq) {
  int** S;// = getFullCopy(table, n);

#pragma scop
  for (int i = n - 1; i >= 0; i--) {
    for (int j = i + 1; j < n; j++) {
      for (int k = i; k < j; k++) {
        S[i][j] = max_score(S[i][k] + S[k+1][j], S[i][j]); // s1
    	if (k==j-1)
	{  
      		S[i][j] = max_score(S[i][j], S[i+1][j-1] + sigma(i, j)); // s2
	}
      }
    }
  }
#pragma endscop
}

