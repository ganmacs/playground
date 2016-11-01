#include <iostream>
#include <cstdlib>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
  stack<int> s, r;
  stack<pair<int, int> > s2;
  char c;
  int i, j, k, sum = 0, t;

  for (i = 0; cin >> c; i++) {
    if (c == '\\') {
      s.push(i);
    }
    else if (c == '/' && s.size() > 0) {
      j = s.top();
      s.pop();
      t = i - j;
      sum += t;
      while (s2.size() > 0 && s2.top().first > j) {
        t += s2.top().second;
        s2.pop();
      }
      s2.push(make_pair(j, t));
    }
  }

  cout << sum << endl;

  for (k = 0; s2.size() > 0; k++, s2.pop()) {
    r.push(s2.top().second);
  }
  cout << k;

  for (; r.size() > 0; r.pop()) {
    cout << ' ' << r.top();
  }
  cout << endl;
  return 0;
}
