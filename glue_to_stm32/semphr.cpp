#include "semphr.h"

#include <mutex>

using namespace std;

QueueHandle_t xSemaphoreCreateRecursiveMutex()
{
    auto handle = new recursive_mutex();
    return (QueueHandle_t)handle;
}

BaseType_t xSemaphoreTakeRecursive(QueueHandle_t xMutex, TickType_t xTicksToWait)
{
    (void)xTicksToWait;
    ((recursive_mutex *)xMutex)->lock();
    return pdPASS;
}

BaseType_t xSemaphoreGiveRecursive(QueueHandle_t xMutex)
{
    ((recursive_mutex *)xMutex)->unlock();
    return pdPASS;
}
