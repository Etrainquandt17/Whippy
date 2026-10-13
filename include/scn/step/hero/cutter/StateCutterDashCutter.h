#ifndef SCN_STEP_HERO_CUTTER_STATECUTTERDASHCUTTER_H
#define SCN_STEP_HERO_CUTTER_STATECUTTERDASHCUTTER_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

class StateCutterDashCutter : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateCutterDashCutter(Hero* hero);
    virtual ~StateCutterDashCutter();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::cutter

#endif
