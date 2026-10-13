#ifndef SCN_STEP_HERO_BEAM_STATEBEAMBLAST_H
#define SCN_STEP_HERO_BEAM_STATEBEAMBLAST_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace beam {

class StateBeamBlast : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateBeamBlast(Hero* hero);
    virtual ~StateBeamBlast();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mWait;
    u32 mShotCount;
    bool mIsRight;
};

}}}}  // namespace scn::step::hero::beam

#endif
