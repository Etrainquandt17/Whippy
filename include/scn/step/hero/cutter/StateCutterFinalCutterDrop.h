#ifndef SCN_STEP_HERO_CUTTER_STATECUTTERFINALCUTTERDROP_H
#define SCN_STEP_HERO_CUTTER_STATECUTTERFINALCUTTERDROP_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

class StateCutterFinalCutterDrop : public StateBase {
public:
    StateCutterFinalCutterDrop(Hero* hero);
    virtual ~StateCutterFinalCutterDrop();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::cutter

#endif
