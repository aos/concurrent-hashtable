#include "table.h"

// Initialize global list lock
pthread_mutex_t list_lock = PTHREAD_MUTEX_INITIALIZER;

// Initialize hash table 
list_l *hashtable[HASHSIZE] = {0};

// Hash function
size_t hash(const char *str) {
  size_t hash = 5381;

  for (int i = 0; str[i] != '\0'; i++) {
    hash += hash * 33 + (int) str[i];
  }
  return hash % HASHSIZE;
}

// Initialize a list
list_l* list_init() {
  list_l *new_list = malloc(sizeof (list_l));

  if (new_list == NULL) {
    fprintf(stderr, "Unable to allocate memory for new list.\n");
  }

  // Initialize head and lock
  new_list->head = NULL;
  new_list->count = 0;
  pthread_mutex_init(&(new_list->lock), NULL);

  return new_list;
}

// Create a new node
node_l* create_node(char *value) {
  // Malloc new node
  node_l *new_node = malloc(sizeof (node_l));

  if (new_node == NULL) {
    fprintf(stderr, "Unable to allocate memory for new node.\n");
  }

  // Allocate memory for value
  // 'strlen' does not count terminating '\0'
  new_node->value = malloc(sizeof (strlen(value) + 1));
   
  if (new_node->value == NULL) {
    fprintf(stderr, "Unable to allocate memory for value.\n"); 
  }

  // Copy value into node
  strcpy(new_node->value, value);
  new_node->next = NULL;

  return new_node;
}

int insert(char *value) {
  // Create new node
  node_l *new_node = create_node(value);
  // Get hash index
  size_t index = hash(value);
  
  // Initialize list at hash table index
  if (hashtable[index] == NULL) {

    pthread_mutex_lock(&(list_lock));

    if (hashtable[index] == NULL) {
      list_l *new_list = list_init();
      hashtable[index] = new_list;
    }

    pthread_mutex_unlock(&(list_lock));
  } 

  // Lock critical section
  pthread_mutex_lock(&(hashtable[index]->lock));

  new_node->next = hashtable[index]->head; 
  hashtable[index]->head = new_node;
  hashtable[index]->count++;

  pthread_mutex_unlock(&(hashtable[index]->lock));

  return 0;
}

char* find(const char *check) {
  size_t index = hash(check);

  // Lock at hashtable index
  pthread_mutex_lock(&(hashtable[index]->lock));

  // Get list head at hashtable[index] (if exists)
  node_l *checker = hashtable[index]->head;

  // Find value in list
  while (checker) {
    if (strcasecmp(check, checker->value) == 0) {

      pthread_mutex_unlock(&(hashtable[index]->lock));
      // Found value
      return checker->value;
    }
    checker->next = checker;
  }

  pthread_mutex_unlock(&(hashtable[index]->lock));
  // Did not find value
  return NULL;
}

int remove(const char *value) {
  size_t index = hash(value);

  // Lock at hashtable index
  pthread_mutex_lock(&(hashtable[index]->lock));

  // Get list head at hashtable index
  node_l *current = hashtable[index]->head;
  node_l *previous = NULL;

  while (current) {
    if (strcasecmp(value, current->value) == 0) {

      // Value is first item in list
      if (current == hashtable[index]->head) {
        hashtable[index]->head = current->next;
        free(current);

        // Update list count
        hashtable[index]->count--;

        pthread_mutex_unlock(&(hashtable[index]->lock));
        return 0; // Success
      }
      else {
        // Link previous node with one after current
        previous->next = current->next;
        free(current);

        hashtable[index]->count--;

        pthread_mutex_unlock(&(hashtable[index]->lock));
        return 0;
      }
    }
    previous = current;
    current = current->next;
  }

  pthread_mutex_unlock(&(hashtable[index]->lock));
  // Did not find value
  return 1;
}
