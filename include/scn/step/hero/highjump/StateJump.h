#ifndef SCN_STEP_HERO_HIGHJUMP_STATEJUMP_H
#define SCN_STEP_HERO_HIGHJUMP_STATEJUMP_H

#include "hel/math/Vector3.h"
#include "scn/step/hero/StateBase.h"
#include "scn/step/hero/highjump/JumpKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

struct HighjumpParamJump;
namespace highjump {

class StateJump : public StateBase {
public:
    StateJump(Hero* hero, JumpKind kind);
    virtual ~StateJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    const HighjumpParamJump& param() const;

    u32 mFrame;
    f32 mSpeedRate;
    hel::math::Vector3 mStartPos;
    bool _1C;
    JumpKind mKind;
    bool mIsEnd;
};

}}}}  // namespace scn::step::hero::highjump

#endif
