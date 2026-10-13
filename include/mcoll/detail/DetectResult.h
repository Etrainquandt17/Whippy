#ifndef MCOLL_DETAIL_DETECTRESULT_H
#define MCOLL_DETAIL_DETECTRESULT_H

#include "mcoll/detail/CollidedLog.h"
#include "types.h"

namespace mcoll {
namespace detail {

// TODO: members and the other functions; the size is the one its users reserve.
class DetectResult {
public:
    DetectResult();
    ~DetectResult();

    u32 collidedLogCount() const;
    CollidedLog collidedLog(u32 index) const;

private:
    u32 _0[0x5A0 / 4];
};

}
}

#endif
