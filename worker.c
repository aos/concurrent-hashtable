/*
 * Thread called by main
*/

#include "table.h"

void *worker(void *value) {
  uint64_t tid;
  pthread_threadid_np(NULL, &tid);

  // Count # of lines
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
    find(line);

    counter++;
  }
  
  fclose(fp);

  printf("Thread (%llu) -> file: %s, words: %ld\n", tid, (char *) value, counter);
  return (void*) counter;
}
