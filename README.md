## Concurrent hashtable

This is a concurrent hashtable implementation in C.

### Implementation

This hashtable works by initially creating an empty array of `HASHSIZE` buckets. On first insertion to a bucket, a linked list structure is initialized. Each linked list structure contains a pointer to the head, the count of nodes, as well as a lock.

Each node structure contains a value and a next pointer. The nodes do not contain key/value pairs as it was built to store a spell-checking dictionary. However, this can be very easily implemented on each node.

The table supports `insert()`, `find()`, and `remove()` methods currently. 

The current implementation of the hashtable works by passing in file names into main, and each thread opens a separate file. The threads each run through the file assigned to them and insert each word into the global hashtable. Each threads runs a counter of number of words inserted which is returned to the main thread. The main thread tallies all words and prints total number of words inserted.

### Notes on concurrency

The hashtable is not lock-free. Additionally, the locks are implemented per linked list (bucket). This allows for manipulation of other buckets without having to lock the entire hashtable.
