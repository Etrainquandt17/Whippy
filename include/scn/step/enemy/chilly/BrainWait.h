#ifndef SCN_STEP_ENEMY_CHILLY_BRAINWAIT_H
#define SCN_STEP_ENEMY_CHILLY_BRAINWAIT_H

#include "scn/step/enemy/BrainBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace chilly {

class BrainWait : public BrainBase {
public:
    BrainWait(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::chilly

#endif
