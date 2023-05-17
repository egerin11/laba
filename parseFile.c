#include"struct.h"
#include "tools.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void searchIP(const char *fileName, LRUCache *cache, const char *dns, const char *domen) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("open error\n");
        return;
    }
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        char *savePtr = NULL;
        const char *token = strtok_r(buffer, " \n", &savePtr);
        if (strcmp(token, dns) == 0) {
            const char *ip = strtok_r(NULL, " \n", &savePtr);
            if (isValidIP(ip) == 0) {
                fclose(fp);
                searchIP(fileName, cache, ip, token);
            } else if (domen != NULL) put(cache, domen, ip);
            else put(cache, dns, ip);
        }
    }
    fclose(fp);
}

int isValidIP(const char *ipAddress) {
    int dots = 0;
    int len = (int) strlen(ipAddress);
    if (len < 7 || len > 15)
        return 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit(ipAddress[i]) && ipAddress[i] != '.')
            return 0;
        if (ipAddress[i] == '.')
            dots++;
    }
    if (dots != 3)
        return 0;
    char *token;
    char *ptr;
    char tempIP[strlen(ipAddress) + 1];
    strcpy(tempIP, ipAddress);
    token = strtok(tempIP, ".");
    while (token != NULL) {
        long num = strtol(token, &ptr, 10);
        if (num < 0 || num > 255)
            return 0;
        if (*ptr)
            return 0;
        token = strtok(NULL, ".");
    }

    return 1;
}

void findDNS(const char *fileName, const char *ip) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("open error\n");
        return;
    }
    fseek(fp, 0, SEEK_SET);
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        char *savePtr = NULL;
        char *token = strtok_r(buffer, " \n", &savePtr);
        char *ipAdr = strtok_r(NULL, " \n", &savePtr);
        if (strcmp(ip, ipAdr) == 0) {
            printf("%s\n", token);
            long position = ftell(fp);
            findDNS(fileName, token);
            fseek(fp, position, SEEK_SET);
        }
    }
    fclose(fp);
}

void addDNS(const char *fileName, const char *dns, const char *ip) {

    FILE *fp = fopen(fileName, "a");
    if (fp == NULL) {
        printf("open error");
        return;
    }
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        char *savePtr = NULL;
        const char *token = strtok_r(buffer, " \n", &savePtr);
        if (strcmp(token, dns) == 0) {
            printf("this dns %s already exists \n", dns);
            fclose(fp);
            return;
        }
    }
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "\n%s %s", dns, ip);
    fclose(fp);
}