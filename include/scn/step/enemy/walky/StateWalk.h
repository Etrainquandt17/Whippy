#ifndef SCN_STEP_ENEMY_WALKY_STATEWALK_H
#define SCN_STEP_ENEMY_WALKY_STATEWALK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace walky {

class StateWalk : public StateBase {
public:
    StateWalk(Enemy* enemy);
    virtual ~StateWalk();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::walky

#endif
