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
  strht_insert(tbl, "key3", "urtra super saikou");

  printf("%s\n", (char *)strht_search(tbl, "key1"));
  printf("%s\n", (char *)strht_search(tbl, "key2"));

  hashtab_iter_t iter;
  ht_new_iter(tbl, &iter);

  strht_remove(tbl, "key2");

  for (; iter.key != NULL; ht_iter_inc(&iter)) {
    printf("%s => %s\n", (char *) iter.key, iter.value);
  }

  ht_destroy(tbl);
  return 0;
}
