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
  for (int i = 0; i < N; i++) {
    cin >> V[i];
  }
  cout << ceil((double)(N-1)/(double)(K-1)) << endl;
  return 0;
}
