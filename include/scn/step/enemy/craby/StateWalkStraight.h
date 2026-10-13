#ifndef SCN_STEP_ENEMY_CRABY_STATEWALKSTRAIGHT_H
#define SCN_STEP_ENEMY_CRABY_STATEWALKSTRAIGHT_H

#include "gobj/MoveParam.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace craby {

class StateWalkStraight : public StateBase {
public:
    StateWalkStraight(Enemy* enemy);
    virtual ~StateWalkStraight();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    gobj::MoveParamAccel mAccel;
};

}}}}  // namespace scn::step::enemy::craby

#endif
