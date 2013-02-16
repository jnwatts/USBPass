#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#include <stdio.h>
#include <avr/pgmspace.h>
#define DBG(msg, args...) printf_P(PSTR("%S:%d " msg "\r\n"), PSTR(__FILE__), __LINE__, ##args)
#else
#define DBG(msg, args...)
#endif

#endif // DEBUG_H
