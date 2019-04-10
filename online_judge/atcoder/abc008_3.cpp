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
  int N, c[200];
  cin >> N;

  for (int i = 0; i < N; i++) cin >> c[i];

	sort(c, c + N);


  long long v = 0, a = 0;
  do {
    v++;
    vector<bool> sta(N, true);

    for (int i = 0; i < N-1; i++) {
      for (int j = i + 1; j < N; j++) {
        if (c[j] % c[i] == 0) {
          sta[j] = !sta[j];
        }
      }
    }

    for (bool b : sta) {
      a += b;
    }
  } while (std::next_permutation(c, c + N));

  printf("%.10f\n", (double)a / v);
}
