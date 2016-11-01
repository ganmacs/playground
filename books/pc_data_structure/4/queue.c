#include <stdio.h>
#include <stdlib.h>

#define M 100000

typedef struct queue {
  char name[100];
  int v;
} queue;

queue qu[M];
int head, tail;

void enque(queue q)
{
  qu[tail] = q;
  tail = (tail + 1) % M;
}

queue dequeue()
{
  queue q = qu[head];
  head = (head + 1) % M;
  return q;
}

int min(int l, int r)
{
  if (l < r)
    return l;

  return r;
}

int main(int argc, char *argv[])
{
  int n, q, m, tm = 0, i;
  queue t;

  scanf("%d %d", &n, &q);

  head = 0;
  tail = n;

  for (i = 0; i < n; i++) {
    scanf("%s %d", qu[i].name, &qu[i].v);
  }

  while (head != tail) {
    t = dequeue();
    m = min(q, t.v);
    tm += m;
    t.v -= m;
    if (t.v > 0) {
      enque(t);
    } else {
      printf("%s %d\n", t.name, tm);
    }
  }
  return 0;
}
