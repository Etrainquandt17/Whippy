#ifndef SCN_STEP_ENEMY_GRANDLOWPERBULLET_STATEPREPARE_H
#define SCN_STEP_ENEMY_GRANDLOWPERBULLET_STATEPREPARE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace grandlowperbullet {

class StatePrepare : public StateBase {
public:
    StatePrepare(Enemy* enemy);
    virtual ~StatePrepare();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::grandlowperbullet

#endif
