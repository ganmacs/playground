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

int main()
{
  int X, Y, A, B, C;
  cin >> X >> Y >> A >> B >> C;
  vector<long long> P(A), Q(B), R(C);
  for (auto& vi: P) cin >> vi;
  for (auto& vi: Q) cin >> vi;
  for (auto& vi: R) cin >> vi;
  sort(P.begin(), P.end(), greater<long long>());
  sort(Q.begin(), Q.end(), greater<long long>());
  sort(R.begin(), R.end(), greater<long long>());

  vector<long long> PQ;
  for (int i = 0; i < X; i++) PQ.push_back(P[i]);
  for (int i = 0; i < Y; i++) PQ.push_back(Q[i]);
  sort(PQ.begin(), PQ.end(), greater<long long>());

  vector<long long> PQS(X + Y + 2);
  PQS[0] = 0;
  for (int i = 0; i < X + Y; i++) {
    PQS[i + 1] = PQ[i] + PQS[i];
  }

  vector<long long> RS(C + 2);
  RS[0] = 0;
  for (int i = 0; i < C; i++) {
    RS[i + 1] = R[i] + RS[i];
  }

  long long ans = 0;
  for (int i = 0; i <= min(C, X + Y); i++) {
    ans = max(ans, PQS[X + Y - i] + RS[i]);
  }

  cout << ans << endl;
  return 0;
}
