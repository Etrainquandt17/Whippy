#ifndef SCN_STEP_ENEMY_ROCKY_STATEWALKSTART_H
#define SCN_STEP_ENEMY_ROCKY_STATEWALKSTART_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace rocky {

class StateWalkStart : public StateBase {
public:
    StateWalkStart(Enemy* enemy);
    virtual ~StateWalkStart();
    virtual void procAnim();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::rocky

#endif
