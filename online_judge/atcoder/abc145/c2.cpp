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

int main()
{
  int N, a, b;
  vector<int> V;
  vector<pair<int, int>> P;

  cin >> N;
  for (int i = 0; i < N; i++) {
    V.push_back(i);
    cin >> a >> b;
    P.push_back(make_pair(a, b));
  }

  int nn = 0;
  double sum = 0.0;
  bool f = true;
  do {
    int x = P[V[0]].first, y = P[V[0]].second;
    for (int i = 1; i < V.size(); i++) {
      int xx = P[V[i]].first;
      int yy = P[V[i]].second;
      sum += sqrt(pow(x - xx, 2) + pow(y - yy, 2));
      x = xx;
      y = yy;
    };
    nn++;
  } while (std::next_permutation(V.begin(), V.end()));

  printf("%08f\n", sum/nn);

  return 0;
}
