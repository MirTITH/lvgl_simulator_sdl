#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define portCHAR       char
#define portFLOAT      float
#define portDOUBLE     double
#define portLONG       long
#define portSHORT      short
#define portSTACK_TYPE uint32_t
#define portBASE_TYPE  long

typedef portSTACK_TYPE StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;

typedef uint32_t TickType_t;
#define portMAX_DELAY (TickType_t)0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
not need to be guarded with a critical section. */
#define portTICK_TYPE_IS_ATOMIC 1

#ifdef __cplusplus
}
#endif
