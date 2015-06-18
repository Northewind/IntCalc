/*
 Output text storage (used in command like OUT "some text")

 Copyright (c) 2015
 Loshkin A.A. <alswayer@ya.ru>
*/


#ifndef OUTXT_H
#define OUTXT_H

int
ot_addtxt (char *t);

char *
ot_gettxt (int addr);

void
ot_freeall ();

#endif  //!OUTXT_H
