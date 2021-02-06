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

long long int NN = 1000003;

int main(int argc, char *argv[])
{

  long long int N, Q;
  string s;
  long long int MM[NN];
  cin >> N >> Q;
  cin >> s;

  for (int i = 0; i < N; i++) {
    MM[i] = 0;
  }

  for (int i = 1; i < s.length(); i++) {
    if (s[i-1] == 'A' && s[i] == 'C') {
      MM[i] = MM[i-1] + 1;
    } else {
      MM[i] = MM[i-1];
    }
  }

  long  int l, r;
  for (int i = 0; i < Q; i++) {
    cin >> l >> r;
    auto v = MM[r-1] - MM[l-1];

    // if (l > 1 && (MM[l-1] != MM[l-2]) && MM[l-1] >= 1 && v != 0) {
    //   v--;
    // }

    cout << v << endl;
  }

  return 0;
}
