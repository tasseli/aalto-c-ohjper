#include <stdio.h>
#include "anydata.h"


/* 01_anydata (a)
 * Return a new AnyData object based on the given input
 */
AnyData setDouble(double value)
{
}

AnyData setInt(int value)
{
}

AnyData setString(char* value)
{
}


void printDouble(double val)
{
    printf("D:%lf", val);
}

void printInt(int val)
{
    printf("I:%d", val);
}

void printString(char* val)
{
    printf("S:%s", val);
}

/* 01_anydata (b)
 * Print the given AnyData value, using one of the above functions
 */
void printValue(AnyData val)
{
}

