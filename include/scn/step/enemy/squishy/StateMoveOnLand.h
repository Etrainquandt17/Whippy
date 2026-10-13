#ifndef SCN_STEP_ENEMY_SQUISHY_STATEMOVEONLAND_H
#define SCN_STEP_ENEMY_SQUISHY_STATEMOVEONLAND_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace squishy {

class StateMoveOnLand : public StateBase {
public:
    StateMoveOnLand(Enemy* enemy);
    virtual ~StateMoveOnLand();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsInWater;
};

}}}}  // namespace scn::step::enemy::squishy

#endif
