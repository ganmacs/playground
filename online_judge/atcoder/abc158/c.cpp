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


// int A[200001];
// int B[200001];


int main(int argc, char *argv[])
{

  int A, B;
  cin >> A >> B;
  // X = A * (100/8)
  // X = B * 10

  auto a = A * (100/8);
  auto b = B * 10;

  if (a > b) {
    swap(a, b);
  }

  b += 1;
  a -= 1;

  for (int i = min(a-10, 0); i <= 1000; i++) {
    if ((i * 8/ 100 == A) &&  (i * 10/100 == B)) {
      cout << i << endl;
      return 0;
    }
  }

  cout << -1 << endl;

  return 0;
}
