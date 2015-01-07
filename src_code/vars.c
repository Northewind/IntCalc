#include <stdio.h>
#include "vars.h"


typedef struct vars_t {
	int id;
	dint_t value;
	struct vars_t *prev;
	struct vars_t *next;
} *vars_t;


static vars_t vars = NULL;
static vars_t vars_end = NULL;


static vars_t
var_add (int var_id, dint_t var_value)
{
	vars_t new = malloc (sizeof (struct vars_t));
	new -> id = var_id;
	new -> value = var_value;
	new -> next = NULL;
	if (! vars) {
		new -> prev = NULL;
		vars = vars_end = new;
	}
	else {
		new -> prev = vars_end;
		vars_end -> next = new;
		vars_end = new;
	}
	return new;
}


void
var_set (int var_id, dint_t var_value)
{
	dint_t *var = var_get (var_id);
	*var = var_value;
}


dint_t *
var_get (int var_id)
{
	for (vars_t res = vars;  res;  res = res -> next) {
		if (res -> id == var_id)  return & res -> value;
	}
	var_add (var_id, i_crt2(0,0));
	return & vars_end -> value;
}


char *
var_asstr (int var_id)
{
	dint_t *varval = var_get (var_id);
	return i_asstr (varval);
}


void
var_prnall ()
{
	char *varstr;
	for (vars_t var = vars;  var;  var = var -> next) {
		varstr = i_asstr (& var -> value);
		printf ("var: %d   val: %s\n", var -> id, varstr);
		free (varstr);
	}
}


void
var_freeall ()
{
	vars_t cur = vars;
	vars_t tmp;
	while (cur) {
		tmp = cur -> next;
		free (cur);
		cur = tmp;
	}
	vars = vars_end = NULL;
}


//#define DEBUG_VARS
#ifdef DEBUG_VARS
int
main ()
{
	dint_t *v1 = var_get (1);
	dint_t v2 = i_crt2 (10,10.4);
	var_set (2, v2);
	dint_t v3 = i_copy_val (&v2);
	var_set (3, v3);
	i_mul (var_get (3), var_get (2));
	var_set (2, i_crt2 (49.8, 50.2));
	var_prnall ();
	return 0;
}
#endif  //DEBUG_VARS
