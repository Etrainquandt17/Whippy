#ifndef SCN_STEP_ENEMY_BLADEKNIGHT_BRAINGRANDLOWPER_H
#define SCN_STEP_ENEMY_BLADEKNIGHT_BRAINGRANDLOWPER_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

class BrainGrandLowper : public BrainBase {
public:
    BrainGrandLowper(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::bladeknight

#endif
