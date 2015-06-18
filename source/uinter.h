/*
 Output to user

 Copyright (c) 2015
 Loshkin A.A. <alswayer@ya.ru>
*/


#ifndef UINTER_H
#define UINTER_H


// UINTER_CLI, ...
#include "main.h"


typedef enum {
	MT_ERROR,  MT_WARN,  MT_RSLT,  MT_INFO
} msg_t;


#ifdef UINTER_CLI
typedef enum {
	MB_PRINT,  MB_PRINT_EXIT
} mes_behav_t;

mes_behav_t onerrors;
#endif  // UINTER_CLI


void
ui_sndmes (msg_t type, char* mes);


#endif  // ! UINTER_H
