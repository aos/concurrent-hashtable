#ifndef _TABLE_H
#define _TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

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

// Initialize global list lock
pthread_mutex_t list_lock = PTHREAD_MUTEX_INITIALIZER;

// Initialize hash table 
list_l *hashtable[HASHSIZE] = {0};

// Table function definitions
int insert(char *value);

char* find(const char *check);

int remove(const char *value);

void *worker(void *value);

#endif /* _TABLE_H */
