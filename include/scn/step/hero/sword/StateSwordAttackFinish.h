#ifndef SCN_STEP_HERO_SWORD_STATESWORDATTACKFINISH_H
#define SCN_STEP_HERO_SWORD_STATESWORDATTACKFINISH_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordAttackFinish : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSwordAttackFinish(Hero* hero);
    virtual ~StateSwordAttackFinish();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::sword

#endif
