#ifndef SCN_STEP_ENEMY_LANZER_BRAINWALK_H
#define SCN_STEP_ENEMY_LANZER_BRAINWALK_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

class BrainWalk : public BrainBase {
public:
    BrainWalk(Enemy& enemy);
    virtual bool onStart();
    virtual bool onLanding();
};

}}}}  // namespace scn::step::enemy::lanzer

#endif
