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
  int N;
  set<string> SS;
  string S;
  cin >> N >> S;

  string t = "000";
  for (char i = '0'; i <= '9'; i++) {
    t[0] = i;
    for (int j = '0'; j <= '9'; j++) {
      t[1] = j;
      for (int k = '0'; k <= '9'; k++) {
        t[2] = k;

        int l = 0;
        bool found = false;
        for (auto& vi: t) {
          found = false;
          while (l < N) {
            if (vi == S[l]) {
              found = true;
              l++;
              break;
            }
            l++;
          }
          if (!found) break;
        }

        if (found) {
          SS.insert(t);
        }
      }
    }
  }

  cout << SS.size() << endl;
  return 0;
}
