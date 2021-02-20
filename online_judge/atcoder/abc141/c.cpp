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

long long int KK[123456];

int main(int argc, char *argv[])
{
  int N, K, Q;
  cin >> N >> K >> Q;
  int v;

  for (int i = 0; i < N; i++) {
    KK[i] = K-Q;
  }

  for (int i = 0; i < Q; i++) {
    cin >> v;
    KK[v-1]++;
  }

  for (int i = 0; i < N; i++) {
    cout << (KK[i] > 0 ? "Yes" : "No") << endl;
  }

  return 0;
}
