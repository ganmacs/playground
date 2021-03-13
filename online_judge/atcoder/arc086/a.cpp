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

bool cmp(pair<int, int>& a, pair<int, int>& b) {
  return a.second < b.second;
}

int main(int argc, char *argv[])
{

  map<int, int> ma;
  int N, K, a, k = 0;
  cin >> N >> K;

  for (int i = 0; i < N; i++) {
    cin >> a;
    ma[a]++;
  }
  vector<pair<int, int> > A;
  for (auto& it : ma) {
    A.push_back(it);
  }
  sort(A.begin(), A.end(), cmp);

  int div= ma.size();

  for (const auto ai: A) {
    if (div <= K) break;
    // std::cout << ai.first << " => " << ai.second << '\n';
    k += ai.second;
    div--;
  }


  // for (auto mi = ma.rbegin(); div > 0 && mi != ma.rend(); ++mi) {
  //   std::cout << mi->first << " => " << mi->second << '\n';
  // }
  // puts("\n===================================== start print");

  // for (auto mi = ma.begin(); div > K && mi != ma.end(); ++mi) {
  //   k += mi->second;
  //   div--;
  // }

  cout << k << endl;
  return 0;
}
