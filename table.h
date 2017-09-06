#ifndef _TABLE_H
#define _TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/resource.h> // For getrusage()
#include <sys/time.h> // For getrusage()

#define HASHSIZE (1013)
#define NUMTHREADS (2)

// Node structure
typedef struct _node_l {
  char             *value;
  struct _node_l   *next;
} node_l;

// Linked list structure
typedef struct _list_l {
  node_l            *head;
  int               count;
  pthread_mutex_t   lock;
} list_l;

// Thread data structure --> **UNUSED**
typedef struct _thread_data {
  int           counter;
  char*         value;
} thread_data;

// Resource usage
struct rusage before, after;

// Table function definitions
int insert(char *value);

char* find(const char *check);

int remove(const char *value);

void *worker(void *value);

// Time difference  
double calculate(const struct rusage *b, const struct rusage *a);

// Plot distribution
int plot_distribution();

#endif /* _TABLE_H */
