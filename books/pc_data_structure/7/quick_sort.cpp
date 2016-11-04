#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct card_t {
  char suit;
  int n;
} card_t;

#define M 100000
#define SEN 2000000000;
card_t v[M], v2[M], L[M/2 + 2], R[M/2 + 2];
int n;

void merge(card_t c[], int l, int r, int m)
{
  int i;
  int ln = m - l;
  int rn = r - m;

  for (i = 0; i <= ln; i++) L[i] = c[l + i];
  L[ln + 1].n = SEN;

  for (i = 1; i <= rn; i++) R[i - 1] = c[m + i];
  R[rn].n = SEN;

  int rk = 0, lk = 0;
  for (i = l; i <= r; i++) {
    if (L[lk].n <= R[rk].n) {
      c[i] = L[lk++];
    } else {
      c[i] = R[rk++];
    }
  }
}

void merge_sort(card_t c[], int l, int r)
{
  if (l < r) {
    int mid = (l + r) / 2;
    merge_sort(c, l, mid);
    merge_sort(c, mid + 1, r);
    merge(c, l, r, mid);
  }
}

int partition(card_t c[], int l, int r)
{
  int pi = l - 1;
  int i = l;
  int t = c[r].n;

  for (; i < r; i++) {
    if (c[i].n <= t) {
      pi++;
      swap(c[pi], c[i]);
    }
  }

  swap(c[pi + 1], c[r]);
  return pi + 1;
}

void pp(card_t c[])
{
  for (int i = 0; i < n; i++) {
    cout << c[i].suit << ' ' << c[i].n << endl;
  }
}

void quick_sort(card_t c[], int l, int r)
{
  if (r > l) {
    int t = partition(c, l, r);
    quick_sort(c, l, t - 1);
    quick_sort(c, t + 1, r);
  }
}

int main(int argc, char *argv[])
{
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    cin >> v[i].suit >> v[i].n;
    v2[i].n = v[i].n;
    v2[i].suit = v[i].suit;
  }

  quick_sort(v, 0, n - 1);
  merge_sort(v2, 0, n-1);

  int j = 1;

  for (int i = 0; i < n; i++) {
    if (v[i].suit != v2[i].suit) j = 0;
  }

  if (j) { cout << "Stable" << endl; }
  else { cout << "Not stable" << endl; }

  pp(v);

  return 0;
}
