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
#include <numeric>

using namespace std;

int main()
{
  string S;
  cin >> S;
  int N = S.size();
  vector<int> V(N, 0);

  for (int i = 0; i < N;) {
    int j = i;
    while (S[j] == 'R' && j < N) j++;
    int t = j-i;
    V[j-1] += t/2 + (t%2);
    V[j] += t/2;

    int k = j;
    while (S[k] == 'L' && j < N) k++;
    t = k-j;
    V[j-1] += t/2;
    V[j] += t/2 + (t%2);
    i = k;
  }

  for (auto& vi: V) {
    cout << vi << " ";
  }
  puts("");

  return 0;
}
