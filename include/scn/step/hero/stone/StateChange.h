#ifndef SCN_STEP_HERO_STONE_STATECHANGE_H
#define SCN_STEP_HERO_STONE_STATECHANGE_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

class Context;

class StateChange : public StateBase {
public:
    static bool ChkChangeStateScrew(Hero* hero);
    static void ChangeStateNoScrew(Hero* hero, Context& context);

    StateChange(Hero* hero, Context& context);
    virtual ~StateChange();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    Context& mContext;
    bool _C;
};

}}}}  // namespace scn::step::hero::stone

#endif
