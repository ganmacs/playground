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
  int N, K;
  cin >> N >> K;
  vector<int> V(N);
  for (auto& vi: V) cin >> vi;
  K--;
  cout << ceil((double)(N-1)*1.0/K) << endl;
  return 0;
}
