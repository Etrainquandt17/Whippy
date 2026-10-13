#ifndef SCN_STEP_ENEMY_COMMON_BRAINFLY_H
#define SCN_STEP_ENEMY_COMMON_BRAINFLY_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class BrainFly : public BrainBase {
public:
    BrainFly(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
    virtual bool onLanding();
};

}}}}  // namespace scn::step::enemy::common

#endif
