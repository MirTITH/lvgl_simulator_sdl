#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

void StartLvglThread();
void LvglLock();
void LvglUnlock();

#ifdef __cplusplus
}
#endif
