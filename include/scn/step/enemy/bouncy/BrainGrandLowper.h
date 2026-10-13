#ifndef SCN_STEP_ENEMY_BOUNCY_BRAINGRANDLOWPER_H
#define SCN_STEP_ENEMY_BOUNCY_BRAINGRANDLOWPER_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {

class BrainGrandLowper : public BrainBase {
public:
    BrainGrandLowper(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::bouncy

#endif
