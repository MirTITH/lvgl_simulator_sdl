#include "get_tick.h"

#include <chrono>

using namespace std;

auto SYS_START_TIME = chrono::steady_clock().now();

uint32_t GetTickMs(){
    auto tick_ms = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock().now() - SYS_START_TIME);
    return tick_ms.count();
}
