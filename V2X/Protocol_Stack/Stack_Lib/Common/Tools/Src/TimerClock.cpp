
#include "TimerClock.h"

#include <chrono>

int64_t GetTimeStamp()
{
    return std::chrono::system_clock::now().time_since_epoch().count();
}
