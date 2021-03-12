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

vector<int> s;

int main(int argc, char *argv[])
{
  int N, a = 0;
  long long ans = 0, aaa = 0;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> a;
    if (a % 10 == 0) {
      ans += a;
    } else {
      s.push_back(a);
      aaa += a;
    }
  }

  if (aaa % 10 != 0) {
    cout << (aaa + ans) << endl;
    return 0;
  } else if (s.empty()) {
    cout << 0 << endl;
    return 0;
  }

  sort(s.begin(), s.end());
  cout << ((aaa-s[0]) +  ans) << endl;
  return 0;
}
