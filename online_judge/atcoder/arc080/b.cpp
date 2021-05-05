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
#include <numeric>

using namespace std;

int main()
{
  int H, W, N;
  cin >> H >> W >> N;

  vector<int> V;
  int a;

  for (int i = 0; i < N; i++) {
    cin >> a;
    for (int j = 0; j < a; j++) {
      V.push_back(i + 1);
    }
  }

  for (int i = 0; i < H;) {
    for (int j = 0; j < W; j++) {
      cout << V[(W*i) + j] << " ";
    }
    puts("");
    i++;

    if (i < H) {
      for (int j = W-1; j >= 0; j--) {
        cout << V[(W*i) + j] << " ";
      }
      puts("");
    }
    i++;
  }

  return 0;
}
