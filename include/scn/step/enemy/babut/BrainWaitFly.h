#ifndef SCN_STEP_ENEMY_BABUT_BRAINWAITFLY_H
#define SCN_STEP_ENEMY_BABUT_BRAINWAITFLY_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

class BrainWaitFly : public BrainBase {
public:
    BrainWaitFly(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::babut

#endif
