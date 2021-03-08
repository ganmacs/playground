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

int NN = 100005;

int P[10], Q[10], S[10];

int main(int argc, char *argv[])
{

  int N, num = 0;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> P[i];
    S[i] = P[i];
  }

  for (int i = 0; i < N; i++) {
    cin >> Q[i];
  }

  sort(S, S + N);
  int k1;
  int k2;

  do {
    num++;

    if (std::equal(std::begin(S), S + N, std::begin(P))) {
      k1 = num;
    }

    if (equal(std::begin(S), S + N, std::begin(Q))) {
      k2 = num;
    }
  } while (next_permutation(S, S + N));

  cout << abs(k1-k2) << endl;
  return 0;
}
