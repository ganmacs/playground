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

int N[3][3];

int main(int argc, char *argv[])
{
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> N[i][j];
    }
    N[i][0] -= N[i][2];
    N[i][1] -= N[i][2];
  }

  for (int i = 0; i < 2; i++) {
    if (!(N[0][i] == N[1][i] && N[1][i] == N[2][i])) {
      puts("No");
      return 0;
    }
  }

  puts("Yes");
}
