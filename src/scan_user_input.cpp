#include "scan_user_input.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "Assert.h"
#include "color.h"
#include "stack.h"
#include "calculator.h"

const size_t PROGRAM_INPUT_BUFFER_SIZE = 20;
static char command[PROGRAM_INPUT_BUFFER_SIZE] = {0};
static const size_t commands_count = 8;


calculator_commands_e
ReadUserInput()
{
    command_t commands_array[commands_count] = {
        {.command_name = "HTL",   .return_value = CALCULATOR_COMMAND_HTL},
        {.command_name = "PUSH",  .return_value = CALCULATOR_COMMAND_PUSH},
        {.command_name = "OUT",   .return_value = CALCULATOR_COMMAND_OUT},
        {.command_name = "PRINT", .return_value = CALCULATOR_COMMAND_PRINT},
        {.command_name = "ADD",   .return_value = CALCULATOR_COMMAND_ADD},
        {.command_name = "SUB",   .return_value = CALCULATOR_COMMAND_SUB},
        {.command_name = "MUL",   .return_value = CALCULATOR_COMMAND_MUL},
        {.command_name = "DIV",   .return_value = CALCULATOR_COMMAND_DIV}};

    int character = 0;
    size_t count = 0;
    calculator_commands_e read_command = CALCULATOR_COMMAND_INCORRECT_COMMAND;

    memset(command, 0, PROGRAM_INPUT_BUFFER_SIZE);

    while ((character = getchar()) != '\n' && character != ' ' && count < PROGRAM_INPUT_BUFFER_SIZE)
    {
        command[count] = (char)character;
        count++;
    }

    ungetc(character, stdin);

    if (count == PROGRAM_INPUT_BUFFER_SIZE)
    {
        return CALCULATOR_COMMAND_BUFFER_OVERFLOW;
    }

    for (size_t index = 0; index < commands_count; index++)
    {
        if (strcmp(command, commands_array[index].command_name) == 0)
        {
            read_command = commands_array[index].return_value;
            break;
        }
    }

    switch(read_command)
    {
        case CALCULATOR_COMMAND_START:
            return CALCULATOR_COMMAND_START;

        case CALCULATOR_COMMAND_HTL:
            return CheckIfSpaces(CALCULATOR_COMMAND_HTL);

        case CALCULATOR_COMMAND_OUT:
            return CheckIfSpaces(CALCULATOR_COMMAND_OUT);

        case CALCULATOR_COMMAND_PRINT:
            return CheckIfSpaces(CALCULATOR_COMMAND_PRINT);

        case CALCULATOR_COMMAND_ADD:
            return CheckIfSpaces(CALCULATOR_COMMAND_ADD);

        case CALCULATOR_COMMAND_SUB:
            return CheckIfSpaces(CALCULATOR_COMMAND_SUB);

        case CALCULATOR_COMMAND_MUL:
            return CheckIfSpaces(CALCULATOR_COMMAND_MUL);

        case CALCULATOR_COMMAND_DIV:
            return CheckIfSpaces(CALCULATOR_COMMAND_DIV);

        case CALCULATOR_COMMAND_PUSH:
            return CALCULATOR_COMMAND_PUSH;

        case CALCULATOR_COMMAND_INCORRECT_COMMAND:
            ClearBuffer();
            return CALCULATOR_COMMAND_INCORRECT_COMMAND;

        case CALCULATOR_COMMAND_BUFFER_OVERFLOW:
            ClearBuffer();
            return CALCULATOR_COMMAND_BUFFER_OVERFLOW;

        default:
            printf("Sorry, Some **** was happened.\n");
            return CALCULATOR_COMMAND_INCORRECT_COMMAND;
    }
}

calculator_commands_e
ReadCoefficient(value_type* coefficient)
{
    ASSERT(coefficient != NULL);

    if (scanf("%d", coefficient) != 1)
    {
        ClearBuffer();
        return CALCULATOR_COMMAND_INCORRECT_COMMAND;
    }

    return CheckIfSpaces(CALCULATOR_COMMAND_START);
}

bool ClearBuffer()
{
    bool flag = false;
    int character = 0;
    while ((character = getchar()) != '\n' && character != EOF)
    {
        if (!isspace(character))
        {
            flag = true;
        }
    }

    return flag;
}

calculator_commands_e
CheckIfSpaces(enum calculator_commands_e expected_state)
{
    if (ClearBuffer())
    {
        return CALCULATOR_COMMAND_INCORRECT_COMMAND;
    }
    else
    {
        return expected_state;
    }
}

