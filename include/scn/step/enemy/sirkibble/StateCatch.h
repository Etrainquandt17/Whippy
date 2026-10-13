#ifndef SCN_STEP_ENEMY_SIRKIBBLE_STATECATCH_H
#define SCN_STEP_ENEMY_SIRKIBBLE_STATECATCH_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sirkibble {

class StateCatch : public StateBase {
public:
    StateCatch(Enemy* enemy);
    virtual ~StateCatch();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::sirkibble

#endif
