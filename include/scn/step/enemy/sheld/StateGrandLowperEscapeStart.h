#ifndef SCN_STEP_ENEMY_SHELD_STATEGRANDLOWPERESCAPESTART_H
#define SCN_STEP_ENEMY_SHELD_STATEGRANDLOWPERESCAPESTART_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sheld {

class StateGrandLowperEscapeStart : public StateBase {
public:
    StateGrandLowperEscapeStart(Enemy* enemy);
    virtual ~StateGrandLowperEscapeStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::sheld

#endif
