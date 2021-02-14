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

int NN = 1000001;

int
main()
{
  int N;
  int A[NN];
  priority_queue<double, vector<double>, greater<double> > q;

  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> A[i];
    q.push(A[i]);
  }

  while (q.size() >= 2) {
    auto a = q.top();q.pop();
    auto b = q.top();q.pop();
    q.push((a + b) / 2);
  }

  cout << q.top() << endl;

  return 0;
}
