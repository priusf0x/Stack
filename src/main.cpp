#include <stdio.h>

#include "stack.h"
#include "scan_user_input.h"
#include "calculator.h"

int main(void)
{
    stack_t calculator_stack = {};

    StackInit(&calculator_stack, 8, "calculator_stack");

    StartCalculator(&calculator_stack);

    StackDestroy(&calculator_stack);

    return 0;
}


