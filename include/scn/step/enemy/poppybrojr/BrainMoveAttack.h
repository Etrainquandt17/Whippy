#ifndef SCN_STEP_ENEMY_POPPYBROJR_BRAINMOVEATTACK_H
#define SCN_STEP_ENEMY_POPPYBROJR_BRAINMOVEATTACK_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojr {

class BrainMoveAttack : public BrainBase {
public:
    BrainMoveAttack(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::poppybrojr

#endif
