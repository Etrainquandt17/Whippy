#ifndef SCN_STEP_ENEMY_FATTYBUFFERJR_STATEAPPEARFALL_H
#define SCN_STEP_ENEMY_FATTYBUFFERJR_STATEAPPEARFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace fattybufferjr {

class StateAppearFall : public StateBase {
public:
    StateAppearFall(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::fattybufferjr

#endif
