#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
static const int MAX = 1000;

int main(){
  long long int N, M, a;
  long long int V[MAX];
  long long int AA[MAX*MAX], cnt = 0;

  cin >> N >> M;
  while (!(N == 0 && M == 0)) {
    V[0] = 0;
    for (int i = 1; i <= N; i++) cin >> V[i];

    cnt = 0;
    for (int i = 0; i <= N; i++) {
      for (int j = i; j <= N; j++) {
        if (V[i] + V[j] <= M)
          AA[cnt++] = V[i] + V[j];
      }
    }
    sort(AA, AA + cnt, less<int>());

    a = 0;
    for (int i = 0; i < cnt; i++) {
      a = max(a, *(upper_bound(AA, AA + cnt, M-AA[i])-1) + AA[i]);
    }
    cout << a << endl;

    cin >> N >> M;
  }
}
