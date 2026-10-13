#ifndef SCN_STEP_HERO_CUTTER_STATECUTTERTHROWLONG_H
#define SCN_STEP_HERO_CUTTER_STATECUTTERTHROWLONG_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

class StateCutterThrowLong : public StateBase {
public:
    StateCutterThrowLong(Hero* hero);
    virtual ~StateCutterThrowLong();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::cutter

#endif
