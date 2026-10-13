#ifndef SCN_STEP_HERO_SPARK_STATEATTACK_H
#define SCN_STEP_HERO_SPARK_STATEATTACK_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace spark {

class StateAttack : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateAttack(Hero* hero);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsEnd;
};

}}}}  // namespace scn::step::hero::spark

#endif
