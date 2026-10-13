#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATESATELLITE_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATESATELLITE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroamagicball {

class StateSatellite : public StateBase {
public:
    StateSatellite(Enemy* enemy);
    virtual ~StateSatellite();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();

private:
    f32 mAngle;
    f32 mRadius;
};

}}}}  // namespace scn::step::enemy::mahoroamagicball

#endif
