#ifndef SCN_STEP_HERO_NEEDLE_STATEATTACKUP_H
#define SCN_STEP_HERO_NEEDLE_STATEATTACKUP_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace needle {

class StateAttackUp : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateAttackUp(Hero* hero);
    virtual ~StateAttackUp();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    u32 mFrame;
    bool mIsAir;
};

}}}}  // namespace scn::step::hero::needle

#endif
