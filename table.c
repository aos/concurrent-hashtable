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

  // Total arguments
  int args = (strcmp(argv[1], "-p") == 0) ? 2 : 1;
  int targs = argc - args;

  // Total line counter
  int total = 0;
  
  // Run timer 
  double running_time = 0.0;

  // Pointers for worker thread return values
  void *ret[targs];

  pthread_t p[targs];

  getrusage(RUSAGE_SELF, &before);
  for (int i = 0; i < targs; i++) {
    pthread_create(&p[i], NULL, worker, argv[i + args]);
  }

  for (int i = 0; i < targs; i++) {
    pthread_join(p[i], &ret[i]); 
    total = total + (int) ret[i];
  }
  getrusage(RUSAGE_SELF, &after);

  // Calculate running time
  running_time = calculate(&before, &after);

  // Plot hash distribution
  if (args == 2) {
    plot_distribution();
  }

  printf("\nThreads: %d\nTotal number of words: %d\n", targs, total);
  printf("Running time: %.2f seconds\n", running_time);
  return 0;
}
