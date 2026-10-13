#ifndef SCN_STEP_ENEMY_BRONTOBURT_STATEWAIT_H
#define SCN_STEP_ENEMY_BRONTOBURT_STATEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace brontoburt {

class StateWait : public StateBase {
public:
    StateWait(Enemy* enemy);
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::brontoburt

#endif
