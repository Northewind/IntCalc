#ifndef VARS_H
#define VARS_H

#include <stdlib.h>
#include "alu.h"

void
var_set (int var_id, dint_t var_value);

dint_t *
var_get (int var_id);

void
var_freeall ();

#endif  //!VARS_H

