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
  int N;
  vector<int> V2;
  cin >> N;
  vector<pair<long long, long long >> V(N);

  for (int i = 0; i < N; i++) {
    cin >> V[i].first >> V[i].second;
    V2.push_back(i);
  }

  int n = 0;
  double total = 0.0;
  do {
    n++;
    for (int i = 1; i < N; i++) {
      total += sqrt((double)pow(V[V2[i]].first-V[V2[i-1]].first, 2) + (double)pow(V[V2[i]].second-V[V2[i-1]].second, 2));
    }
  } while (next_permutation(V2.begin(), V2.end()));

  printf("%.8f\n", total/n);
  return 0;
}
