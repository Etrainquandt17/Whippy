#ifndef SCN_STEP_ENEMY_TOGEKUKI_BRAINWAIT_H
#define SCN_STEP_ENEMY_TOGEKUKI_BRAINWAIT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace togekuki {

class BrainWait : public BrainBase {
public:
    BrainWait(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::togekuki

#endif
