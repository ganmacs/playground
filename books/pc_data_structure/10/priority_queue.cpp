#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define INF (1<<30)

int n = 0, ii = 0;
const int M = 20000000;
int A[M];

void max_heapify(int i)
{
  int left = i * 2;
  int right = (i * 2) + 1;
  int v = i;


  if (left <= n && A[left] > A[v]) v = left;
  if (right <= n && A[right] > A[v]) v = right;

  if (v != i) {
    swap(A[v], A[i]);
    max_heapify(v);
  }
}

void insert(int v)
{
  ii++;
  A[ii] = v;
  int j = ii;

  while (j > 1 && A[j] > A[j/2]) {
    swap(A[j], A[j/2]);
    j /= 2;
  }
}

int extract()
{
  if (ii < 1) return -INF;
  int max = A[1];
  A[1] = A[ii];
  ii--;
  max_heapify(1);
  return max;
}

int main()
{
  char cmd[10];
  int l;

  while (1) {
    scanf("%s", cmd);
    if (cmd[0] == 'e' && cmd[1] == 'n') break ;
    else if (cmd[0] == 'i') {
      n++;
      cin >> l;
      insert(l);
    } else {
      n--;
      printf("%d\n", extract());
    }
  }

  return 0;
}
