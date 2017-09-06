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
  
  // Run timer 
  double running_time = 0.0;

  // Pointers for worker thread return values
  void *ret[argc - 1];

  pthread_t p[argc - 1];

  getrusage(RUSAGE_SELF, &before);
  for (int i = 0; i < argc - 1; i++) {
    pthread_create(&p[i], NULL, worker, argv[i + 1]);
  }

  for (int i = 0; i < argc - 1; i++) {
    pthread_join(p[i], &ret[i]); 
    total = total + (int) ret[i];
  }
  getrusage(RUSAGE_SELF, &after);

  // Calculate running time
  running_time = calculate(&before, &after);

  // Plot hash distribution
  plot_distribution();

  printf("\nThreads: %d\nTotal number of words: %d\n", argc - 1, total);
  printf("Running time: %.2f seconds\n", running_time);
  return 0;
}
