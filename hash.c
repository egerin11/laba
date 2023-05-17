#include "tools.h"
#include <string.h>
unsigned int murMurHash(const char *key, unsigned int seed) {
    int len = (int) strlen(key);
    const unsigned int m = 0x5bd1e995;
    const int r = 24;
    unsigned int h = seed ^ len;
    const unsigned char *data = (const unsigned char *) key;
    while (len >= 4) {
        unsigned int k = *(unsigned int *) data;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
        data += 4;
        len -= 4;
    }
    switch (len) {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
        default:
            break;
    }
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    return h;
}

unsigned int hashGet(const char *str, int hashSize) {
    return murMurHash(str, 0) % hashSize;
}