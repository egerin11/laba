#ifndef LABA2_5_TOOLS_H
#define LABA2_5_TOOLS_H
#define BUFFER_SIZE 256

#include "struct.h"
#include <stdbool.h>

bool check(int *number);

LRUCache *createCache(int size);

unsigned int murMurHash(const char *key, unsigned int seed);
void freeCache(LRUCache *cache);
Node *createNode(const char *key, const char *value);

void inputNumber(int *number);

List *createList(int capacity);

Table *createTable(int capacity);


void clearStdin();


void getString(char **string);

void getAllDNS();


void getIP(LRUCache *cache, const char *key);

char *get(LRUCache *cache, const char *key);

unsigned int hashGet(const char *str, int hashSize);

void put(LRUCache *cache, const char *key, const char *value);

void moveToFront(LRUCache *cache, const char *key);

void removeCache(LRUCache *cache);


void addToList(LRUCache *cache, Node *node);

int addToHash(Table *table, Node *node);

void put(LRUCache *cache, const char *key, const char *value);

void addInFile();

void find(LRUCache *cache);

void searchIP(const char *fileName, LRUCache *cache, const char *dns, const char *domen);

void findDNS(const char *fileName, const char *ip);

int isValidIP(const char *ipAddress);

void addDNS(const char *fileName, const char *dns, const char *ip);

void print(LRUCache *);

void showMenu();

void inputNumberWithBoundsForMenu(int *number, int leftBound, int rightBound);

#endif
