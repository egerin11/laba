#include <stdio.h>
#include "tools.h"
#include "struct.h"


#define EXIT 5
#define GET_IP 1
#define GET_ALL_DNS 2
#define CACHE 3
#define ADD 4


int main() {
 int choice = 0;
  LRUCache *cache = createCache(MAX_HASH_SIZE);
//    put(cache, "a" , "b");
//    put(cache, "c" , "d");
//    put(cache, "e" , "f");
//    put(cache, "g" , "h");
//    put(cache, "c" , "z");
//    put(cache, "e" , "y");
//
//    printf("%s\n",get(cache, "e"));
//
//    print(cache);

    do {
        showMenu();
        inputNumberWithBoundsForMenu(&choice,0,5);

        switch (choice) {
            case GET_IP:
                find(cache);
                break;
            case GET_ALL_DNS:
                getAllDNS();
                break;
            case CACHE:
                print(cache);
                break;
            case ADD:
                addInFile();
                break;
            default:{
                printf("goodbye");
                freeCache(cache);
                break;
            }

        }
    } while (choice != EXIT);


    return 0;
}
