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

string H[102];


int main()
{
  int H, W;
  string l;

  cin >> H >> W;

  for (int i = 0; i < W + 2; i++) {
    cout << "#";
  }

  puts("");

  for (int i = 0; i < H; i++) {
    cin >> l;
    cout << "#" << l << "#" << endl;;
  }

  for (int i = 0; i < W + 2; i++) {
    cout << "#";
  }
  puts("");

  return 0;
}
