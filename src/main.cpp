#include <stdio.h>

#include "calculator.h"
#include "tools.h"
#include "stack.h"
#include "scan_user_input.h"


int main(void)
{
    stack_t calculator_stack = {};

    PrintHelloMessage();

    StackInit(&calculator_stack, 3, "calculator_stack");

    // StartCalculator(&calculator_stack);

    StackDump(&calculator_stack);

    StackDestroy(&calculator_stack);

    return 0;
}


