#include "struct.h"
#include "tools.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

void getString(char **string) {
    int size = 0;
    int realSize = 8;
    *string = (char *) malloc(realSize * sizeof(char));
    rewind(stdin);
    char check;
    while (true) {
        check = (char) getchar();
        if (check == '\n') {
            if (size + 1 < realSize) {
                *string = (char *) realloc(*string, (size + 1) * sizeof(char));
            }
            (*string)[size] = '\0';
            return;
        }

        (*string)[size] = check;
        size++;
        if (size + 1 == realSize) {
            realSize *= 2;
            *string = (char *) realloc(*string, realSize * sizeof(char));
        }
    }
}

LRUCache *createCache(int size) {
    LRUCache *newCache = (LRUCache *) malloc(sizeof(LRUCache));
    Table *table = createTable(size * 2);
    List *list = createList(MAX_CACHE_SIZE);
    newCache->table = table;
    newCache->list = list;
    return newCache;
}

Node *createNode(const char *key, const char *value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->hashNext = NULL;
    return newNode;
}

List *createList(int capacity) {
    List *newList = (List *) malloc(sizeof(List));
    newList->size = 0;
    newList->capacity = capacity;
    newList->head = newList->tail = NULL;
    return newList;
}

Table *createTable(int capacity) {
    Table *newHash = (Table *) malloc(sizeof(Table));
    newHash->capacity = capacity;
    newHash->array = (Node **) malloc(sizeof(Node) * capacity);
    for (size_t i = 0; i < capacity; i++)
        newHash->array[i] = NULL;
    return newHash;
}

void removeCache(LRUCache *cache) {
    Table *table = cache->table;
    List *list = cache->list;
    Node *entry = list->head;
    if (list->head == NULL)
        return;
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->head = entry->next;
        list->size--;
        list->head->prev = NULL;
    }
    size_t hashCode = hashGet(entry->key, table->capacity);
    Node **indirect = &table->array[hashCode];
    while ((*indirect) != entry)
        indirect = &(*indirect)->next;
    *indirect = entry->next;
    free(entry);
}

void moveToFront(LRUCache *cache, const char *key) {
    Table *table = cache->table;
    List *list = cache->list;
    if (list->size == 1)
        return;
    size_t hashCode = hashGet(key, table->capacity);
    Node *curr = table->array[hashCode];
    while (curr) {
        if (strcmp(curr->key, key) == 0)
            break;
        curr = curr->hashNext;
    }
    if (curr == NULL)
        return;
    if (curr->prev == NULL) {
        curr->prev = list->tail;
        list->head = curr->next;
        list->head->prev = NULL;
        list->tail->next = curr;
        list->tail = curr;
        list->tail->next = NULL;
        return;
    }
    if (curr->next == NULL)
        return;
    curr->next->prev = curr->prev;
    curr->prev->next = curr->next;
    curr->next = NULL;
    list->tail->next = curr;
    curr->prev = list->tail;
    list->tail = curr;
}

void addToList(LRUCache *cache, Node *node) {
    List *list = cache->list;
    if (list->size == list->capacity)
        removeCache(cache);
    if (list->head == NULL) {
        list->head = list->tail = node;
        list->size = 1;
        return;
    }
    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
    list->size++;
}

int addToHash(Table *table, Node *node) {
    size_t hashCode = hashGet(node->key, table->capacity);
    if (table->array[hashCode] != NULL) {
        Node *curr = table->array[hashCode];
        while (curr->hashNext != NULL) {
            if (strcmp(curr->key, node->key) == 0) {
                curr->value = node->value;
                return 1;
            }
            curr = curr->hashNext;
        }
        if (strcmp(curr->key, node->key) == 0) {
            curr->value = node->value;
            return 1;
        }
        curr->hashNext = node;
        return 0;
    } else {
        table->array[hashCode] = node;
        return 0;
    }
}

void put(LRUCache *cache, const char *key, const char *value) {
    Node *valNode = createNode(key, value);
    if (addToHash(cache->table, valNode))
        moveToFront(cache, valNode->key);
    else
        addToList(cache, valNode);
}

char *get(LRUCache *cache, const char *key) {
    Table *table = cache->table;
    size_t hashCode = hashGet(key, table->capacity);
    Node *curr = table->array[hashCode];
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            moveToFront(cache, key);
            return curr->value;
        }
        curr = curr->hashNext;
    }
    return NULL;
}

void getIP(LRUCache *cache, const char *key) {
    if (get(cache, key) == NULL) {
        searchIP("dns.txt", cache, key, NULL);
    }
    else return;
}

//write function for freeing memory struct Node, List, Table, Cache
void freeNode(Node *node) {
    free(node->key);
    free(node->value);
    free(node);
}

void freeList(List *list) {
    Node *curr = list->head;
    while (curr) {
        Node *next = curr->next;
        freeNode(curr);
        curr = next;
    }
    free(list);
}

void freeTable(Table *table) {
    for (size_t i = 0; i < table->capacity; i++) {
        Node *curr = table->array[i];
        while (curr) {
            Node *next = curr->hashNext;
            freeNode(curr);
            curr = next;
        }
    }
    free(table->array);
    free(table);
}

void freeCache(LRUCache *cache) {
    freeTable(cache->table);
    freeList(cache->list);
    free(cache);
}



