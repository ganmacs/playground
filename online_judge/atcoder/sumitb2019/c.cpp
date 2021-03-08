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

int NN = 200;
long long N;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main(int argc, char *argv[])
{
  cin >> N;

  int l = N/100 + 1;
  rep(a, l) {
    rep(b, l) {
      rep(c, l) {
        rep(d, l) {
          rep(e, l) {
            rep(f, l) {
              if (a*100 + b*101 + c*102 + d*103 + e*104 + f*105 == N) {
                cout << 1 << endl;
                return 0;
              }
            }
          }
        }
      }
    }
  }

  cout << 0 << endl;
  return 0;
}
