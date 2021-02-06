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

int main(int argc, char *argv[])
{
  int A, B;
  cin >> A >> B;

  if (B == 1) {
    cout << 0 << endl;
    return 0;
  }

  auto c = B - A;
  int r = 1;


  if (c > 0) {
    for (int i = 0; i < 22; i++) {
      c -= (A-1);
      r++;

      if (c <= 0) {
        break;
      }
    }
  }

  cout << r << endl;
}
