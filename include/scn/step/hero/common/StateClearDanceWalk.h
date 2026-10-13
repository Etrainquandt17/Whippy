#ifndef SCN_STEP_HERO_COMMON_STATECLEARDANCEWALK_H
#define SCN_STEP_HERO_COMMON_STATECLEARDANCEWALK_H

#include "hel/math/Vector3.h"
#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateClearDanceWalk : public StateBase {
public:
    StateClearDanceWalk(Hero* hero, u32 zoom);
    virtual ~StateClearDanceWalk();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 mTargetPos;
    u32 mZoom;
};

}}}}  // namespace scn::step::hero::common

#endif
