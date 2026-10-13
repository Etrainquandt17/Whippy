#ifndef SCN_STEP_ENEMY_WAPOD_STATESTAY_H
#define SCN_STEP_ENEMY_WAPOD_STATESTAY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace wapod {

class StateStay : public StateBase {
public:
    StateStay(Enemy* enemy);
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::wapod

#endif
