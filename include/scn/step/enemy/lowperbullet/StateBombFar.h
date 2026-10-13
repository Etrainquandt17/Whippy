#ifndef SCN_STEP_ENEMY_LOWPERBULLET_STATEBOMBFAR_H
#define SCN_STEP_ENEMY_LOWPERBULLET_STATEBOMBFAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lowperbullet {

class StateBombFar : public StateBase {
public:
    StateBombFar(Enemy* enemy);
    virtual ~StateBombFar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mFallAccel;
};

}}}}  // namespace scn::step::enemy::lowperbullet

#endif
