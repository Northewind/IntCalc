#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "alu.h"
#include "uinter.h"

#define M_PIl          3.141592653589793238462643383279502884L 
#define COMP_ERROR     0.000000001L

dint_t
i_crt  (long double nom)
{
	return (dint_t) { .low = nom,  .upp = nom };
}

dint_t
i_crt2 (long double lim1, long double lim2)
{
	if (lim1 > lim2) {
		long double tmp = lim1;
		lim1 = lim2;
		lim2 = tmp;
	}
	return (dint_t) { .low = lim1,  .upp = lim2 };
}


dint_t
i_crt3 (long double nom, long double dev1, long double dev2)
{
	if (dev1 > dev2) {
		long double tmp = dev1;
		dev1 = dev2;
		dev2 = tmp;
	}
	return (dint_t) { .low = nom + dev1,
			  .upp = nom + dev2 };
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
		&& i1 -> upp >= i2 -> upp)
			return CMP_GE;
	if (i1 -> upp <= i2 -> low)
			return CMP_LT | CMP_NE;
	if (i1 -> low <= i2 -> low
		&& i1 -> upp <= i2 -> upp)
			return CMP_LE;
	if (i1 -> low >= i2 -> low
		&& i1 -> upp <= i2 -> upp)
			return CMP_IN;
	if (i1 -> low <= i2 -> low
		&& i1 -> upp >= i2 -> upp)
			return CMP_OUT;
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
	i1 -> low -= i2 -> upp;
	i1 -> upp -= i2 -> low;
	return i1;
}


static dint_t
array_min_max (int count, const long double arr[])
{
	dint_t res = { .low = arr[0],   .upp = arr[0] };
	for (int i = 1;  i < count;  i++) {
		if (arr[i] < res.low) 
			res.low = arr[i];
		else if (arr[i] > res.upp)
			res.upp = arr[i];
	}
	return res;
}


dint_t *
i_mul (dint_t *m1, const dint_t *m2)
{
	long double p[] = {
		m1 -> low * m2 -> low,
		m1 -> low * m2 -> upp,
		m1 -> upp * m2 -> low,
		m1 -> upp * m2 -> upp };
	*m1 = array_min_max (4, p);
	return m1;
}


dint_t *
i_div (dint_t *m1, const dint_t *m2)
{
	long double p[] = {
		m1 -> low / m2 -> low,
		m1 -> low / m2 -> upp,
		m1 -> upp / m2 -> low,
		m1 -> upp / m2 -> upp };
	*m1 = array_min_max (4, p);
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


// Find minimum of function f in interval s using bisection method
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
			ui_sndmes (MT_ERROR, "Max iterations reached");
			break;
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
	long double low = sind (arg_min (&sind, s, COMP_ERROR));
	long double upp = sind (arg_min (&sind_neg, s, COMP_ERROR));
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
	i_cos (s);
	i_mul (s, s);
	i_inv (s);
	i_dec (s);
	return i_pow (s, 0.5L);
}


dint_t *
i_cot (dint_t *s)
{	
	dint_t si = *s;
	i_div (i_cos (s), i_sin (&si));
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
	long double low = asind (arg_min (&asind, s, COMP_ERROR));
	long double upp = asind (arg_min (&asind_neg, s, COMP_ERROR));
	s -> low = low;
	s -> upp = upp;
	return s;
}


// acos x = 2 * asin (sqrt ((1 - x) / 2))
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
	long double low = atand (arg_min (&atand, s, COMP_ERROR));
	long double upp = atand (arg_min (&atand_neg, s, COMP_ERROR));
	s -> low = low;
	s -> upp = upp;
	return s;
}


// acot x = atan (1 / x)
dint_t *
i_acot (dint_t *s)
{
	i_inv (s);
	return i_atan (s);
	// Other way: acot x = pi/2 - atan (x)
}


#define STR_SZ 20
char *
i_asstr (const dint_t *s)
{
	char *res = malloc (STR_SZ);
	if (s -> low  ==  s -> upp)
		snprintf (res, STR_SZ, "%.3Lf", s -> low);
	else
		snprintf (res, STR_SZ, "%.3Lf  %.3Lf", s -> low, s -> upp);
	return res;
}
#undef STR_SZ
