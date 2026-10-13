#ifndef SCN_STEP_ENEMY_KABU_BRAINTELEPORTREPEAT_H
#define SCN_STEP_ENEMY_KABU_BRAINTELEPORTREPEAT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

class BrainTeleportRepeat : public BrainBase {
public:
    BrainTeleportRepeat(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::kabu

#endif
