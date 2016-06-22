#define N 10000
#define WORD 16
#define SHIFT 4

void
set(int v[], int i)
{
  v[i >> SHIFT] |= 1 << ((WORD - 1) & i);
}

void
clear(int v[], int i)
{
  v[i >> SHIFT] &= ~(1 << ((WORD - 1) & i));
}
