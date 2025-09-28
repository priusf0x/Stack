#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "stack.h"
#include "logger.h"

enum calculator_commands_e
{
    CALCULATOR_COMMAND_START = 0,
    CALCULATOR_COMMAND_ADD = 1,
    CALCULATOR_COMMAND_SUB = 2,
    CALCULATOR_COMMAND_MUL = 3,
    CALCULATOR_COMMAND_DIV = 4,
    CALCULATOR_COMMAND_OUT = 5,
    CALCULATOR_COMMAND_HTL = 6,
    CALCULATOR_COMMAND_PUSH = 7,
    CALCULATOR_COMMAND_PRINT = 8,
    CALCULATOR_COMMAND_BUFFER_OVERFLOW = 9,
    CALCULATOR_COMMAND_INCORRECT_COMMAND = 10
};

stack_function_errors_e StartCalculator(stack_t* calculator_stack);
stack_function_errors_e StackAdd(stack_t* swag);
stack_function_errors_e StackSub(stack_t* swag);
stack_function_errors_e StackMul(stack_t* swag);
stack_function_errors_e StackDiv(stack_t* swag);
void                    PrintOut(stack_t* calculator_stack);

#ifdef SKIP_STACK_VERIFICATION
#define VERIFY_FUNCTION(X) X
#else
#define VERIFY_FUNCTION(X) if (X != STACK_FUNCTION_SUCCESS) {LOGSHIT(DETALIZATION_LEVEL_ERROR, "STACK_FUNCTION_ERROR %d was occupied in line %d in %s.", X, __LINE__, __FILE__);}
#endif

#endif
