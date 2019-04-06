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
  int X, Y, Z, K;
  vector<long long> a, b, c;
  long ans[3003];
  cin >> X >> Y >> Z >> K;

  long long v;
  for (int i = 0; i < X; i++) {
    cin >> v;
    a.push_back(v);
  }
  for (int i = 0; i < Y; i++) {
    cin >> v;
    b.push_back(v);
  }
  for (int i = 0; i < Z; i++) {
    cin >> v;
    c.push_back(v);
  }

  int size = min(3000, X*Y*Z);
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  sort(c.begin(), c.end());

  long aa = a.back();
  a.pop_back();

  long bb = b.back();
  b.pop_back();

  long cc = c.back();
  c.pop_back();

  for (int i = 0; i < size; i++) {
    if (aa >= bb &&  aa >= cc) {
      ans[i] = aa + bb + cc;
      aa = a.back();
      a.pop_back();
      ans[i] = aa + bb + cc;

      if (bb >= cc) {
      } else {
        i++;
        ans[i] = aa + bb + cc;

      }

    } else if (bb >= aa &&  bb >= cc) {
    } else {
    }
  }

}
