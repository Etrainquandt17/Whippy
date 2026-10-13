#ifndef SCN_STEP_ENEMY_KABU_STATEGRANDLOWPERESCAPESTART_H
#define SCN_STEP_ENEMY_KABU_STATEGRANDLOWPERESCAPESTART_H

#include "scn/step/enemy/StateBase.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace kabu {

class StateGrandLowperEscapeStart : public StateBase {
public:
    StateGrandLowperEscapeStart(Enemy* enemy);
    virtual ~StateGrandLowperEscapeStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::kabu

#endif
