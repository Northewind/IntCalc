#ifndef ADDR_H
#define ADDR_H

void
ad_push (int addr);

int
ad_pop ();

void
ad_free ();

int
ad_hash (char *str);

#endif //!ADDR_H
