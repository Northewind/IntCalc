#ifndef UINTER_H
#define UINTER_H


typedef enum {
	MT_ERROR,  MT_WARN,  MT_RSLT,  MT_INFO
} msg_t;


void
ui_sndmes (msg_t type, char* mes);


#endif  // ! UINTER_H
