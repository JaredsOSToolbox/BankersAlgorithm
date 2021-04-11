//Safety algorithm
int safety(int A[][10],int N[][10],int AV[1][10],int n,int m,int a[]){
  int i, j, k, x = 0;
  int F[10], W[1][10];
  int pflag = 0, flag = 0;
  for (i = 0; i < n; i++) F[i] = 0;
  for (i = 0; i < m; i++) W[0][i] = AV[0][i];

  for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      if (F[i] == 0) {
        flag = 0;
        for (j = 0; j < m; j++) {
          if (N[i][j] > W[0][j]) flag = 1;
        }
        if (flag == 0 && F[i] == 0) {
          for (j = 0; j < m; j++) W[0][j] += A[i][j];
          F[i] = 1;
          pflag++;
          a[x++] = i;
        }
      }
    }
    if (pflag == n) return 1;
	}
	return 0;
}

bool safety(std::vector<std::vector<int>> A, std::vector<std::vector<int>> N,
            std::vector<std::vector<int>> AV, int n, int m, std::vector<int> )
