#ifndef SCN_STEP_ENEMY_CRABY_STATEWAIT_H
#define SCN_STEP_ENEMY_CRABY_STATEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace craby {

class StateWait : public StateBase {
public:
    StateWait(Enemy* enemy);
    virtual ~StateWait();
    virtual void procAnim();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::craby

#endif
