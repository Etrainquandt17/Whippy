#ifndef SCN_STEP_ENEMY_BARRACU_STATEBOUND_H
#define SCN_STEP_ENEMY_BARRACU_STATEBOUND_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace barracu {

class StateBound : public StateBase {
public:
    StateBound(Enemy* enemy);
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::barracu

#endif
