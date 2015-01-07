#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcode.h"

#define STR_SZ 7
char *
oc_asstr (opcode_t oc)
{
	char *res = malloc (STR_SZ);
	switch (oc) {
		case MOV_RC:
			strncpy (res, "MOV_RC", STR_SZ);
			break;
		case MOV_RR:
			strncpy (res, "MOV_RC", STR_SZ);
			break;
		case XCHG_RR:
			strncpy (res, "XCHG_RR", STR_SZ);
			break;
		case ADD_RC:
			strncpy (res, "ADD_RC", STR_SZ);
			break;
		case ADD_RR:
			strncpy (res, "ADD_RR", STR_SZ);
			break;
		case SUB_RC:
			strncpy (res, "SUB_RC", STR_SZ);
			break;
		case SUB_RR:
			strncpy (res, "SUB_RR", STR_SZ);
			break;
		case MUL_RC:
			strncpy (res, "MUL_RC", STR_SZ);
			break;
		case MUL_RR:
			strncpy (res, "MUL_RR", STR_SZ);
			break;
		case DIV_RC:
			strncpy (res, "DIV_RC", STR_SZ);
			break;
		case DIV_RR:
			strncpy (res, "DIV_RR", STR_SZ);
			break;
		case INV_R:
			strncpy (res, "INV_R", STR_SZ);
			break;
		case INC_R:
			strncpy (res, "INC_R", STR_SZ);
			break;
		case DEC_R:
			strncpy (res, "DEC_R", STR_SZ);
			break;
		case SIN_R:
			strncpy (res, "SIN_R", STR_SZ);
			break;
		case COS_R:
			strncpy (res, "COS_R", STR_SZ);
			break;
		case TAN_R:
			strncpy (res, "TAN_R", STR_SZ);
			break;
		case COT_R:
			strncpy (res, "COT_R", STR_SZ);
			break;
		case ASIN_R:
			strncpy (res, "ASIN_R", STR_SZ);
			break;
		case ACOS_R:
			strncpy (res, "ACOS_R", STR_SZ);
			break;
		case ATAN_R:
			strncpy (res, "ATAN_R", STR_SZ);
			break;
		case ACOT_R:
			strncpy (res, "ACOT_R", STR_SZ);
			break;
		case CMP_RC:
			strncpy (res, "CMP_RC", STR_SZ);
			break;
		case CMP_CR:
			strncpy (res, "CMP_CR", STR_SZ);
			break;
		case CMP_RR:
			strncpy (res, "CMP_RR", STR_SZ);
			break;
		case CMP_CC:
			strncpy (res, "CMP_CC", STR_SZ);
			break;
		case JMP_A:
			strncpy (res, "JMP_A", STR_SZ);
			break;
		case JE_A:
			strncpy (res, "JE_A", STR_SZ);
			break;
		case JNE_A:
			strncpy (res, "JNE_A", STR_SZ);
			break;
		case JGT_A:
			strncpy (res, "JGT_A", STR_SZ);
			break;
		case JGE_A:
			strncpy (res, "JGE_A", STR_SZ);
			break;
		case JLT_A:
			strncpy (res, "JLT_A", STR_SZ);
			break;
		case JLE_A:
			strncpy (res, "JLE_A", STR_SZ);
			break;
		case JIN_A:
			strncpy (res, "JIN_A", STR_SZ);
			break;
		case JOUT_A:
			strncpy (res, "JOUT_A", STR_SZ);
			break;
		case CALL_A:
			strncpy (res, "CALL_A", STR_SZ);
			break;
		case RET_NO:
			strncpy (res, "RET", STR_SZ);
			break;
		case OUT_A:
			strncpy (res, "OUT_A", STR_SZ);
			break;
		case OUT_R:
			strncpy (res, "OUT_R", STR_SZ);
			break;
		case OUT_C:
			strncpy (res, "OUT_C", STR_SZ);
			break;
		case HLT_NO:
			strncpy (res, "HLT", STR_SZ);
			break;
		default:
			strncpy (res, "UKNOWN", STR_SZ);
			break;
	}
	return res;
}
#undef STR_SZ


