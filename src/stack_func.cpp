#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

#include "Assert.h"
#include "Logger.h"

stack_function_errors_e
StackInit(stack_t* swag,
          size_t   expected_capacity)
{
    ASSERT(swag != NULL);

    if (expected_capacity <= 0)
    {
        return STACK_FUNCTION_INCORRECT_VALUE_ERROR;
    }

    (swag->stack_data) = (value_type*) calloc(expected_capacity, sizeof(value_type));
    if (swag->stack_data == NULL)
    {
        swag->state = STACK_STATE_MEMORY_ERROR;
        return STACK_FUNCTION_MEMORY_ERROR;
    }

    swag->capacity = expected_capacity;
    swag->state = STACK_STATE_OK;

    return STACK_FUNCTION_SUCCESS;
}

stack_function_errors_e
StackDestroy(stack_t* swag)
{
    free(swag->stack_data);
    swag->state = STACK_STATE_UNINITIALIZED;
    swag->capacity = 0;
    swag->size = 0;

    return STACK_FUNCTION_SUCCESS;
}

stack_function_errors_e
StackPush(stack_t*   swag,
          value_type value)
{
    ASSERT(swag != NULL);

    VERIFY_STACK(swag);

    if ((swag->size) == (swag->capacity))
    {
        (swag->stack_data) = (value_type*) realloc(swag->stack_data, 2 * sizeof(value_type) * (swag->capacity));
        (swag->capacity) *= 2;
    }

    VERIFY_STACK(swag);

    (swag->stack_data)[swag->size] = value;
    (swag->size)++;

    return STACK_FUNCTION_SUCCESS;
}

stack_function_errors_e
StackPop(stack_t*    swag,
         value_type* pop_variable)
{
    ASSERT(swag != NULL);

    VERIFY_STACK(swag);

    if ((swag->size) == 0)
    {
        *pop_variable = 0;
        return STACK_FUNCTION_EMPTY_STACK_ERROR;
    }

    (swag->size)--;
    *pop_variable = (swag->stack_data)[swag->size];
    (swag->stack_data)[swag->size] = 0;

    return STACK_FUNCTION_SUCCESS;
}

stack_function_errors_e
VerifyStack(stack_t* swag)
{
    if ((swag->state) == STACK_STATE_UNINITIALIZED)
    {
        return STACK_FUNCTION_UNINITIALIZED_ERROR;
    }
    else if ((swag->state) == STACK_STATE_UNINITIALIZED)
    {
        return STACK_FUNCTION_MEMORY_ERROR;
    }
    else if (((swag->state) == STACK_STATE_ZERO_CAPACITY) && (swag->capacity) <= 0)
    {
        (swag->state) = STACK_STATE_ZERO_CAPACITY;
        return STACK_FUNCTION_ZERO_CAPACITY;
    }
    else if ((swag->stack_data) == NULL)
    {
        return STACK_FUNCTION_NULL_POINTER_ERROR;
    }
    return STACK_FUNCTION_SUCCESS;
}

