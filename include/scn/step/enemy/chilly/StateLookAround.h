#ifndef SCN_STEP_ENEMY_CHILLY_STATELOOKAROUND_H
#define SCN_STEP_ENEMY_CHILLY_STATELOOKAROUND_H

#include "scn/step/enemy/StateBase.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace chilly {

class StateLookAround : public StateBase {
public:
    StateLookAround(Enemy* enemy);
    virtual void procAnim();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::chilly

#endif
