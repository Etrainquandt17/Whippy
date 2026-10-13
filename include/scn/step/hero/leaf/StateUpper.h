#ifndef SCN_STEP_HERO_LEAF_STATEUPPER_H
#define SCN_STEP_HERO_LEAF_STATEUPPER_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

class StateUpper : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateUpper(Hero* hero);
    virtual ~StateUpper();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsTriggered;
};

}}}}  // namespace scn::step::hero::leaf

#endif
