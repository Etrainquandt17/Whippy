#ifndef MCOLL_DETAIL_COLLIDEDLOG_H
#define MCOLL_DETAIL_COLLIDEDLOG_H

#include "mcoll/detail/CollidedInfo.h"
#include "types.h"

namespace mcoll {
namespace detail {

// TODO: members and the other functions; the size is the one its users reserve.
class CollidedLog {
public:
    CollidedLog();
    CollidedLog(const CollidedLog& other);

    bool isValid() const;
    CollidedInfo info() const;

private:
    u32 _0[2];
    CollidedInfo mInfo;
};

}
}

#endif
