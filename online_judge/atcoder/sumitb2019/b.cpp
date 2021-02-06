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
  int N;
  int K = 108;
  cin >> N;

  int v = (N*100) / 108;


  for (int i = max(v-5, 1); i < v + 5; i++) {
    if ( floor(i * 1.08) == N) {
      cout << i << endl;
      return 0;
    }
  }

  cout << ":(" << endl;

  return 0;
}
