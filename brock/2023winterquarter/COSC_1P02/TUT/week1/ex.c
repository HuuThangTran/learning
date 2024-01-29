#include <stdio.h>

int sum (int x, int y)
int sum (int x,int y) {
    int t;
    t= x + y;
    return t; 
}


int main (void) {
    int n = 7;
    int y = 11;
    int o;
    o = sum(n,y);
    printf("o: %i\n",o);
}


