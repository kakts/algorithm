#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N (10)

int organization_search(int x, int *a, int num) {
    
    int n = 0, t;
    while(n < num && a[n] != x) {
        n++;
    }

    if (n < num) {
        if (n > 0) {
            t = a[n-1];
            a[n-1] = a[n];
            a[n] = t;
            return n-1;
        }
        return n;
    }

    return NOT_FOUND;
}


