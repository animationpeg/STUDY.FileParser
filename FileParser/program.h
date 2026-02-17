#pragma once
#include <stdio.h>

// Sample Header file with inline functions for addition and multiplication

inline void add(int a, int b)
{
    printf("Added value=%d\n", a + b);
}

inline void multiply(int a, int b)
{
    printf("Multiplied value=%d\n", a * b);
}