#ifndef SCN_STEP_ENEMY_GLUNK_BRAINATTACK_H
#define SCN_STEP_ENEMY_GLUNK_BRAINATTACK_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace glunk {

class BrainAttack : public BrainBase {
public:
    BrainAttack(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::glunk

#endif
