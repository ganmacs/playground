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

// int A[1000];

int main(int argc, char *argv[])
{
  int N;
  vector<pair<int, int> > v;
  vector<int> k;

  cin >> N;
  int a, b;
  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    v.push_back(make_pair(a, b));
    k.push_back(i);
  }



  double sum = 0.0;
  int sss = 0;

  do {
    int x = -11111;
    int y = 0;

    for (int ki: k) {

      if (x != -11111) {
        sum += sqrt(pow(x-v[ki].first, 2) + pow(y-v[ki].second, 2));
      }

      x = v[ki].first;
      y = v[ki].second;
    }

    sss++;
  } while (std::next_permutation(k.begin(), k.end()));

  printf("%0.7f\n", sum/sss);
  return 0;
}
