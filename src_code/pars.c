#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pars.h"
#include "addr.h"
#include "uinter.h"

#define ADDR_DFLT 0
#define CMD_ERR   (-1)


static int prev_addr = ADDR_DFLT;


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
	while (isspace (* --c));
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
prs_isid_correct (char *id)
{
	for (char *c = id;  *c;  c++) {
		if (! (isalnum (*c)  ||  *c == '_'
			|| *c == '.' ||  *c == '$'
			|| *c == '@' ))  return false;
	}
	return true;
}


static int
prs_label (char **str)
{
	int semi = prs_find (*str, ':');
	if (semi <= 0)  return ADDR_DFLT;
	char labl [LABEL_SZ + 1];
	int iend = semi - 1;
	for (char *c = (*str)+iend;   c >= *str;   c--, iend--) {
		if (! isspace (*c))  break;
	}
	int len = (iend+1 > LABEL_SZ) ? LABEL_SZ : iend+1;
	memcpy (labl, *str, len);
	labl [len] = 0;
	// Is label name correct
	if (! prs_isid_correct (labl))  {
		ui_sndmes (MT_ERROR, "Invalid label name");
	}
	// Cut off label from instruction
	*str += semi;
	while (isspace (* ++(*str)));
	return prev_addr = -ad_hash (labl);
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
			while (isspace(*str_it))  str_it++;
			*str = str_it;
			return c;
		}
	}
	return CMD_ERR;
}


static argset_type
prs_args (char **str, argset_t *as)
{
	return AS_NO;
}


#define INSTR_NOEXEC ((instr_t) { .addr = ADDR_NOEXEC })

instr_t
parse (char *str)
{
	// Uncommenting
	prs_uncomm (&str);
	if (*str == 0)  return INSTR_NOEXEC;
	// Parsing the label
	int addr = prs_label (&str);
	if (addr == ADDR_DFLT)
		addr = prev_addr;
	else
		prev_addr = addr;
	if (*str == 0)  return INSTR_NOEXEC;
	// Parsing the command
 	cmdcode_t cmd = prs_cmd (&str);
	if (cmd == CMD_ERR)  {
		ui_sndmes (MT_ERROR, "Unknown command");
		return INSTR_NOEXEC;
	}
	prev_addr = ADDR_DFLT;
	if (*str == 0) {
		if (cmd_argset_type (cmd) & AS_NO) {
			return (instr_t) { .addr=addr,
					   .opcode=cmd_to_opcode (cmd, AS_NO) };
		}
		else {
			ui_sndmes (MT_ERROR, "No arguments for command");
			return INSTR_NOEXEC;
		}
	}
	else {
		if (cmd_argset_type (cmd) & AS_NO) {
			ui_sndmes (MT_WARN, "Surplus arguments after command");
			return (instr_t) { .addr=addr,
					   .opcode=cmd_to_opcode (cmd, AS_NO) };
		}
	}
	// Parsing the args
	argset_t as;
	argset_type ast = prs_args (&str, &as);
	return INSTR_NOEXEC;
}

