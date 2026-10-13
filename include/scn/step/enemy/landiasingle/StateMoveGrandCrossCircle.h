#ifndef SCN_STEP_ENEMY_LANDIASINGLE_STATEMOVEGRANDCROSSCIRCLE_H
#define SCN_STEP_ENEMY_LANDIASINGLE_STATEMOVEGRANDCROSSCIRCLE_H

#include "hel/math/Vector2.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

class StateMoveGrandCrossCircle : public StateBase {
public:
    StateMoveGrandCrossCircle(Enemy* enemy);
    virtual ~StateMoveGrandCrossCircle();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    hel::math::Vector2 mStart;
    hel::math::Vector2 mEnd;
};

}}}}  // namespace scn::step::enemy::landiasingle

#endif
