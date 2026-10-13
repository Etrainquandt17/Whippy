#ifndef SCN_STEP_ENEMY_CLAYN_BRAINWAIT_H
#define SCN_STEP_ENEMY_CLAYN_BRAINWAIT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

class BrainWait : public BrainBase {
public:
    BrainWait(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
    virtual bool onLanding();
};

}}}}  // namespace scn::step::enemy::clayn

#endif
