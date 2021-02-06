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
  int H, W;
  string C[101];
  cin >> H >> W;


  for (int i = 0; i < H; i++) {
    cin >> C[i];
  }

  for (int i = 0; i < H*2; i++) {
    cout << C[i/2]<< endl;
  }

  return 0;
}
