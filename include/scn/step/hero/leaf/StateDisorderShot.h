#ifndef SCN_STEP_HERO_LEAF_STATEDISORDERSHOT_H
#define SCN_STEP_HERO_LEAF_STATEDISORDERSHOT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

class StateDisorderShot : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateDisorderShot(Hero* hero);
    virtual ~StateDisorderShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    bool mIsRightDir;
};

}}}}  // namespace scn::step::hero::leaf

#endif
