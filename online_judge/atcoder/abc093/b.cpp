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


int X[30][30];

int main(int argc, char *argv[])
{
  long long int A, B, K;
  cin >> A >> B >> K;

  if ((abs(A - B) + 1)< K*2) {
    for (int i = A; i <= B ; i++) {
      cout << i << endl;
    }
    return 0;
  }

  for (int i = A; i < A + K; i++) {
    cout << i << endl;
  }

  for (int i = B-K + 1; i < B + 1; i++) {
    cout << i << endl;
  }

  return 0;
}
