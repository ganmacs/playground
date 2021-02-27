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

  long long unsigned int N;
  cin >> N;

  std::set<long long unsigned int> s;

  long long unsigned int n = N;


  for (long long unsigned int i = 2; (i * i) <= N; i++) {
    for (long long unsigned int k = i*i; k <= N; k *= i) {
      if (s.find(k) == s.end()) {
        s.insert(k);
        n--;
      }
    }
  }

  cout << n << endl;
  return 0;
}