argset_t
oc_argset_type (opcode_t oc)
{
	argset_t res;
	switch (oc) {
		case INV_R:
		case INC_R:
		case DEC_R:
		case SIN_R:
		case COS_R:
		case TAN_R:
		case COT_R:
		case ASIN_R:
		case ACOS_R:
		case ATAN_R:
		case ACOT_R:
		case OUT_R:
			res = R;
			break;
		case MOV_RR:
		case XCHG_RR:
		case ADD_RR:
		case SUB_RR:
		case MUL_RR:
		case DIV_RR:
		case CMP_RR:
			res = RR;
			break;
		case MOV_RC:
		case ADD_RC:
		case SUB_RC:
		case MUL_RC:
		case DIV_RC:
		case CMP_RC:
			res = RC;
			break;
		case CMP_CC:
			res = CC;
			break;
		case OUT_C:
			res = C;
			break;
		case CMP_CR:
			res = CR;
			break;
		case JMP_A:
		case JE_A:
		case JNE_A:
		case JGT_A:
		case JGE_A:
		case JLT_A:
		case JLE_A:
		case JIN_A:
		case JOUT_A:
		case CALL_A:
		case OUT_A:
			res = A;
			break;
		case RET_NO:
		case HLT_NO:
			res = NO;
			break;
	}
	return res;
}


#define STR_SZ 3
char *
oc_argset_asstr (argset_t as)
{
	char *res = malloc (STR_SZ);
	switch (as) {
		case R:
			strncpy (res, "R", STR_SZ);
			break;
		case RR:
			strncpy (res, "RR", STR_SZ);
			break;
		case RC:
			strncpy (res, "RC", STR_SZ);
			break;
		case CC:
			strncpy (res, "CC", STR_SZ);
			break;
		case C:
			strncpy (res, "C", STR_SZ);
			break;
		case CR:
			strncpy (res, "CR", STR_SZ);
			break;
		case A:
			strncpy (res, "A", STR_SZ);
			break;
		case NO:
			strncpy (res, "NO", STR_SZ);
			break;
		default:
			strncpy (res, "UK", STR_SZ);
	}
	return res;
}
#undef STR_SZ


#define STR_SZ 5
char *
oc_cmdstr (cmdcode_t cc)
{
	char *res = malloc (STR_SZ);
	switch (cc) {
		case MOV:
			strncpy (res, "mov", STR_SZ);
			break;
		case XCHG:
			strncpy (res, "xchg", STR_SZ);
			break;
		case ADD:
			strncpy (res, "add", STR_SZ);
			break;
		case SUB:
			strncpy (res, "sub", STR_SZ);
			break;
		case MUL:
			strncpy (res, "mul", STR_SZ);
			break;
		case DIV:
			strncpy (res, "div", STR_SZ);
			break;
		case INV:
			strncpy (res, "inv", STR_SZ);
			break;
		case INC:
			strncpy (res, "inc", STR_SZ);
			break;
		case DEC:
			strncpy (res, "dec", STR_SZ);
			break;
		case SIN:
			strncpy (res, "sin", STR_SZ);
			break;
		case COS:
			strncpy (res, "cos", STR_SZ);
			break;
		case TAN:
			strncpy (res, "tan", STR_SZ);
			break;
		case COT:
			strncpy (res, "cot", STR_SZ);
			break;
		case ASIN:
			strncpy (res, "asin", STR_SZ);
			break;
		case ACOS:
			strncpy (res, "acos", STR_SZ);
			break;
		case ATAN:
			strncpy (res, "atan", STR_SZ);
			break;
		case ACOT:
			strncpy (res, "acot", STR_SZ);
			break;
		case CMP:
			strncpy (res, "cmp", STR_SZ);
			break;
		case JMP:
			strncpy (res, "jmp", STR_SZ);
			break;
		case JE:
			strncpy (res, "je", STR_SZ);
			break;
		case JNE:
			strncpy (res, "jne", STR_SZ);
			break;
		case JGT:
			strncpy (res, "jgt", STR_SZ);
			break;
		case JGE:
			strncpy (res, "jge", STR_SZ);
			break;
		case JLT:
			strncpy (res, "jlt", STR_SZ);
			break;
		case JLE:
			strncpy (res, "jle", STR_SZ);
			break;
		case JIN:
			strncpy (res, "jin", STR_SZ);
			break;
		case JOUT:
			strncpy (res, "jout", STR_SZ);
			break;
		case CALL:
			strncpy (res, "call", STR_SZ);
			break;
		case RET:
			strncpy (res, "ret", STR_SZ);
			break;
		case OUT:
			strncpy (res, "out", STR_SZ);
			break;
		case HLT:
			strncpy (res, "hlt", STR_SZ);
			break;
		default:
			strncpy (res, "uknw", STR_SZ);
			break;
	}
	return res;
}
#undef STR_SZ



//#define DEBUG_OPCODE
#ifdef DEBUG_OPCODE
int
main ()
{
	char *ocstr, *asstr;
	for (int i = 0;  i < 40;  i++) {
		ocstr = oc_asstr (i);
		asstr = oc_argset_asstr (oc_argset_type (i));
		printf ("opcode: 0x%X  %s  argset: %s\n", i, ocstr, asstr);
		free (ocstr);
		free (asstr);
	}
	return 0;
}
#endif  //DEBUG_OPCODE
