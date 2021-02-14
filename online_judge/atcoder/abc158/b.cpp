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
  long long unsigned int N, A, B;
  cin >> N >> A >> B;


  auto ab = A + B;

  long long unsigned int n = N/ab;
  long long unsigned int r = N % ab;


  cout << min(r, A) + n*A << endl;

  return 0;
}
