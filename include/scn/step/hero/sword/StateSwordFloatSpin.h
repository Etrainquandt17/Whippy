#ifndef SCN_STEP_HERO_SWORD_STATESWORDFLOATSPIN_H
#define SCN_STEP_HERO_SWORD_STATESWORDFLOATSPIN_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordFloatSpin : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSwordFloatSpin(Hero* hero);
    virtual ~StateSwordFloatSpin();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqJumpEffect();

    bool mIsBubble;
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::sword

#endif
