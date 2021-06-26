#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;


void f(bool b) {
  if (b) {
    puts("Yes");
  } else {
    puts("No");
  }
}

int main()
{
  int N, a;
  cin >> N;
  map<int, int> M;

  for (int i = 0; i < N; i++) {
    cin >> a;
    M[a]++;
  }

  vector<int> V;
  for (auto& vi: M) V.push_back(vi.first);

  if (V.size() > 3) {
    puts("No");
  } else if (V.size() == 1) {
    f(V[0] == 0);
  } else if (V.size() == 2) {
    f(M[0] == N/3);
  } else if (V.size() == 3) {
    if ((V[0] ^ V[2]) == V[1]) {
      f((M[V[0]] == M[V[1]] && M[V[0]] == M[V[2]]));
    } else {
      puts("No");
    }
  }

  return 0;
}
