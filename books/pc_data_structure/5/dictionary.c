#include <stdio.h>
#include <string.h>

#define M 3001134

int c2i(char c)
{
  if (c == 'A') return 1;
  else if (c == 'C') return 3;
  else if (c == 'G') return 5;
  else if (c == 'T') return 7;

  return 0;
}

char hash[M][20];

long long gkey(char v[])
{
  long long sum = 0, h = 1;
  int i, n;
  for (i = 0, n = strlen(v); i < n; i++) {
    sum += (h * c2i(v[i]));
    h *= 5;
  }

  return sum;
}

#define h1(vv) (vv % M)
#define h2(vv) ((vv + 1) % M)

void insert(char v[])
{
  long long key = gkey(v), i = 0, h;
  while (1) {
    h = (h1(key) + h2(key) * i) % M;
    if (hash[h][0] == '\0') {
      strcpy(hash[h], v);
      return;
    }
    i++;
  }
}

int find(char v[])
{
  long long key = gkey(v), i = 0, h;
  while (1) {
    h = (h1(key) + h2(key) * i) % M;
    if (hash[h][0] == '\0')
      return 0;

    if (strcmp(hash[h], v) == 0) {
      return 1;
    }

    i++;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  int n, i;
  scanf("%d", &n);
  char cmd[20], v[20];

  for (i = 0; i < M; i++) hash[i][0] = '\0';

  for (i = 0; i < n; i++) {
    scanf("%s %s", cmd, v);

    if (cmd[0] == 'i') {
      insert(v);
    } else {
      if (find(v)) {
        puts("yes");
      }
      else {
        puts("no");
      }
    }

  }

  return 0;
}
