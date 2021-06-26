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
#include <deque>

using namespace std;

int main()
{
  std::deque<int> deq;
  string S;
  cin >> S;

  for (auto& vi: S) {
    if (deq.empty()) {
      deq.push_back(vi);
    } else if (deq.back() == 'S' && vi == 'T') {
      deq.pop_back();
    } else {
      deq.push_back(vi);
    }
  }

  printf("%ld\n", deq.size());
  return 0;
}
