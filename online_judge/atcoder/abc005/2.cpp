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
  int N, c[299];
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> c[i];
  }

  sort(c, c + N);

  cout << c[0] << endl;
  return 0;
}
