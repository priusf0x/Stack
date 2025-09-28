#include "scanf.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "Assert.h"
#include "color.h"
#include "stack.h"
#include "calculator.h"

const size_t PROGRAM_INPUT_BUFFER_SIZE = 20;
static char command[PROGRAM_INPUT_BUFFER_SIZE] = {0};

calculator_commands_e ReadUserInput()
{
    int character = 0;
    size_t count = 0;

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

    if (strcmp(command, "HTL") == 0)
    {
        return CheckIfSpaces(CALCULATOR_COMMAND_HTL);
    }
    else if (strcmp(command, "PUSH") == 0)
    {
        return CALCULATOR_COMMAND_PUSH;
    }
    else if (strcmp(command, "OUT") == 0)
    {
        return CheckIfSpaces(CALCULATOR_COMMAND_OUT);
    }
    else if (strcmp(command, "PRINT") == 0)
    {
        return CheckIfSpaces(CALCULATOR_COMMAND_PRINT);
    }
    else if (strcmp(command, "ADD") == 0)
    {
        return CheckIfSpaces(CALCULATOR_COMMAND_ADD);
    }
    else if (strcmp(command, "SUB") == 0)
    {
        return CheckIfSpaces(CALCULATOR_COMMAND_SUB);
    }
    else if (strcmp(command, "MUL") == 0)
    {
        return CheckIfSpaces(CALCULATOR_COMMAND_MUL);
    }
    else if (strcmp(command, "DIV") == 0)
    {
        return CheckIfSpaces(CALCULATOR_COMMAND_DIV);
    }
    else
    {
        ClearBuffer();
        return CALCULATOR_COMMAND_INCORRECT_COMMAND;
    }

}

calculator_commands_e ReadCoefficient(value_type* coefficient)
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

calculator_commands_e CheckIfSpaces(enum calculator_commands_e expected_state)
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

