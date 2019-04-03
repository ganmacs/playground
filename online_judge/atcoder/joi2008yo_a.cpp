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
  int ans = 0, in;
  cin >> in;
  in = 1000-in;


  ans += (in / 500);
  in %= 500;

  ans += (in / 100);
  in %= 100;

  ans += (in / 50);
  in %= 50;

  ans += (in / 10);
  in %= 10;

  ans += (in / 5);
  in %= 5;

  ans += in;
  cout << ans << endl;
}
