#ifndef SCN_STEP_ENEMY_OWGULF_STATEFLYSTRAIGHT_H
#define SCN_STEP_ENEMY_OWGULF_STATEFLYSTRAIGHT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace owgulf {

class StateFlyStraight : public StateBase {
public:
    StateFlyStraight(Enemy* enemy);
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::owgulf

#endif
