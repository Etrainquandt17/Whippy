#ifndef SCN_STEP_HERO_HAMMER_STATEUNDERATTACK_H
#define SCN_STEP_HERO_HAMMER_STATEUNDERATTACK_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

class StateUnderAttack : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateUnderAttack(Hero* hero);
    virtual ~StateUnderAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    int mEffectInterval;
    bool mCanCancel;
};

}}}}  // namespace scn::step::hero::hammer

#endif
