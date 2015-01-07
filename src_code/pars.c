#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pars.h"
#include "addr.h"
#include "uinter.h"

char *ops[] = {"mov", "xchg",
		"out", "hlt",
		"add", "sub", "mul", "div", "inc", "dec", "inv",
		"sin", "cos", "tan", "cot", "asin", "acos", "atan", "acot",
		"jmp", "je", "jne", "jgt", "jge", "jlt", "jle", "jin", "jout",
		"call", "ret"};

static int prev_addr = 0;


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
	if (semi <= 0)  return 0;
	char labl [LABEL_SZ + 1];
	int iend = semi - 1;
	for (char *c = (*str)+iend;   c >= *str;   c--, iend--) {
		if (! isspace (*c))  break;
	}
	int len = (iend+1 > LABEL_SZ) ? LABEL_SZ : iend+1;
	memcpy (labl, *str, len);
	labl [len] = 0;
	// Korrektnost imeni metki
	if (! prs_isid_correct (labl))  {
		ui_sndmes (MT_ERROR, "Ne korrektnoe imya metki");
	}
	// Obrezka metki ot instrukcii
	*str += semi;
	while (isspace (* ++(*str)));
	return prev_addr = -ad_hash (labl);
}


static cmdcode_t
prs_cmd (char **str)
{
//	char *cmd, *cmd_it, *str_it;
//	str_it = *str;
//	cmdcode_t c;
//	for (c = MOV;  c <= HLT;  c++)  {
//		cmd = cmd_it = oc_cmdstr (c);
//		while (*cmd_it != 0  &&  *str_it != 0) {
//			if (*cmd_it != *str_it)  goto next_cmd;
//			cmd_it++;
//			str_it++;
//		}
//		if (*cmd_it == *str_it)  break;
//next_cmd:	free (cmd);
//	}
//	return c;
}


instr_t
parse (char *str)
{
	prs_uncomm (&str);
	int addr = prs_label (&str);
 	prs_cmd (&str);
	printf ("%d   >>>%s<<<\n", addr, str);
	if (strcmp (str, "hlt") == 0) exit (0);
}

