#ifndef PARS_H
#define PARS_H

#include "instr.h"

#define LABEL_SZ 15
#define ADDR_NOEXEC -1

instr_t
parse (char *str);

#endif // ! PARS_H
