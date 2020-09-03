/**
 * \file    ioutils.h
 * \author  Tomáš Dulík
 * \date    16.2.2012
 * \brief   Miniknihovna pro načítání vstupu
 */

#ifndef IOUTILS_H_
#define IOUTILS_H_

#include <stdbool.h>

bool io_utils_get_string(char* c, int maxLen);
bool io_utils_get_char(char* c);
bool io_utils_get_long(long* val);
bool io_utils_get_double(double* val);
void io_utils_clear_stdin();

#endif  //_IOUTILS_H_
