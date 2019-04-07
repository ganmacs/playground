#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
  char s[4][4];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cin >> s[i][j];
    }
  }

  for (int i = 3; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      cout << s[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
