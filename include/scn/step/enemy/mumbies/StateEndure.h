#ifndef SCN_STEP_ENEMY_MUMBIES_STATEENDURE_H
#define SCN_STEP_ENEMY_MUMBIES_STATEENDURE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mumbies {

class StateEndure : public StateBase {
public:
    StateEndure(Enemy* enemy);
    virtual ~StateEndure();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::mumbies

#endif
