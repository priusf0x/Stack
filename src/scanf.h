#ifndef SCAN_H
#define SCAN_H

#include "stack.h"
#include "calculator.h"

bool                  ClearBuffer();
calculator_commands_e ReadUserInput(void);
calculator_commands_e ReadCoefficient(value_type* coefficient);
calculator_commands_e CheckIfSpaces(enum calculator_commands_e expected_state);

#endif
