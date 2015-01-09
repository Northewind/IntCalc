#ifndef ADDR_H
#define ADDR_H

void
ad_push (int addr);

int
ad_pop ();

void
ad_freeall ();

int
ad_hash (char *str);

int
ad_hash_subs (char *start, char *end);

#endif // ! ADDR_H
