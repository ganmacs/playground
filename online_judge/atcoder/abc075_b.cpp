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

int mm[8][2] = { {0, 1}, {0, -1}, {1, 1}, {1, 0}, {1, -1}, {-1, 1}, {-1, 0}, {-1, -1} };

int main(int argc, char *argv[])
{
  int H, W;
  vector<string> ss;

  cin >> H >> W;

  for (int i = 0; i < H; i++) {
    string s;
    cin >> s;
    ss.push_back(s);
  }

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (ss[i][j] == '#') {
        cout << '#';
      } else {
        int ans = 0;
        for (int k = 0; k < 8; k++) {
          if ((j + mm[k][0] >= 0) && (j + mm[k][0] < W) && (i + mm[k][1] >= 0) && (i + mm[k][1] < H)) {
            if (ss[i + mm[k][1]][j + mm[k][0]] == '#') {
              ans++;
            }
          }
        }
        cout << ans;
      }
    }
    cout << endl;
  }

  return 0;
}
