#include <cstdio>
#include <iostream>
using namespace std;
static const int M = 1000;

struct Card { char suit, value; };

void pp (Card v[], int size)
{
  for (int i = 0; i < size-1; i++) {
    cout << v[i].suit << v[i].value << ' ';
  }
  cout << v[size-1].suit << v[size-1].value << endl;;
}

void bubble(Card v[], int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = n - 1; j > i; j--) {
      if (v[j].value < v[j-1].value)
        swap(v[j], v[j-1]);
    }
  }
}

void selection(Card v[], int n)
{
  int minv;
  for (int i = 0; i < n; i++) {
    minv = i;
    for (int j = i; j < n; j++) {
      if (v[minv].value > v[j].value)
        minv = j;
    }

    swap(v[minv], v[i]);
  }
}

bool is_stable(Card v1[], Card v2[], int n)
{
  for (int i = 0; i < n; i++) {
    if (v1[i].suit != v2[i].suit)
      return false;
  }
  return true;
}

int main(int argc, char *argv[])
{
  Card v1[M], v2[M];
  int n;

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> v1[i].suit;
    cin >> v1[i].value;
    v2[i] = v1[i];
  }

  bubble(v1, n);
  pp(v1, n);
  cout << "Stable" << endl;


  selection(v2, n);
  pp(v2, n);


  if (is_stable(v1, v2, n)) {
    cout << "Stable" << endl;
  } else {
    cout << "Not stable" << endl;
  }


  return 0;
}
