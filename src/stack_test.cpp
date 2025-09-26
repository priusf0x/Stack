#include <stdio.h>

#include "stack.h"

int main(void)
{
    stack_t swag = {};

    StackInit(&swag, 3);

    StackPush(&swag, 2);
    StackPush(&swag, 4);
    StackPush(&swag, 5);
    StackPush(&swag, 2);

    value_type x = 0;

    StackPop(&swag, &x);
    printf("%d\n", x);

    StackPop(&swag, &x);
    printf("%d\n", x);

    StackPop(&swag, &x);
    printf("%d\n", x);

    StackPop(&swag, &x);
    printf("%d\n", x);
    StackPop(&swag, &x);
    printf("%d\n", x);

    StackPop(&swag, &x);
    printf("%d\n", x);

    StackDump(&swag);

    StackDestroy(&swag);

    return 0;
}
