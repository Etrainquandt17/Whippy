#ifndef UTIL_ISTATECALLBACK_H
#define UTIL_ISTATECALLBACK_H

namespace util {

class IStateChanger;
class StateChangerBase;

class IStateCallback {
public:
    virtual ~IStateCallback();
    virtual void onStateChanged(const IStateChanger& changer) = 0;
};

}  // namespace util

#endif
