#ifndef EFFECT_DETAIL_REQUESTARGOPTION_H
#define EFFECT_DETAIL_REQUESTARGOPTION_H

#include "types.h"

namespace hel {
namespace math {
class Vector3;
}
}

namespace effect {
namespace detail {

class RequestArgOption {
public:
    static RequestArgOption CreateP(const hel::math::Vector3& pos);
    ~RequestArgOption();

    void setScale(f32 scale);
    void setOffset(const hel::math::Vector3& offset);

private:
    u32 _0[0x58 / 4];
};

}
}

#endif
