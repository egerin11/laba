#ifndef LABA2_5_STRUCT_H
#define LABA2_5_STRUCT_H
#define MAX_HASH_SIZE 1
#define MAX_CACHE_SIZE 4

typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
    struct Node* prev;
    struct Node* hashNext;
} Node;

typedef struct Table {
    int capacity;
    Node* *array;
} Table;

typedef struct List {
    int size;
    int capacity;
    Node* head;
    Node* tail;
} List;

typedef struct LRUCache {
    Table* table;
    List* list;
}LRUCache;
#endif
