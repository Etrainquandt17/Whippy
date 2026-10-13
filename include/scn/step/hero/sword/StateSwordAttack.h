#ifndef SCN_STEP_HERO_SWORD_STATESWORDATTACK_H
#define SCN_STEP_HERO_SWORD_STATESWORDATTACK_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordAttack : public StateBase {
public:
    static bool tryToChangeState(Hero* hero);

    StateSwordAttack(Hero* hero);
    virtual ~StateSwordAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    u32 mFrame;
    bool mIsHold;
    bool mIsHit;
    bool mIsEnd;
};

}}}}  // namespace scn::step::hero::sword

#endif
