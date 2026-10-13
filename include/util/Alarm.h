#ifndef UTIL_ALARM_H
#define UTIL_ALARM_H

#include "hel/common/ExplicitSingleton.h"
#include "revolution/os/OSAlarm.h"

namespace util {

class Alarm : public hel::common::ExplicitSingleton<Alarm> {
public:
    Alarm();
    virtual ~Alarm();

private:
    void init();
    void final();

    OSAlarm mAlarm;
};

}  // namespace util

#endif
