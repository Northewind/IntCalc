/*
 Interpreter input

 Copyright (c) 2015
 Loshkin A.A. <alswayer@ya.ru>
*/


#ifndef INTERPR_H
#define INTERPR_H


#define INFO_VERSION  ("\
icalc (interval calculator) 0.5\n\
Copyright (C) 2015 Alexander Loshkin\n\
This program is free software. It comes with ABSOLUTELY NO WARRANTY.\n\
")


#define INFO_HELP ("\
Usage: icalc [parameters]\n\
  Interval calculator-intepreter with assembly syntax.\n\
  It reads stdin and write into stdout.\n\
    Parameters:\n\
    -h, --help      This help\n\
    -v, --version   Version info\n\
    -W              Exit on errors\n\
\n\
    Supported commands:\n\
      mov, xchg,\n\
      add, sub, mul, div, neg, sqrt, inv, inc, dec,\n\
      sin, cos, tan, cot, asin, acos, atan, acot,\n\
      jmp, cmp, je, jne, jgt, jge, jlt, jle, jin, jout,\n\
      nop, hlt, out, free, ret, call.\n\
")

#define UINTER_CLI

#endif  // ! INTERPR_H
