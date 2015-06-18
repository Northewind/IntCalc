/*
 All interval arithmetic and logics operations

 Copyright (c) 2015
 Loshkin A.A. <alswayer@ya.ru>
*/


#ifndef ALU_H
#define ALU_H

typedef struct {
	long double low;
	long double upp;
} dint_t;


typedef enum cmp_status {
	CMP_UNK=0,  CMP_EQ=2,   CMP_NE=4,   CMP_GT=8,   CMP_GE=16,
	CMP_LT=32,  CMP_LE=64,  CMP_IN=128, CMP_OUT=256
} cmp_status_t;


dint_t
i_crt  (long double nom);

dint_t
i_crt2 (long double lim1, long double lim2);

dint_t
i_crt3 (long double nom, long double dev1, long double dev2);

void
i_xchg (dint_t *i1, dint_t *i2);

cmp_status_t
i_cmp (const dint_t *i1, const dint_t *i2);

dint_t *
i_add (dint_t *i1, const dint_t *i2);

dint_t *
i_sub (dint_t *i1, const dint_t *i2);

dint_t *
i_mul (dint_t *i1, const dint_t *i2);

dint_t *
i_div (dint_t *i1, const dint_t *i2);

dint_t *
i_inv (dint_t *s);

dint_t *
i_inc (dint_t *s);

dint_t *
i_dec (dint_t *s);

dint_t *
i_neg (dint_t *s);

dint_t *
i_pow (dint_t *s, long double idx);

dint_t *
i_sin (dint_t *s);

dint_t *
i_cos (dint_t *s);

dint_t *
i_tan (dint_t *s);

dint_t *
i_cot (dint_t *s);

dint_t *
i_asin (dint_t *s);

dint_t *
i_acos (dint_t *s);

dint_t *
i_atan (dint_t *s);

dint_t *
i_acot (dint_t *s);

char *
i_asstr (const dint_t *s);


#endif  // ! ALU_H
