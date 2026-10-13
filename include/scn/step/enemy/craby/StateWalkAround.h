#ifndef SCN_STEP_ENEMY_CRABY_STATEWALKAROUND_H
#define SCN_STEP_ENEMY_CRABY_STATEWALKAROUND_H

#include "gobj/MoveParam.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace craby {

class StateWalkAround : public StateBase {
public:
    StateWalkAround(Enemy* enemy);
    virtual ~StateWalkAround();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    gobj::MoveParamAccel mAccel;
    f32 mBasePosX;
};

}}}}  // namespace scn::step::enemy::craby

#endif
