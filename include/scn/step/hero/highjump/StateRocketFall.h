#ifndef SCN_STEP_HERO_HIGHJUMP_STATEROCKETFALL_H
#define SCN_STEP_HERO_HIGHJUMP_STATEROCKETFALL_H

#include "hel/math/Vector3.h"
#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

class StateRocketFall : public StateBase {
public:
    StateRocketFall(Hero* hero);
    virtual ~StateRocketFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    f32 mSpeedRate;
    hel::math::Vector3 mStartPos;
    bool _1C;
};

}}}}  // namespace scn::step::hero::highjump

#endif
