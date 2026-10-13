#ifndef SCN_STEP_ENEMY_WALKY_BRAINWALKJUMP_H
#define SCN_STEP_ENEMY_WALKY_BRAINWALKJUMP_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace walky {

class BrainWalkJump : public BrainBase {
public:
    BrainWalkJump(Enemy& enemy);
    virtual bool onStart();
    virtual bool onLanding();
    virtual void update();
};

}}}}  // namespace scn::step::enemy::walky

#endif
