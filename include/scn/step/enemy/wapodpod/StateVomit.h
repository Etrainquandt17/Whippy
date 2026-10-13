#ifndef SCN_STEP_ENEMY_WAPODPOD_STATEVOMIT_H
#define SCN_STEP_ENEMY_WAPODPOD_STATEVOMIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace wapodpod {

class StateVomit : public StateBase {
public:
    StateVomit(Enemy* enemy);
    virtual void procAnim();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::wapodpod

#endif
