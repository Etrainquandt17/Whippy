#ifndef SCN_STEP_HERO_SWORD_STATESWORDRAISING_H
#define SCN_STEP_HERO_SWORD_STATESWORDRAISING_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordRaising : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSwordRaising(Hero* hero);
    virtual ~StateSwordRaising();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    f32 mRate;
};

}}}}  // namespace scn::step::hero::sword

#endif
