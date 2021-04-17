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
  unsigned long long int ans = 0;
  string S;
  vector<string> V;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> S;
    sort(S.begin(), S.end());
    V.push_back(S);
  }

  sort(V.begin(), V.end());

  for (int i = 0; i < N;) {
    int j = i;
    while (j < N && V[i] == V[j]) {
      ans += (j-i);
      j++;
    }
    i = j;
  }

  cout << ans << endl;

  return 0;
}
