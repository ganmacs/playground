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
  long long int A, B, C;
  long long unsigned int K, l, c, r;
  cin >> A >> B >> C >> K;

  long long int a;

  if (K % 2 == 0) {
    a = A-B;
  } else {
    a = B-A;
  }


  cout << a << endl;
  return 0;
}
