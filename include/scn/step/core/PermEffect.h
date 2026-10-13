#ifndef SCN_STEP_CORE_PERMEFFECT_H
#define SCN_STEP_CORE_PERMEFFECT_H

#include "scn/step/effect/Kind.h"
#include "types.h"

namespace hel {
namespace math {

class Direction3;
class Vector3;

}
}

namespace scn {
namespace step {

class Component;

namespace core {

// TODO: members.
class PermEffectDetail {
public:
    PermEffectDetail(Component& component);
    ~PermEffectDetail();

    void requestP(effect::Kind kind, const hel::math::Vector3& pos);
    void requestP(effect::Kind kind, const hel::math::Vector3& pos, f32 scale);
    void requestPD(effect::Kind kind, const hel::math::Vector3& pos, const hel::math::Direction3& dir);
    void requestPD(effect::Kind kind, const hel::math::Vector3& pos, const hel::math::Direction3& dir, f32 scale);
    void requestForeP(effect::Kind kind, const hel::math::Vector3& pos);
    void requestForeP(effect::Kind kind, const hel::math::Vector3& pos, f32 scale);
    void requestCharaFrontP(effect::Kind kind, const hel::math::Vector3& pos);
    void requestInfoP(effect::Kind kind, const hel::math::Vector3& pos);

private:
    u32 _0[0x32];
};

// TODO: the other members and the base class; the names of the two accessors are guesses (they are inline).
class PermEffect {
public:
    PermEffect(Component& component);
    virtual ~PermEffect();

    PermEffectDetail& normal() { return mNormal; }
    PermEffectDetail& powerful() { return mPowerful; }

private:
    Component& mComponent;
    PermEffectDetail mNormal;
    PermEffectDetail mPowerful;
};

}
}
}

#endif
