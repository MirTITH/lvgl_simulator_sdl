#pragma once

#include "stdint.h"
#include "portmacro.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*TaskFunction_t)(void *);
#define configSTACK_DEPTH_TYPE uint16_t
typedef void *TaskHandle_t;
typedef unsigned long UBaseType_t;

void vTaskDelete(void *);

int xTaskCreate(TaskFunction_t pxTaskCode,
                const char *const pcName, /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
                const configSTACK_DEPTH_TYPE usStackDepth,
                void *const pvParameters,
                UBaseType_t uxPriority,
                TaskHandle_t *const pxCreatedTask);

TickType_t xTaskGetTickCount(void);

void vTaskDelayUntil(TickType_t *const pxPreviousWakeTime, const TickType_t xTimeIncrement);

void vTaskDelay(const TickType_t xTicksToDelay);

#ifdef __cplusplus
}
#endif
