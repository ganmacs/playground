
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

  int H, W, h, w;
  cin >> H >> W;
  cin >> h >> w;

  cout << (H * W - (h*W + w*H - w*h)) << endl;
}
