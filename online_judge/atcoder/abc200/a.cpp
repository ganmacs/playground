#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  int N;
  cin >> N;

  if (N % 100 == 0) {

    cout << (N/100) << endl;
  } else {
    cout << (N/100) + 1 << endl;
  }

  return 0;
}
