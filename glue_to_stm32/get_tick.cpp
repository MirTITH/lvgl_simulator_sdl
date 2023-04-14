#include "get_tick.h"

#include <chrono>
#include <mutex>

using namespace std;

static mutex TickMutex;
auto SYS_START_TIME = chrono::steady_clock().now();

uint32_t GetTickMs()
{
    TickMutex.lock();
    auto tick_ms = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock().now() - SYS_START_TIME);
    TickMutex.unlock();
    return tick_ms.count();
}
