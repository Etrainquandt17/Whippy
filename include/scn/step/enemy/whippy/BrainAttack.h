#ifndef SCN_STEP_ENEMY_WHIPPY_BRAINATTACK_H
#define SCN_STEP_ENEMY_WHIPPY_BRAINATTACK_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace whippy {

class BrainAttack : public BrainBase {
public:
    BrainAttack(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::whippy

#endif
