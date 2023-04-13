#include "task.h"
#include "get_tick.h"
#include <chrono>
#include <SDL2/SDL_thread.h>
// #include <thread>
#include <unistd.h>

using namespace std;

typedef struct {
    TaskFunction_t pxTaskCode;
    void *const pvParameters;
} SdlThreadGlue_t;

static int SDL_ThreadGlueEntry(void *data)
{
    ((SdlThreadGlue_t *)data)->pxTaskCode(((SdlThreadGlue_t *)data)->pvParameters);
    return 0;
}

void vTaskDelete(void *)
{
}

int xTaskCreate(TaskFunction_t pxTaskCode, const char *const pcName, const configSTACK_DEPTH_TYPE usStackDepth, void *const pvParameters, UBaseType_t uxPriority, TaskHandle_t *const pxCreatedTask)
{
    (void)usStackDepth;
    (void)uxPriority;
    (void)pxCreatedTask;
    auto param = new SdlThreadGlue_t{pxTaskCode, pvParameters};
    SDL_CreateThread(SDL_ThreadGlueEntry, pcName, param);
    return 0;
}

TickType_t xTaskGetTickCount(void)
{
    return GetTickMs();
}

void vTaskDelayUntil(TickType_t *const pxPreviousWakeTime, const TickType_t xTimeIncrement)
{
    int64_t delta_time = *pxPreviousWakeTime + xTimeIncrement - GetTickMs();
    if (delta_time > 0) {
        usleep(delta_time * 1000);
    }
    *pxPreviousWakeTime = GetTickMs();
}

void vTaskDelay(const TickType_t xTicksToDelay)
{
    usleep(xTicksToDelay * 1000);
    // this_thread::sleep_for(chrono::milliseconds(xTicksToDelay));
}
