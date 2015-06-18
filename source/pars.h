/*
 Instruction parser

 Copyright (c) 2015
 Loshkin A.A. <alswayer@ya.ru>
*/


#ifndef PARS_H
#define PARS_H

#include "instr.h"

#define LABEL_SZ 32
#define ADDR_NOEXEC -1

instr_t
parse (char *str);

#endif // ! PARS_H
