#ifndef SCN_STEP_HERO_WING_STATESHUTTLELOOP_H
#define SCN_STEP_HERO_WING_STATESHUTTLELOOP_H

#include "hel/math/Vector2.h"
#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace wing {

class StateShuttleLoop : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateShuttleLoop(Hero* hero);
    virtual ~StateShuttleLoop();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector2 mPrevPos;
};

}}}}  // namespace scn::step::hero::wing

#endif
