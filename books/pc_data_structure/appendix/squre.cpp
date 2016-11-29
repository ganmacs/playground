#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void rec(int n1, int n2, string s)
{
  if (n2 == 0) cout << s << endl;
  for (int i = min(n1, n2); i > 0; i--) {
    rec(i, n2 - i, s + ((s == "") ? "" : " ") + std::to_string(i));
  }
}

int main()
{
  int n;
  while (cin >> n, n) rec(n, n, "");
}
