#ifndef SCN_STEP_ENEMY_GLUNK_BRAINWAIT_H
#define SCN_STEP_ENEMY_GLUNK_BRAINWAIT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace glunk {

class BrainWait : public BrainBase {
public:
    BrainWait(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::glunk

#endif
