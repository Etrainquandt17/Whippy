#ifndef SCN_STEP_HERO_SWORD_STATESWORDMINCE_H
#define SCN_STEP_HERO_SWORD_STATESWORDMINCE_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordMince : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSwordMince(Hero* hero);
    virtual ~StateSwordMince();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsNext;
};

}}}}  // namespace scn::step::hero::sword

#endif
