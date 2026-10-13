#ifndef SCN_STEP_ENEMY_COMMON_BRAINWALKTURNCLIFF_H
#define SCN_STEP_ENEMY_COMMON_BRAINWALKTURNCLIFF_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class BrainWalkTurnCliff : public BrainBase {
public:
    BrainWalkTurnCliff(Enemy& enemy);
    virtual bool onLanding();
};

}}}}  // namespace scn::step::enemy::common

#endif
