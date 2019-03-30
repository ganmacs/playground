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

int main(int argc, char *argv[])
{
  int N, r = 0,  b = 0;
  string s;
  cin >> N;
  cin >> s;

  for (int i = 0; i < N; i++) {
    if (s[i] == 'R') {
      r++;
    } else {
      b++;
    }
  }

  if (r > b) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}
