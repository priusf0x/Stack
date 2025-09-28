#include "calculator.h"

#include <stdio.h>

#include "Assert.h"
#include "color.h"
#include "scanf.h"
#include "logger.h"
#include "stack.h"

stack_function_errors_e StartCalculator(stack_t* calculator_stack)
{
    VERIFY_STACK_WITH_RETURN(calculator_stack);

    calculator_commands_e input_command = CALCULATOR_COMMAND_START;
    value_type intermediate_value = 0;

    while (input_command != CALCULATOR_COMMAND_HTL)
    {
        switch(input_command)
        {
            case CALCULATOR_COMMAND_START:
                input_command = ReadUserInput();
                break;

            case CALCULATOR_COMMAND_INCORRECT_COMMAND:
                printf(RED "Incorrect command.\n" STANDARD);
                input_command = CALCULATOR_COMMAND_START;
                break;

            case CALCULATOR_COMMAND_PUSH:
                input_command = ReadCoefficient(&intermediate_value);
                if (input_command == CALCULATOR_COMMAND_START)
                {
                    VERIFY_FUNCTION(StackPush(calculator_stack, intermediate_value));
                }
                break;

            case CALCULATOR_COMMAND_ADD:
                VERIFY_FUNCTION(StackAdd(calculator_stack));
                input_command = CALCULATOR_COMMAND_START;
                break;

            case CALCULATOR_COMMAND_SUB:
                VERIFY_FUNCTION(StackSub(calculator_stack));
                input_command = CALCULATOR_COMMAND_START;
                break;

            case CALCULATOR_COMMAND_MUL:
                VERIFY_FUNCTION(StackMul(calculator_stack));
                input_command = CALCULATOR_COMMAND_START;
                break;

            case CALCULATOR_COMMAND_DIV:
                VERIFY_FUNCTION(StackDiv(calculator_stack));
                input_command = CALCULATOR_COMMAND_START;
                break;

            case CALCULATOR_COMMAND_OUT:
                if (StackPop(calculator_stack, &intermediate_value) == STACK_FUNCTION_SUCCESS)
                {
                    printf("%d\n", intermediate_value); //ПОПКА-БУДЕТ-КРАСНАЯ - Переделаю
                }
                input_command = CALCULATOR_COMMAND_START;
                break;

            case CALCULATOR_COMMAND_PRINT:
                PrintOut(calculator_stack);
                input_command = CALCULATOR_COMMAND_START;
                break;

            case CALCULATOR_COMMAND_HTL:
                printf(GREEN "Vsyo poka\n" STANDARD);
                break;

            case CALCULATOR_COMMAND_BUFFER_OVERFLOW:
                printf(RED "Buffer overflow was occupied.\n" STANDARD);
                input_command = CALCULATOR_COMMAND_START;
                break;

            default: break;
        }
    }

    return STACK_FUNCTION_SUCCESS;
}

void PrintOut(stack_t* calculator_stack)
{
    for (size_t index = 1; index <= calculator_stack->capacity; index++)
        {
            if (index <= calculator_stack->size)
            {
                printf(GREEN "[%zu ELEMENT] %d \n" STANDARD, index, (calculator_stack->stack_data)[index]);
            }
            else
            {
                printf(RED"[%zu ELEMENT] NOTHING_HERE \n" STANDARD, index);
            }
        }
}

stack_function_errors_e
StackAdd(stack_t* swag)
{
    ASSERT(swag != NULL);

    VERIFY_STACK_WITH_RETURN(swag);

    value_type value_1 = 0;
    value_type value_2 = 0;

    if (swag->size < 2)
    {
        return STACK_FUNCTION_NOT_ENOUGH_ELEMENTS;
    }

    StackPop(swag, &value_1);
    StackPop(swag, &value_2);

    StackPush(swag, value_1 + value_2);

    VERIFY_STACK_WITH_RETURN(swag);

    return STACK_FUNCTION_SUCCESS;
}

stack_function_errors_e
StackSub(stack_t* swag)
{
    ASSERT(swag != NULL);

    VERIFY_STACK_WITH_RETURN(swag);

    value_type value_1 = 0;
    value_type value_2 = 0;

    if (swag->size < 2)
    {
        return STACK_FUNCTION_NOT_ENOUGH_ELEMENTS;
    }

    StackPop(swag, &value_1);
    StackPop(swag, &value_2);

    StackPush(swag, value_2 - value_1);

    VERIFY_STACK_WITH_RETURN(swag);

    return STACK_FUNCTION_SUCCESS;
}

stack_function_errors_e
StackMul(stack_t* swag)
{
    ASSERT(swag != NULL);

    VERIFY_STACK_WITH_RETURN(swag);

    value_type value_1 = 0;
    value_type value_2 = 0;

    if (swag->size < 2)
    {
        return STACK_FUNCTION_NOT_ENOUGH_ELEMENTS;
    }

    StackPop(swag, &value_1);
    StackPop(swag, &value_2);

    StackPush(swag, value_1 * value_2);

    VERIFY_STACK_WITH_RETURN(swag);

    return STACK_FUNCTION_SUCCESS;
}

stack_function_errors_e
StackDiv(stack_t* swag)
{
    ASSERT(swag != NULL);

    VERIFY_STACK_WITH_RETURN(swag);

    value_type value_1 = 0;
    value_type value_2 = 0;

    if (swag->size < 2)
    {
        return STACK_FUNCTION_NOT_ENOUGH_ELEMENTS;
    }

    StackPop(swag, &value_1);
    StackPop(swag, &value_2);

    StackPush(swag, value_2 / value_1);

    VERIFY_STACK_WITH_RETURN(swag);

    return STACK_FUNCTION_SUCCESS;
}

