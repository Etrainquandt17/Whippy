#ifndef SCN_STEP_HERO_STONE_STATESLIP_H
#define SCN_STEP_HERO_STONE_STATESLIP_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

class Context;

class StateSlip : public StateBase {
public:
    StateSlip(Hero* hero, Context& context);
    virtual ~StateSlip();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool isSpeedZero() const;

    Context& mContext;
    bool mIsRolling;
};

}}}}  // namespace scn::step::hero::stone

#endif
