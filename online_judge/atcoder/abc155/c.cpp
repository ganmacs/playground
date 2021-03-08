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

string S[212345];

bool cmp(const pair<string, long long int>& a, const pair<string, long long int>& b) {
  return a.second > b.second;
}

int main(int argc, char *argv[])
{
  map<string, long long int> SSS;
  long long int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> S[i];
    auto it = SSS.find(S[i]);
    if( it != SSS.end() ) {
      SSS[S[i]]++;
    } else {
      SSS[S[i]] = 1;
    }
  }

  vector<pair<string, long long int> > A;
  for (auto& it : SSS) {
    A.push_back(it);
  }

  sort(A.begin(), A.end(), cmp);
  long long int k = -1;
  vector<string> A1;
  for (auto ai: A) {
    if (k == -1) {
      k = ai.second;
    } else if (k != ai.second) {
      break;
    }

    A1.push_back(ai.first);
  }
  sort(A.begin(), A.end());


  for (auto a: A) {
    cout << a << endl;
  }

  return 0;
}
