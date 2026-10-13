#ifndef EFFECT_DETAIL_REQUESTARG_H
#define EFFECT_DETAIL_REQUESTARG_H

#include "effect/detail/RequestArgOption.h"
#include "types.h"

namespace effect {
namespace detail {

class RequestArg {
public:
    RequestArg(u32 id, const RequestArgOption& option);
    ~RequestArg();

private:
    u32 _0[0x84 / 4];
};

}
}

#endif
