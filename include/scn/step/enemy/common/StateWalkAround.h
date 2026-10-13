#ifndef SCN_STEP_ENEMY_COMMON_STATEWALKAROUND_H
#define SCN_STEP_ENEMY_COMMON_STATEWALKAROUND_H

#include "gobj/MoveParam.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateWalkAround : public StateBase {
public:
    StateWalkAround(Enemy* enemy);
    virtual ~StateWalkAround();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mBaseX;
    gobj::MoveParamAccel mAccel;
};

}}}}  // namespace scn::step::enemy::common

#endif
