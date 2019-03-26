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

string S;
int len;
long long ans = 0;

int diff[4][2] = { {1, 0}, {-1, 0}, {0, 1},  {0, -1} };

int main(int argc, char *argv[])
{
  int N;
  cin >> N;

  int t, x, y;
  queue<pair<int, int> > que1, que2;
  que1.push(make_pair(0, 0));

  int j = 0;
  for (int i = 0; i < N; i++) {
    cin >> t >> x >> y;

    pair<int, int> item;
    for (; j < t; j++) {
      while (!que1.empty()) {
        item = que1.front();
        que1.pop();

        for (int k = 0; k < 4; k++) {
          if ((item.first + diff[k][0] >= 0) && (item.first + diff[k][0] <= 100000) &&
              (item.second + diff[k][1] >= 0) && (item.second + diff[k][1] <= 100000)) {
            que2.push(make_pair(item.first + diff[k][0], item.second + diff[k][1]));
          }
        }
      }

      while (!que2.empty()) {
        que1.push(que2.front());
        que2.pop();
      }
    }

    bool ok = false;
    while (!que1.empty()) {
      item = que1.front();
      que1.pop();

      if (item.first == x && item.second == y) {
        ok = true;
        break;
      }

      que2.push(item);
    }

    if (!ok) {
      i++;
      for (; i < N; i++) {
        cin >> t >> x >> y;
      }
      puts("No");
      return 0;
    }

    while (!que2.empty()) {
      que1.push(que2.front());
      que2.pop();
    }
  }

  puts("Yes");
}
