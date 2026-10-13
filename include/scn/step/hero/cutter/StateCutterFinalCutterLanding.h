#ifndef SCN_STEP_HERO_CUTTER_STATECUTTERFINALCUTTERLANDING_H
#define SCN_STEP_HERO_CUTTER_STATECUTTERFINALCUTTERLANDING_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

class StateCutterFinalCutterLanding : public StateBase {
public:
    StateCutterFinalCutterLanding(Hero* hero);
    virtual ~StateCutterFinalCutterLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::cutter

#endif
