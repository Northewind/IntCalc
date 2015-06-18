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
