#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "alu.h"
#include "uinter.h"

#define M_PIl          3.141592653589793238462643383279502884L 

dint_t
i_crt  (long double nom)
{
	dint_t res = { .low = nom,  .upp = nom };
	return res;
}

dint_t
i_crt2 (long double lim1, long double lim2)
{
	dint_t res = {	.low = fmin (lim1, lim2),
			.upp = fmax (lim1, lim2)  };
	return res;
}


dint_t
i_crt3 (long double nom, long double dev1, long double dev2)
{
	if (dev1 > dev2) {
		long double tmp = dev1;
		dev1 = dev2;
		dev2 = tmp;
	}
	dint_t res = {	.low = nom + dev1,
			.upp = nom + dev2 };
	return res;
}


dint_t *
i_copy (const dint_t *s)
{
	dint_t *res = malloc (sizeof (dint_t));
	*res = *s;
	return res;
}


dint_t
i_copy_val (const dint_t *s)
{
	dint_t res = {	.low = s -> low,
			.upp = s -> upp  };
	return res;	
}


void
i_xchg (dint_t *i1, dint_t *i2)
{
	dint_t tmp = *i1;
	*i1 = *i2;
	*i2 = tmp;
}


cmp_status_t
i_cmp (const dint_t *i1, const dint_t *i2)
{
	if (i1 -> low == i2 -> low
		&& i1 -> upp == i2 -> upp)
			return CMP_EQ | CMP_GE | CMP_LE | CMP_IN | CMP_OUT;
	if (i1 -> low >= i2 -> upp)
			return CMP_GT | CMP_NE;
	if (i1 -> low >= i2 -> low
		&& i1 -> upp >= i2 -> upp) return CMP_GE;
	if (i1 -> upp <= i2 -> low) 	   return CMP_LT | CMP_NE;
	if (i1 -> low <= i2 -> low
		&& i1 -> upp <= i2 -> upp) return CMP_LE;
	if (i1 -> low >= i2 -> low
		&& i1 -> upp <= i2 -> upp) return CMP_IN;
	if (i1 -> low <= i2 -> low
		&& i1 -> upp >= i2 -> upp) return CMP_OUT;
	return CMP_UNK;
}


dint_t *
i_add (dint_t *i1, const dint_t *i2)
{
	i1 -> low += i2 -> low;
	i1 -> upp += i2 -> upp;
	return i1;
}


dint_t *
i_sub (dint_t *i1, const dint_t *i2)
{
	long double low = i1 -> low;
	i1 -> low -= i2 -> upp;
	i1 -> upp -= low;
	return i1;
}


static dint_t *
array_min_max (int count, const long double arr[])
{
	dint_t *res = malloc (sizeof (dint_t));
	res -> low = arr[0];
	res -> upp = arr[0];
	int i;
	for (i = 1;  i < count;  i++) {
		if (res -> low > arr[i]) {
			res -> low = arr[i];
			continue;
		}
		if (res -> upp < arr[i])
			res -> upp = arr[i];
	}
	return res;
}


dint_t *
i_mul (dint_t *m1, const dint_t *m2)
{
	long double p[4];
	p[0] = m1 -> low * m2 -> low;
	p[1] = m1 -> low * m2 -> upp;
	p[2] = m1 -> upp * m2 -> low;
	p[3] = m1 -> upp * m2 -> upp;
	dint_t *from_arr = array_min_max(4, p);
	*m1 = *from_arr;
	free (from_arr);
	return m1;
}


dint_t *
i_div (dint_t *m1, const dint_t *m2)
{
	long double p[4];
	p[0] = m1 -> low / m2 -> low;
	p[1] = m1 -> low / m2 -> upp;
	p[2] = m1 -> upp / m2 -> low;
	p[3] = m1 -> upp / m2 -> upp;
	dint_t *from_arr = array_min_max(4, p);
	*m1 = *from_arr;
	free (from_arr);
	return m1;
}


dint_t *
i_inv (dint_t *s)
{
	long double tmp = s -> low;
	s -> low = 1.0L / s -> upp;
	s -> upp = 1.0L / tmp;
	return s;
}


dint_t *
i_inc (dint_t *s)
{
	s -> low ++;
	s -> upp ++;
	return s;
}


dint_t *
i_dec (dint_t *s)
{
	s -> low --;
	s -> upp --;
	return s;
}


dint_t *
i_pow (dint_t *s, long double idx)
{
	s -> low = powl (s -> low, idx);
	s -> upp = powl (s -> upp, idx);
	return s;
}


dint_t *
i_neg (dint_t *s)
{
	long double tmp = s -> low;
	s -> low = - s -> upp;
	s -> upp = - tmp;
	return s;
}


