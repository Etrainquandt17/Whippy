#ifndef SCN_STEP_ENEMY_LOWPERBULLET_STATESHOTBULLET_H
#define SCN_STEP_ENEMY_LOWPERBULLET_STATESHOTBULLET_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lowperbullet {

class StateShotBullet : public StateBase {
public:
    StateShotBullet(Enemy* enemy);
    virtual ~StateShotBullet();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::lowperbullet

#endif
