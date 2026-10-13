#ifndef SCN_STEP_ENEMY_BLIPPER_STATEFATTYBUFFERESCAPENEAR_H
#define SCN_STEP_ENEMY_BLIPPER_STATEFATTYBUFFERESCAPENEAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace blipper {

class StateFattyBufferEscapeNear : public StateBase {
public:
    StateFattyBufferEscapeNear(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::blipper

#endif
