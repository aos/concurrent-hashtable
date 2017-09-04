/*
 * Thread-safe concurrent hash table implementation
 *
 * Locking is implemented per-list. In this way, it is possible to
 * access multiple lists without waiting for a lock.
*/
#include "table.h"

void *worker(void *value) {
  uint64_t tid;
  pthread_threadid_np(NULL, &tid);

  // Count # of lines
  //int *counter = malloc(sizeof (int));
  long counter = 0;

  // Open file
  FILE *fp = fopen((char*) value, "r");

  if (fp == NULL) {
    printf("Open failed\n");
  }

  // Initialize line pointer, length, and line capacity
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;

  while ((linelen = getline(&line, &linecap, fp)) > 0) {
    insert(line);
    // char *string = find(line);
    // printf("Thread id (%llu), value: %s\n", tid, string);
    counter++;
  }

  printf("Thread (%ud) -> file name: %s, number of words: %ld\n", tid, (char *) value, counter);

  return (void*) counter;
}

int
main(int argc, char *argv[])
{
  /** TODO:
   * Allow files to be added on command-line,
   * instead of being hard-coded in.
  */

  char *files[] = {"sowpods.txt", "large.txt", "francais.txt"};

  // Total line counter
  int total = 0;

  // Pointers for worker thread return values
  void *ret[3];

  pthread_t p[3];

  for (int i = 0; i < 3; i++) {
    pthread_create(&p[i], NULL, worker, files[i]);
  }

  for (int i = 0; i < 3; i++) {
    pthread_join(p[i], &ret[i]); 
    total = total + (int) ret[i];
  }

  printf("Total number of words: %d\n", total);
  return 0;
}
