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
#include <numeric>

using namespace std;

int main()
{
  string S1, S2, S3;
  cin >> S1 >> S2 >> S3;
  map<char, int> M;
  for (auto& vi: S1) M[vi]++;
  for (auto& vi: S2) M[vi]++;
  for (auto& vi: S3) M[vi]++;

  if (M.size()>10 || S1 == S3 || S2 == S3) {
    puts("UNSOLVABLE");
    return 0;
  }

  vector<int> V;
  for (int i = 0; i < 10; i++) V.push_back(i);
  vector<char> C;
  for (auto& vi: M) C.push_back(vi.first);
  int N = C.size();

  do {
    string s1 = S1, s2 = S2, s3 = S3;
    for (int i = 0; i < N; i++) {
      replace(s1.begin(), s1.end(), C[i], (char)(V[i] + '0'));
      replace(s2.begin(), s2.end(), C[i], (char)(V[i] + '0'));
      replace(s3.begin(), s3.end(), C[i], (char)(V[i] + '0'));
    }
    if (s1[0] == '0' || s2[0] == '0' || s3[0] == '0') continue;
    long long n1 = stoll(s1), n2 = stoll(s2), n3 = stoll(s3);
    if (n1 + n2 == n3) {
      cout << n1 << endl;
      cout << n2 << endl;
      cout << n3 << endl;
      return 0;
    }
  } while (next_permutation(V.begin(), V.end()));

  puts("UNSOLVABLE");
  return 0;
}
