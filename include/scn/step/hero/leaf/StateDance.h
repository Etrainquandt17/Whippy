#ifndef SCN_STEP_HERO_LEAF_STATEDANCE_H
#define SCN_STEP_HERO_LEAF_STATEDANCE_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

class StateDance : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateDance(Hero* hero);
    virtual ~StateDance();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsEnd;
};

}}}}  // namespace scn::step::hero::leaf

#endif
