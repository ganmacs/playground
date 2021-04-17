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

int
main()
{
  string S;
  int Q;
  cin >> S >> Q;
  int t, b = 0;
  string c;

  string ll, rr;

  for (int i = 0; i < Q; i++) {
    cin >> t;
    if (t == 1) {
      b = (b + 1) % 2;
    } else {
      cin >> t >> c;
      if (b % 2 == 0) {
        if (t == 1) {
          ll = c + ll;
        } else {
          rr = rr + c;
        }
      } else {
        if (t == 1) {
          rr = rr + c;
        } else {
          ll = c + ll;
        }
      }
    }
  }


  if (b % 2 == 1) {
    reverse(rr.begin(), rr.end());
    reverse(ll.begin(), ll.end());
    reverse(S.begin(), S.end());
    cout << rr << S << ll << endl;
  } else {
    cout << ll << S << rr << endl;
  }

  return 0;
}
