#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEGLIDESWORD_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEGLIDESWORD_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateGlideSword : public StateBase {
public:
    StateGlideSword(Boss* boss, const hel::math::Vector3& pos);
    StateGlideSword(Boss* boss, f32, bool);
    virtual ~StateGlideSword();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
