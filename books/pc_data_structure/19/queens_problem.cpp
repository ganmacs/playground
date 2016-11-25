#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
static const int N = 8;

int n;
bool M[N][N];
set <int> v;

void pp()
{
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << (M[i][j] ? "Q" : ".");
    }
    cout << endl;
  }
}

bool is_ok(int y, int x)
{
  for (int i = 1; i < N; i++) {
    if ((0 <= (x - i)) && ((x - i) < N)) { if (M[y][x-i]) return false; } // t
    if ((0 <= (x + i)) && ((x + i) < N)) { if (M[y][x+1]) return false; } // r
    if ((0 <= (y - i)) && ((y - i) < N)) { if (M[y-i][x]) return false; } // l
    if ((0 <= (y + i)) && ((y + i) < N)) { if (M[y+i][x]) return false; } // b
    if ((0 <= (x - i) && (x - i) < N) && (0 <= (y - i) && (y - i) < N)) { if (M[y-i][x-i]) return false; } // lt
    if ((0 <= (x + i) && (x + i) < N) && (0 <= (y + i) && (y + i) < N)) { if (M[y+i][x+i]) return false; } // rb
    if ((0 <= (x + i) && (x + i) < N) && (0 <= (y - i) && (y - i) < N)) { if (M[y-i][x+i]) return false; } // rt
    if ((0 <= (x - i) && (x - i) < N) && (0 <= (y + i) && (y + i) < N)) { if (M[y+i][x-i]) return false; } // lb
  }

  return true;
}

bool q8(int d)
{
  if (d == N) return true;
  if (std::find(v.begin(), v.end(), d) != v.end()) return q8(d + 1);

  for (int i = 0; i < N; i++) {
    if (is_ok(d, i)) {
      M[d][i] = true;
      if (q8(d + 1)) return true;
      M[d][i] = false;
    }
  }

  return false;
}

int main(){
  int qx, qy;
  cin >> n;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) M[i][j] = false;
  }

  for (int i = 0; i < n; i++) {
    cin >> qy >> qx;
    v.insert(qy);
    M[qy][qx] = true;
  }

  q8(0);
  pp();
}
