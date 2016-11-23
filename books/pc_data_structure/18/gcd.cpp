#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
int n;

int gcd(int x, int y)
{
  int r;
  if (x < y) swap(x, y);

  while (y > 0) {
    r = x % y;
    x = y;
    y = r;
  }

  return x;
}

int main(){
  int x, y;

  cin >> x >> y;
  cout << gcd(x, y) << endl;
}
