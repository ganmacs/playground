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


int A[200001];
int B[200001];

int a(int v) {
  int ans = 0;

  for (int i = 1; i <= v; i++) {
    if (v%i == 0) {
      ans++;
    }
  }
  return ans;
}

int main(int argc, char *argv[])
{
  int N;
  cin >> N;

  if (N == 105) {
    cout << 1 << endl;
    return 0;
  } else if (N < 105) {
    cout << 0 << endl;
    return 0;
  }

  auto ans = 1;


  for (int i = 107; i <= N; i += 2) {
    if(a(i) == 8) {
      ans++;
    }
  }


    cout << ans << endl;

  return 0;
}
