#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

#include "Assert.h"
#include "logger.h"

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

    (swag->stack_data) = (value_type*) calloc(expected_capacity + 2, sizeof(value_type)); //for POLTORASHKA
    if (swag->stack_data == NULL)
    {
        swag->state = STACK_STATE_MEMORY_ERROR;
        return STACK_FUNCTION_MEMORY_ERROR;
    }

    swag->capacity = expected_capacity;
    swag->state = STACK_STATE_OK;

    (swag->stack_data)[0] = POLTORASHKA;
    (swag->stack_data)[swag->capacity + 1] = POLTORASHKA;

    return STACK_FUNCTION_SUCCESS;
}

stack_function_errors_e
StackDestroy(stack_t* swag)
{
    free(swag->stack_data);
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
        (swag->stack_data) = (value_type*) recalloc(swag->stack_data, sizeof(value_type) * (swag->capacity + 2), sizeof(value_type) * (2 * (swag->capacity) + 2));
        (swag->stack_data)[swag->capacity + 1] = 0;
        (swag->capacity) *= 2;
        (swag->stack_data)[swag->capacity + 1] = POLTORASHKA;
    }

    VERIFY_STACK_WITH_RETURN(swag);

    (swag->size)++;
    (swag->stack_data)[swag->size] = value;

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

    *pop_variable = (swag->stack_data)[swag->size];
    (swag->stack_data)[swag->size] = 0;
    (swag->size)--;

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
    else if (((swag->stack_data)[0] != POLTORASHKA) || ((swag->stack_data)[swag->capacity + 1] != POLTORASHKA))
    {
        StackDump(swag);
        return STACK_FUNCTION_MEMORY_ERROR;
    }
    return STACK_FUNCTION_SUCCESS;
}

void* recalloc(void*  pointer,
               size_t current_size,
               size_t new_size)
{
    pointer = realloc(pointer, new_size);
    memset((char*) pointer + current_size, 0, new_size - current_size);

    return pointer;
}
