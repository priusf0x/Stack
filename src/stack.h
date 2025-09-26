#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef int value_type;

enum stack_function_errors_e
{
    STACK_FUNCTION_SUCCESS,
    STACK_FUNCTION_INITIALIZATION_ERROR,
    STACK_FUNCTION_UNINITIALIZED_ERROR,
    STACK_FUNCTION_NULL_POINTER_ERROR,
    STACK_FUNCTION_MEMORY_ERROR,
    STACK_FUNCTION_ZERO_CAPACITY,
    STACK_FUNCTION_INCORRECT_VALUE_ERROR,
    STACK_FUNCTION_EMPTY_STACK_ERROR
};

enum stack_state_e
{
    STACK_STATE_OK,
    STACK_STATE_UNINITIALIZED,
    STACK_STATE_MEMORY_ERROR,
    STACK_STATE_ZERO_CAPACITY
};

typedef struct swag
{
    value_type* stack_data;
    size_t size;
    size_t capacity;
    enum stack_state_e state = STACK_STATE_UNINITIALIZED;
} stack_t;

stack_function_errors_e StackInit(stack_t* swag, size_t count);
stack_function_errors_e StackDestroy(stack_t* swag);
stack_function_errors_e StackPush(stack_t* swag, value_type value);
stack_function_errors_e StackPop(stack_t* swag, value_type* pop_variable);
stack_function_errors_e VerifyStack(stack_t* swag);
stack_function_errors_e StackDump(stack_t* swag);

#ifdef HARD_SWAG
#define VERIFY_STACK(X)
#else
#define VERIFY_STACK(X) if (VerifyStack(X) != STACK_FUNCTION_SUCCESS) {printf("Stack error in %d line in file %s \n", __LINE__, __FILE__);return VerifyStack(X);}
#endif

#define VAR_NAME(X) #X

#endif
