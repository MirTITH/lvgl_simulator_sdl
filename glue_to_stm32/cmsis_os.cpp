#include "cmsis_os.h"
#include "get_tick.h"

uint32_t osKernelSysTick()
{
    return GetTickMs();
}
