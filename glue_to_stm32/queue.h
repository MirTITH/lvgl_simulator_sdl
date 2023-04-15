#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "task.h"

/**
 * Type by which queues are referenced.  For example, a call to xQueueCreate()
 * returns an QueueHandle_t variable that can then be used as a parameter to
 * xQueueSend(), xQueueReceive(), etc.
 */
struct QueueDefinition; /* Using old naming convention so as not to break kernel aware debuggers. */
typedef struct QueueDefinition *QueueHandle_t;

/**
 * Type by which queue sets are referenced.  For example, a call to
 * xQueueCreateSet() returns an xQueueSet variable that can then be used as a
 * parameter to xQueueSelectFromSet(), xQueueAddToSet(), etc.
 */
typedef struct QueueDefinition *QueueSetHandle_t;

/**
 * Queue sets can contain both queues and semaphores, so the
 * QueueSetMemberHandle_t is defined as a type to be used where a parameter or
 * return value can be either an QueueHandle_t or an SemaphoreHandle_t.
 */
typedef struct QueueDefinition *QueueSetMemberHandle_t;

/* For internal use only. */
#define queueSEND_TO_BACK  ((BaseType_t)0)
#define queueSEND_TO_FRONT ((BaseType_t)1)
#define queueOVERWRITE     ((BaseType_t)2)

/* For internal use only.  These definitions *must* match those in queue.c. */
#define queueQUEUE_TYPE_BASE               ((uint8_t)0U)
#define queueQUEUE_TYPE_SET                ((uint8_t)0U)
#define queueQUEUE_TYPE_MUTEX              ((uint8_t)1U)
#define queueQUEUE_TYPE_COUNTING_SEMAPHORE ((uint8_t)2U)
#define queueQUEUE_TYPE_BINARY_SEMAPHORE   ((uint8_t)3U)
#define queueQUEUE_TYPE_RECURSIVE_MUTEX    ((uint8_t)4U)

void vQueueDelete(QueueHandle_t xQueue);

#ifdef __cplusplus
}
#endif
