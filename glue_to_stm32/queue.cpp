#include "queue.h"

using namespace std;

void vQueueDelete(QueueHandle_t xQueue)
{
    delete xQueue;
}
