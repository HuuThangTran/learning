#include <stdio.h>
#include <math.h>
#include "stringtofloat.h" 

int main (int argc, char* argv[]) {
    char* a = "3.00";
    stringtofloat(a);
    printf("%0.3f",a);
}