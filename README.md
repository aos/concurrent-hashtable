## Concurrent hashtable

This is a concurrent hashtable implementation in C.

### Implementation

This hashtable works by initially creating an empty array of `HASHSIZE` buckets. On first insertion to a bucket, a linked list structure is initialized. Each linked list structure contains a pointer to the head, the count of nodes, as well as a lock.

Each node structure contains a value and a next pointer. The nodes do not contain key/value pairs as it was built to store a spell-checking dictionary. However, this can be very easily implemented on each node.

The table supports `insert()`, `find()`, and `remove()` methods currently. 

### Notes on concurrency

The hashtable is not lock-free. Additionally, the locks are implemented per linked list (bucket). This allows for manipulation of other buckets without having to lock the entire hashtable.
