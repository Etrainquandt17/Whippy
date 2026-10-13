#ifndef SCN_STEP_ENEMY_COMMON_BRAINWALKSTRAIGHT_H
#define SCN_STEP_ENEMY_COMMON_BRAINWALKSTRAIGHT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class BrainWalkStraight : public BrainBase {
public:
    BrainWalkStraight(Enemy& enemy);
    virtual bool onLanding();
};

}}}}  // namespace scn::step::enemy::common

#endif