// Poisk minimuma funkcii na intervale metodom deleniya otrezka popolam
static long double
arg_min (long double (*f)(long double), const dint_t *s, long double error)
{
	unsigned iter = 0;
	long double res;
	long double middle, lpnt, rpnt, lval, rval;
	long double lbnd = s -> low;
	long double rbnd = s -> upp;
	do {
		middle = (lbnd + rbnd)/2;
		lpnt = middle - error;
		rpnt = middle + error;
		lval = f (lpnt);
		rval = f (rpnt);
		if (lval <= rval) {
			rbnd = rpnt;
			res = lpnt;
		}
		else {
			lbnd = lpnt;
			res = rpnt;
		}
		iter++;
		if (iter >= 10000000u) {
			ui_sndmes (MT_ERROR,
				"Previsheno chislo iteraciy pri poiske minimuma");
		}

	} while (rbnd - lbnd >= 2.1*error);
	return res;
}


static long double
sind (long double x)
{
	return sinl (x / 180.0L * M_PIl);
}


static long double
sind_neg (long double x)
{
	return -sind (x);
}


dint_t *
i_sin (dint_t *s)
{
	long double low = sind (arg_min (&sind, s, 0.000001L));
	long double upp = sind (arg_min (&sind_neg, s, 0.000001L));
	s -> low = low;
	s -> upp = upp;
	return s;
}


dint_t *
i_cos (dint_t *s)
{
	s -> low += 90.0L;
	s -> upp += 90.0L;
	return i_sin (s);
}


// tan = sqrt (1 / (cos^2) - 1)
dint_t *
i_tan (dint_t *s)
{
	dint_t tmp = *s;
	i_cos (&tmp);
	i_mul (&tmp, &tmp);
	s -> low = s -> upp = 1;
	i_div (s, &tmp);
	i_dec (s);
	return i_pow(s, 0.5L);
}


dint_t *
i_cot (dint_t *s)
{	
	dint_t *si = i_sin (i_copy (s));
	i_div (i_cos (s), si);
	free (si);
	return s;
}


static long double
asind (long double x)
{
	return asinl (x) / M_PIl * 180.0L;
}


static long double
asind_neg (long double x)
{
	return -asind (x);
}


dint_t *
i_asin (dint_t *s)
{
	long double low = asind (arg_min (&asind, s, 0.000001L));
	long double upp = asind (arg_min (&asind_neg, s, 0.000001L));
	s -> low = low;
	s -> upp = upp;
	return s;
}


// acos = 2 * asin (sqrt ((1 - x) / 2))
dint_t *
i_acos (dint_t *s)
{
	i_neg (s);
	i_inc (s);
	dint_t tmp = { .low = 2.0L, .upp = 2.0L };
	i_div (s, &tmp);
	i_pow (s, 0.5L);
	i_asin (s);
	return i_mul (s, &tmp);
}


static long double
atand (long double x)
{
	return atanl (x) / M_PIl * 180.0L;
}


static long double
atand_neg (long double x)
{
	return -atand (x);
}


dint_t *
i_atan (dint_t *s)
{
	long double low = atand (arg_min (&atand, s, 0.000001L));
	long double upp = atand (arg_min (&atand_neg, s, 0.000001L));
	s -> low = low;
	s -> upp = upp;
	return s;
}


// acot = atan (1 / x)
dint_t *
i_acot (dint_t *s)
{
	dint_t tmp = *s;
	s -> low = s -> upp = 1.0L;
	i_div (s, &tmp);
	return i_atan (s);
}


#define STR_SZ 20
char *
i_asstr (const dint_t *s)
{
	char *res = malloc (STR_SZ);
	snprintf (res, STR_SZ, "%.3Lf %.3Lf", s -> low, s -> upp);
	return res;
}
#undef STR_SZ


#define STR_SZ 4
char *
i_cmp_status_asstr (cmp_status_t s)
{
	char *res = malloc (STR_SZ);
	if ((s & CMP_EQ) != 0) strncpy (res, "EQ", STR_SZ);
	else if ((s & CMP_GT) != 0) strncpy (res, "GT", STR_SZ);
	else if ((s & CMP_GE) != 0) strncpy (res, "GE", STR_SZ);
	else if ((s & CMP_LT) != 0) strncpy (res, "LT", STR_SZ);
	else if ((s & CMP_LE) != 0) strncpy (res, "LE", STR_SZ);
	else if ((s & CMP_IN) != 0) strncpy (res, "IN", STR_SZ);
	else if ((s & CMP_OUT) != 0) strncpy (res, "OUT", STR_SZ);
	else if ((s & CMP_UNK) != 0) strncpy (res, "UNK", STR_SZ);
	return res;
}
#undef STR_SZ


//#define DEBUG_CORE
#ifdef DEBUG_CORE
void
prnt (const char *op, const dint_t *s)
{
	char *s_str = i_asstr (s);
	printf ("%s%s\n", op, s_str);
	free (s_str);
}

int
main (int argc, char *argv[])
{
	char *tmp_str;
	dint_t s, sres;
	s = i_crt2 (0.02, 1.2);
	prnt ("s = ", &s);
	sres = i_copy_val (&s);
	i_inv (&sres);
	prnt ("sres = inv(s) = ", &sres);
	tmp_str = i_cmp_status_asstr (i_cmp (&s, &sres));
	printf ("cmp (s, sres) = %s\n", tmp_str);
	free (tmp_str);
	i_inv (&sres);
	prnt ("sres = inv (sres) = ", &sres);
	return 0;
}
#endif		// DEBUG_CORE

