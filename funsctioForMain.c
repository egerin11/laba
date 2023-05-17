#include<stdio.h>
#include "struct.h"
#include "tools.h"
#include <stdbool.h>


void showMenu() {
    printf("\t\tMENU\n");
    printf("\tGET IP 1\n");
    printf("\tGET ALL DNS 2\n");
    printf("\tCACHE 3\n");
    printf("\tADD  4\n");
    printf("\tEXIT 5\n");


}

bool check(int *number) {
    return scanf("%d", number) != 1 || getchar() != '\n';
}

void clearStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void inputNumber(int *number) {
    while (check(number)) {
        printf("Enter a valid number: ");
        clearStdin();
    }

}

void inputNumberWithBoundsForMenu(int *number, const int leftBound, const int rightBound) {

    do {
        printf("Enter a number: ");
        inputNumber(number);
    } while (*number <= leftBound || *number > rightBound);

}

void getAllDNS() {
    char *ip;
    printf("input IP \n");
    getString(&ip);
    findDNS("dns.txt", ip);

}

void print(LRUCache* cache) {
    Node* temp = cache -> list -> head;
    for(int i = 0; i < cache -> list -> size; i++) {
        printf("%s %s \n", temp -> key, temp -> value);
        temp = temp -> next;
    }
}

void addInFile() {
    char *dns = NULL;
    printf("input DNS \n");
    getString(&dns);
    char *ip = NULL;
    printf("input IP \n");
    getString(&ip);
    while (isValidIP(ip) == 0) {
        printf("input valid \n");
        getString(&ip);
        clearStdin();
    }
    addDNS("dns.txt", dns, ip);
}

void find(LRUCache *cache) {
    char *dns = NULL;
    printf("input DNS\n");
    getString(&dns);
    getIP(cache, dns);
}