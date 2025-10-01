#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

#include "Assert.h"
#include "logger.h"
#include "tools.h"

#define HARD_SWAG

stack_function_errors_e
StackInit(stack_t*    swag,
          size_t      expected_capacity,
          const char* swag_name)
{
    ASSERT(swag != NULL);
    ASSERT(swag_name != NULL);

    swag->name = swag_name;

    if (expected_capacity == 0)
    {
        return STACK_FUNCTION_INCORRECT_VALUE_ERROR;
    }

    swag->real_capacity_in_bytes = sizeof(value_type) * expected_capacity + sizeof(long long) * (2 * CANARY_SIZE + 1);
    swag->canary_start = (byte_t*) calloc(swag->real_capacity_in_bytes, sizeof(byte_t));
    if (swag->canary_start == NULL)
    {
        swag->state = STACK_STATE_MEMORY_ERROR;
        return STACK_FUNCTION_MEMORY_ERROR;
    }

    memset(swag->canary_start, CANARY_FILL, sizeof(long long) * CANARY_SIZE);

    swag->stack_data = (value_type*) (swag->canary_start + sizeof(long long) * CANARY_SIZE);
    swag->capacity = expected_capacity;

    (swag->canary_end) = (byte_t*) (swag->stack_data + expected_capacity);
    while (!CheckIfDividableByEight((size_t) swag->canary_end))
    {
        (swag->canary_end)++;
    }
    memset(swag->canary_end, CANARY_FILL, sizeof(long long) * CANARY_SIZE);

    swag->state = STACK_STATE_OK;

    return STACK_FUNCTION_SUCCESS;
}

stack_function_errors_e
StackDestroy(stack_t* swag)
{
    free(swag->canary_start);
    swag->canary_start = NULL;
    swag->canary_end = NULL;
    swag->stack_data = NULL;

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

    VERIFY_STACK_WITH_RETURN(swag);

    if ((swag->size) == (swag->capacity))
    {
        memset(swag->canary_end, 0, sizeof(long long) * CANARY_SIZE);

        (swag->canary_start) = (byte_t*) recalloc(swag->canary_start, swag->real_capacity_in_bytes, swag->real_capacity_in_bytes + sizeof(value_type) * swag->capacity);

        VERIFY_STACK_WITH_RETURN(swag);

        swag->real_capacity_in_bytes += sizeof(value_type) * swag->capacity;

        swag->stack_data = (value_type*) (swag->canary_start + sizeof(long long) * CANARY_SIZE);
        swag->capacity *= 2;
        swag->canary_end = (byte_t*) (swag->stack_data + swag->capacity);
        while (!CheckIfDividableByEight((size_t) swag->canary_end))
        {
            (swag->canary_end)++;
        }
        memset(swag->canary_end, CANARY_FILL, sizeof(long long) * CANARY_SIZE);
    }

    VERIFY_STACK_WITH_RETURN(swag);

    (swag->stack_data)[swag->size] = value;
    (swag->size)++;

    return STACK_FUNCTION_SUCCESS;
}

stack_function_errors_e
StackPop(stack_t*    swag,
         value_type* pop_variable)
{
    ASSERT(swag != NULL);

    VERIFY_STACK_WITH_RETURN(swag);

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
    else if (((swag->state) == STACK_STATE_ZERO_CAPACITY) || (swag->capacity) == 0)
    {
        (swag->state) = STACK_STATE_ZERO_CAPACITY;
        return STACK_FUNCTION_ZERO_CAPACITY;
    }
    else if ((swag->stack_data) == NULL)
    {
        return STACK_FUNCTION_NULL_POINTER_ERROR;
    }
    // else if (((swag->stack_data)[0] != POLTORASHKA) || ((swag->stack_data)[swag->capacity + 1] != POLTORASHKA)) //ХУЙНЯ-ПЕРЕДЕЛЫВАЙ
    // {
    //     StackDump(swag);
    //     return STACK_FUNCTION_MEMORY_ERROR;
    // }
    return STACK_FUNCTION_SUCCESS;
}

