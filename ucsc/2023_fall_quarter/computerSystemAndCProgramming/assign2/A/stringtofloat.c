/*
stringtofloat.c - serve as a function to conver string into float

input:P
output:

compile: gcc stringtofloat.c -o stringtofloat
*/
#include <stdio.h>
#include <math.h>
#include "stringtofloat.h"

float stringtofloat(char* strPtr, char** endptr) {
    //place holder
    int sign = 1;
    float result = 0.0f;
    int decimalPoint = 0;
    int decimalNum = 0;

    //Skipping the white space before the integer character
    while (*strPtr == ' ' || *strPtr == '\t') {
        strPtr++;
        // printf("the current pointed location: %c\n",strPtr[0]);
        // why printf("the current pointed location: %c\n",strPtr[0]); is okay but printf("the current pointed location: %d or i or c \n",strPtr); is wrong
    }

    // Take account for negative and positive interger 
    if (*strPtr == '-') {
        sign = -1;
        strPtr++;
        // printf("the current pointed location: %c\n",strPtr[0]);
    } else if (*strPtr == '+') {
        sign = 1;
        strPtr++;
        // printf("the current pointed location: %c\n",strPtr[0]);
    }
    // Process the number
    while (*strPtr >= '0' && *strPtr <= '9') {
        result = result * 10.0f + (*strPtr - '0');      
        // check 0.0f purpose            
        // printf("result: %5.3f\n",result);
        strPtr++;
    }

    //check for . and process number behind the deimal points
    while (*strPtr == '.') {
        int decimalPoint = 1;
        strPtr++;
        while (*strPtr >= '0' && *strPtr <= '9') {
            result = result *10.0f + (*strPtr - '0');
            decimalNum++;
            strPtr++;
        }
    }
    while (decimalNum > 0) {
        result /= 10.0f;
        decimalNum--;
    }
    result *= sign;
    printf("result: %5.3f\n",result);

    if (endptr != NULL) {
        *endptr = (char *)strPtr;
    }
    return result;
}
