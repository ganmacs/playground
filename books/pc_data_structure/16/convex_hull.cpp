#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <stack>
#include <set>

using namespace std;
static const double EPS = 1e-8;
static const int INF = 1000000;
static const int MAX = 100000;

int n;
pair<int, int> A[MAX];

double cross(double x1, double y1, double x2, double y2) { return (x1 * y2) - (y1 * x2); }

bool ccw(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
  double d = cross(b.first - a.first,
                   b.second - a.second,
                   c.first - a.first,
                   c.second - a.second);
  return EPS < d;
}


bool msort(const pair<int, int> &a, const  pair <int, int> &b)
{
  if (a.first == b.first)
    return a.second < b.second;

  return a.first < b.first;
}

void convex()
{
  int k = 0;
  vector<pair<int, int> > s1(MAX), s2(MAX), s3;

  for (int i = 0; i < n; i++) {
    while (k >= 2 && ccw(s1[k-2], s1[k-1], A[i])) k--;
    s1[k++] = A[i];
  }
  s1.resize(k);

  k = 0;
  for (int i = n-1; i >= 0; i--) {
    while (k >= 2 && ccw(s2[k-2], s2[k-1], A[i])) k--;
    s2[k++] = A[i];
  }
  s2.resize(k);

  for (int i = (int)s2.size()-1; i >= 0; i--) s3.push_back(s2[i]);
  for (int i = (int)s1.size()-2; i > 0; i--) s3.push_back(s1[i]);

  cout << s3.size() << endl;

  int j = 0;
  int jmin = s3[0].second;
  for (int i = 0; i < (int)s3.size(); i++) {
    if ((int)s3.size() > i + 1 && s3[i + 1].second < jmin) {
      j++;
      jmin = s3[i + 1].second;
      continue;
    }
    cout << s3[i].first << " " << s3[i].second << endl;
  }

  for (int i = 0; i < j; i++) {
    cout << s3[i].first << " " << s3[i].second << endl;
  }
}

int main(){
  cin >> n;

  int x, y;

  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    A[i] = make_pair(x, y);
  }

  sort(A, A + n, msort);

  convex();
}
