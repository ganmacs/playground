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

  long long unsigned int H;
  cin >> H;

  long long unsigned int jj = 0;
  long long unsigned int i = 1;

  for (; i <= pow(2, 41); i <<= 1) {
    if (H < i) {
      break;
    }
    jj += i;
  }

  cout << jj << endl;

  return 0;
}
