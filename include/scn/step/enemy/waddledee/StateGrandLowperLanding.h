#ifndef SCN_STEP_ENEMY_WADDLEDEE_STATEGRANDLOWPERLANDING_H
#define SCN_STEP_ENEMY_WADDLEDEE_STATEGRANDLOWPERLANDING_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

class StateGrandLowperLanding : public StateBase {
public:
    StateGrandLowperLanding(Enemy* enemy);
    virtual ~StateGrandLowperLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::waddledee

#endif
