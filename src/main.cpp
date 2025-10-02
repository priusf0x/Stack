#include <stdio.h>

#include "calculator.h"
#include "tools.h"
#include "stack.h"
#include "scan_user_input.h"

/*Dear programmer:
 *When I wrote this code, only god and
 *I knew how it worked.
 *Now, only god knows it!
 */

int main(void)
{
    stack_t calculator_stack = {};

    PrintHelloMessage();

    StackInit(&calculator_stack, 3, "calculator_stack");

    // StartCalculator(&calculator_stack);

    StackPush(&calculator_stack, 41);
    StackPush(&calculator_stack, 41);
    StackPush(&calculator_stack, 41);
    StackPush(&calculator_stack, 41);

    StackDump(&calculator_stack);

    StackDestroy(&calculator_stack);

    return 0;
}


