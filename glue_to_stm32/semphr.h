#pragma once

#include "queue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef QueueHandle_t SemaphoreHandle_t;

#define semBINARY_SEMAPHORE_QUEUE_LENGTH ((uint8_t)1U)
#define semSEMAPHORE_QUEUE_ITEM_LENGTH   ((uint8_t)0U)
#define semGIVE_BLOCK_TIME               ((TickType_t)0U)

QueueHandle_t xSemaphoreCreateRecursiveMutex();
BaseType_t xSemaphoreTakeRecursive(QueueHandle_t xMutex, TickType_t xTicksToWait);
BaseType_t xSemaphoreGiveRecursive(QueueHandle_t xMutex);

#define vSemaphoreDelete(xSemaphore)

#ifdef __cplusplus
}
#endif
