#ifndef DEBUG_H
#define DEBUG_H

#ifdef __x86_64__
#include <stdio.h>
#define DBG(msg, args...) printf(msg, ##args)
#else
#define DBG(msg, args...)
#endif

#endif // DEBUG_H
