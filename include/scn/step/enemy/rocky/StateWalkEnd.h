#ifndef SCN_STEP_ENEMY_ROCKY_STATEWALKEND_H
#define SCN_STEP_ENEMY_ROCKY_STATEWALKEND_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace rocky {

class StateWalkEnd : public StateBase {
public:
    StateWalkEnd(Enemy* enemy);
    virtual ~StateWalkEnd();
    virtual void procAnim();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::rocky

#endif
