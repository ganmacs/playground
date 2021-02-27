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

long long int KK[123456];

int main(int argc, char *argv[])
{
  int N, M, a, b;

  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    KK[i] = 0;
  }

  for (int i = 0; i < M; i++) {
    cin >> a >> b;
    KK[a-1]++;
    KK[b-1]++;
  }


  for (int i = 0; i < N; i++) {
    cout << KK[i] << endl;
  }

  return 0;
}
