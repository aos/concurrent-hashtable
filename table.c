/*
 * Thread-safe concurrent hash table implementation
 *
 * Locking is implemented per-list. In this way, it is possible to
 * access multiple lists without waiting for a lock.
*/

#include "table.h"

int
main(int argc, char *argv[])
{
  // Total line counter
  int total = 0;

  // Pointers for worker thread return values
  void *ret[argc - 1];

  pthread_t p[argc - 1];

  for (int i = 0; i < argc - 1; i++) {
    pthread_create(&p[i], NULL, worker, argv[i + 1]);
  }

  for (int i = 0; i < argc - 1; i++) {
    pthread_join(p[i], &ret[i]); 
    total = total + (int) ret[i];
  }

  printf("Total number of words: %d\n", total);
  return 0;
}
