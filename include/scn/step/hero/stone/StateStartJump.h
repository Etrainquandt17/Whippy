#ifndef SCN_STEP_HERO_STONE_STATESTARTJUMP_H
#define SCN_STEP_HERO_STONE_STATESTARTJUMP_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

class Context;

class StateStartJump : public StateBase {
public:
    static bool ChkChangeState(Hero* hero);

    StateStartJump(Hero* hero, Context& context);
    virtual ~StateStartJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    Context& mContext;
};

}}}}  // namespace scn::step::hero::stone

#endif
