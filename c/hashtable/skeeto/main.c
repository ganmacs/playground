#include <stdlib.h>
#include <stdio.h>
#include "strht.h"
#include "hashtab.h"

int
main(int argc, char *argv[])
{

  hashtab_t *tbl = ht_init(1000);
  strht_insert(tbl, "key1", "saikou");
  strht_insert(tbl, "key2", "urtra saikou");

  printf("%s\n", (char *)strht_search(tbl, "key1"));
  printf("%s\n", (char *)strht_search(tbl, "key2"));


  return 0;
}
