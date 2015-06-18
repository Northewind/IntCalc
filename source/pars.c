#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pars.h"
#include "addr.h"
#include "uinter.h"
#include "outxt.h"

#define INSTR_NOEXEC  ((instr_t) { .addr = ADDR_NOEXEC })


typedef enum {
	AT_R, AT_C, AT_A, AT_S, AT_UNDEF
} argtype_t;


static void
prs_uncomm (char **str)
{
	while (isspace (**str))  (*str)++;
	bool inqout = false;
	char *c;
	for (c = *str;  *c;  c++) {
		if (*c == '"')	  inqout = ! inqout;
		if (*c == ';'  &&  ! inqout)   break;
	}
	c--;
	while (isspace (*c)  &&  c >= *str)  c--;
	c [1] = 0;
}


// Find first character ch in string str out of qoutes
static int
prs_find (char *str, char ch)
{
	bool inqout;
	char *c;
	for (c = str,  inqout = false;   *c;   c++) {
		if  (*c == '"')   inqout = ! inqout;
		if  (*c == ch  &&  ! inqout) {
			return c - str;
		}
	}
	return -1;
}


static bool
prs_idchar (char c)
{
	return  isalnum (c)  ||  c == '_'
		|| c == '.'  ||  c == '$'  ||  c == '@';
}


static bool
prs_isid_correct (char *id)
{
	for (char *c = id;  *c;  c++) {
		if (! prs_idchar (*c))  return false;
	}
	return true;
}


static int
prs_label (char **str)
{
	int semi = prs_find (*str, ':');
	if (semi <= 0)  return ad_getnew ();
	char *beg = *str;
	char *end = beg + semi;
	while (isspace (*--end));
	*++end = 0;
	// Is label name correct
	if (! prs_isid_correct (beg))  {
		ui_sndmes (MT_ERROR, "Invalid label name");
	}
	if (end - beg  >  LABEL_SZ)  {
		ui_sndmes (MT_WARN, "Label name too long");
	}
	// Cut off label from instruction
	*str += semi;
	while (isspace (*++*str));
	return ad_hash (beg);
}


static cmdcode_t
prs_cmd (char **str)
{
	const char *cmd;
	char *str_it;
	cmdcode_t c;
	for (c = MOV;  c <= HLT;  c++)  {
		cmd = cmd_str (c);
		str_it = *str;
		while (*cmd == *str_it  &&  *str_it != 0) {
			cmd++;
			str_it++;
		}
		if (*cmd == 0)  {
			while (isspace (*str_it))  str_it++;
			*str = str_it;
			return c;
		}
	}
	return CMD_ERROR;
}


static bool
prs_argend (char c)
{
	return isspace (c)  ||  c == 0  ||  c == ',';
}


static argtype_t
prs_arg_r (char **str, int *val)
{
	argtype_t res = AT_UNDEF;
	if (**str == 'r') {
		char *beg = *str;
		while (isdigit (*++*str));
		if (prs_idchar (**str)) {
			// Label, starting with 'r'
			while (prs_idchar (**str))  ++*str;
			if (prs_argend (**str))  {
				*val = ad_hash_subs (beg, *str);
				res = AT_A;
			}
		}
		else if (prs_argend (**str)  &&  ++beg != *str) {
			// Register
			char tmp = **str;
			**str = 0;
			*val = atoi (beg);
			**str = tmp;
			res = AT_R;
		}
	}
	return res;
}


static argtype_t
prs_arg_txt (char **str, int *addr)
{
	if (**str != '"')  return AT_UNDEF;
	char *beg = *str;
	while (*++*str != '"'  &&  **str);
	if (**str)  {
		int sz = *str - beg;
		char *txt = malloc (sz);
		strncpy (txt, beg+1, sz-1);
		txt [sz-1] = 0;
		*addr = ot_addtxt (txt);
		++*str;
		return AT_S;
	}
	return AT_UNDEF;
}


static argtype_t
prs_arg_a (char **str, int *addr)
{
	if (! prs_idchar (**str))  return AT_UNDEF;
	char *beg = *str;
	while (prs_idchar (*++*str));
	char tmp = **str;
	**str = 0;
	*addr = ad_hash (beg);
	**str = tmp;
	return AT_A;
}


static double
prs_arg_num (char **str)
{
	char *nstr = *str;
	if (**str == '-'  ||  **str == '+')  ++*str;
	if (! isdigit (**str))  return 0.0/0.0;
	while (isdigit (*++*str));
	if (**str == '.')  ++*str;
	while (isdigit (**str))  ++*str;
	if (prs_argend (**str)) {
		char tmp = **str;
		**str = 0;
		double num = atof (nstr);
		**str = tmp;
		while (isspace (**str))  ++*str;
		return num;
	}
	return 0.0/0.0;
}


