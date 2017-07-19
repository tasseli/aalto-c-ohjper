#include <stdio.h>
#include <string.h>
#include "anydata.h"


/* 01_anydata (a)
 * Return a new AnyData object based on the given input
 */
AnyData setDouble(double value)
{
	AnyData returnable;
	returnable.type = DOUBLE;
	returnable.value.dval = value;
	return returnable;
}

AnyData setInt(int value)
{
	AnyData returnable;
	returnable.type = INT;
	returnable.value.ival = value;
	return returnable;
}

AnyData setString(char* value)
{
	AnyData returnable;
	returnable.type = STRING;
	strcpy(returnable.value.sval, value);
	return returnable;
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
	switch(val.type) {
	case DOUBLE:
		printDouble(val.value.dval);
		break;
	case INT:
		printInt(val.value.ival);
		break;
	case STRING:
		printString(val.value.sval);
		break;
	}
}

