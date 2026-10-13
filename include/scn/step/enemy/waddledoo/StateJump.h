#ifndef SCN_STEP_ENEMY_WADDLEDOO_STATEJUMP_H
#define SCN_STEP_ENEMY_WADDLEDOO_STATEJUMP_H

#include "scn/step/enemy/StateBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

class StateJump : public StateBase {
public:
    StateJump(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::waddledoo

#endif