static argtype_t
prs_arg_dint (char **str, dint_t *val)
{
	double n1 = prs_arg_num (str);
	if (n1 != n1)  return AT_UNDEF;
	double n2 = prs_arg_num (str);
	if (n2 != n2) {
		*val = i_crt (n1);
		return AT_C;
	}
	double n3 = prs_arg_num (str);
	if (n3 != n3) {
		*val = i_crt2 (n1, n2);
		return AT_C;
	}
	*val = i_crt3 (n1, n2, n3);
	return AT_C;
}


static argtype_t
prs_arg (char **str, void *val)
{
	argtype_t at;
	if (**str == 'r')
		at = prs_arg_r (str, val);
	else if (**str == '"')
		at = prs_arg_txt (str, val);
	else if (isdigit (**str)  ||  **str == '-'  ||  **str == '+')
		at = prs_arg_dint (str, val);
	else if (prs_idchar (**str))
		at = prs_arg_a (str, val);
	else
		at = AT_UNDEF;
	while (isspace (**str))  ++*str;
	return at;
}


static argset_type
prs_args (char **str, argset_t *as)
{
	if (**str == 0)  return AS_NO;
	// First arg
	char val1 [sizeof (dint_t)];
	argtype_t at1 = prs_arg (str, val1);
	if (**str == 0) {
		switch (at1) {
			case AT_R:
				memcpy (&(as -> as_r.r), val1, sizeof (int));
				return AS_R;
			case AT_A:
				memcpy (&(as -> as_a.a), val1, sizeof (int));
				return AS_A;
			case AT_S:
				memcpy (&(as -> as_s.s), val1, sizeof (int));
				return AS_S;
			case AT_C:
			case AT_UNDEF:
				return AS_ERROR;
		}
	}
	// Delimiter
	if (**str == ',')  ++*str;
	while (isspace (**str))  ++*str;
	// Second arg
	char val2 [sizeof (dint_t)];
	argtype_t at2 = prs_arg (str, val2);
	if (**str)  return AS_ERROR;
	switch (at1) {
		case AT_R:
			switch (at2) {
				case AT_R:
					memcpy (&(as -> as_rr.r1), val1, sizeof (int));
					memcpy (&(as -> as_rr.r2), val2, sizeof (int));
					return AS_RR;
				case AT_C:
					memcpy (&(as -> as_rc.r), val1, sizeof (int));
					memcpy (&(as -> as_rc.c), val2, sizeof (dint_t));
					return AS_RC;
				case AT_A:
				case AT_S:
				case AT_UNDEF:
					return AS_ERROR;
			}
		case AT_C:
			switch (at2) {
				case AT_R:
					memcpy (&(as -> as_cr.c), val1, sizeof (dint_t));
					memcpy (&(as -> as_cr.r), val2, sizeof (int));
					return AS_CR;
				case AT_C:
					memcpy (&(as -> as_cc.c1), val1, sizeof (dint_t));
					memcpy (&(as -> as_cc.c2), val2, sizeof (dint_t));
					return AS_CC;
				case AT_A:
				case AT_S:
				case AT_UNDEF:
					return AS_ERROR;
			}
		case AT_A:
		case AT_S:
		case AT_UNDEF:
			return AS_ERROR;
	}
	return AS_ERROR;
}


instr_t
parse (char *str)
{
	// Uncommenting and label parsing
	prs_uncomm (&str);
	if (*str == 0)  return INSTR_NOEXEC;
	int addr = prs_label (&str);
	if (*str == 0)  return (instr_t) { .addr = addr,
					   .opcode = NOP_NO };
	// Parsing the command
 	cmdcode_t cmd = prs_cmd (&str);
	if (cmd == CMD_ERROR)  {
		ui_sndmes (MT_ERROR, "Unknown command");
		return INSTR_NOEXEC;
	}
	if (*str == 0) {
		if (cmd_argset_type (cmd) & AS_NO)
			return (instr_t) { .addr = addr,
					   .opcode = cmd_to_opcode (cmd, AS_NO) };
		else {
			ui_sndmes (MT_ERROR, "No arguments for command");
			return INSTR_NOEXEC;
		}
	}
	else if (cmd_argset_type (cmd) & AS_NO) {
			ui_sndmes (MT_WARN, "Surplus arguments after command");
			return (instr_t) { .addr = addr,
					   .opcode = cmd_to_opcode (cmd, AS_NO) };
		}
	// Parsing the args
	argset_t as;
	argset_type ast = prs_args (&str, &as);
	if (ast == AS_ERROR) {
		ui_sndmes (MT_ERROR, "Invalid arguments");
		return INSTR_NOEXEC;
	}
	opcode_t opcode = cmd_to_opcode (cmd, ast);
	if (opcode == OPCODE_ERROR)  {
		ui_sndmes (MT_ERROR, "Invalid arguments");
		return INSTR_NOEXEC;
	}
	return (instr_t) { .addr = addr,
			   .opcode = opcode,
			   .args = as };
}
