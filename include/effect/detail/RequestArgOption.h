#ifndef EFFECT_DETAIL_REQUESTARGOPTION_H
#define EFFECT_DETAIL_REQUESTARGOPTION_H

#include "g3d/NodeAccessor.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace effect {
namespace detail {

class RequestArgOption {
public:
    static RequestArgOption CreateP(const hel::math::Vector3& pos);
    static RequestArgOption CreatePD(const hel::math::Vector3& pos, const hel::math::Direction3& dir);
    static RequestArgOption CreateN(const g3d::NodeAccessor& node);
    static RequestArgOption CreateND(const g3d::NodeAccessor& node, const hel::math::Direction3& dir);

    RequestArgOption();
    ~RequestArgOption();

    void setScale(f32 scale);
    void setOffset(const hel::math::Vector3& offset);

private:
    u32 mType;
    f32 mScale;
    hel::math::Vector3 mOffset;
    hel::math::Vector3 mPos;
    hel::math::Direction3 mDir;
    g3d::NodeAccessor mNode;
};

}
}

#endif
