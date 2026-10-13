#ifndef SCN_STEP_HERO_CUTTER_STATECUTTERSWEEPCUTTER_H
#define SCN_STEP_HERO_CUTTER_STATECUTTERSWEEPCUTTER_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

class StateCutterSweepCutter : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateCutterSweepCutter(Hero* hero);
    virtual ~StateCutterSweepCutter();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::cutter

#endif
