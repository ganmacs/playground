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

int N = 100004;


bool prime(int j)
{
  for (int i = 2; i * i <= j; i++) {
    if (j % i == 0) {
      return false;
    }
  }

  return true;
}

int main(int argc, char *argv[])
{
  int n;
  std::map<int, bool> r;

  cin >> n;
  bool p = false;
  for (int j = n; j < N; j++) {
    if (prime(j)) {
      cout << j << endl;
      return 0;
    }
  }

  return 0;
}
