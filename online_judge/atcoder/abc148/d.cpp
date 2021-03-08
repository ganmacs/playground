#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

long long int a[200001];
long long int b[200001];

int main(int argc, char *argv[])
{


  long long int N, k = 1;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
    b[i] = 0;
  }

  for (int i = 0; i < N; i++) {
    if (a[i] == k) {
      b[i + 1] = k;
      k++;
    } else {
      b[i + 1] = b[i];
    }
  }

  if (k == 1) {
    cout << -1 << endl;
  } else {
    cout << (N-(k-1)) << endl;
  }

  return 0;
}
