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


int PQ[] = { 1, 2, 3, 4, 5, 6, 7, 8 };


int main(int argc, char *argv[])
{

  int N, P[8], Q[8];

  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> P[i];
  }

  for (int i = 0; i < N; i++) {
    cin >> Q[i];
  }


  int k = 1;
  int k1 = 0;
  int k2 = 0;

  do {
    if (std::equal(std::begin(PQ), PQ + N, std::begin(P))) {
      k1 = k;
    }

    if (std::equal(std::begin(PQ), PQ + N, std::begin(Q))) {
      k2 = k;
    }

    k++;
  } while(next_permutation(PQ,  PQ + N));


  cout << abs(k1-k2) << endl;
}
