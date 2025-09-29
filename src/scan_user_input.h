#ifndef SCAN_USER_INPUT
#define SCAN_USER_INPUT

#include "stack.h"
#include "calculator.h"

struct command_t
{
    const char* command_name = NULL;
    calculator_commands_e return_value = CALCULATOR_COMMAND_INCORRECT_COMMAND;
};

bool                  ClearBuffer();
calculator_commands_e ReadUserInput(void);
calculator_commands_e ReadCoefficient(value_type* coefficient);
calculator_commands_e CheckIfSpaces(enum calculator_commands_e expected_state);

#endif //SCAN_USER_INPUT
