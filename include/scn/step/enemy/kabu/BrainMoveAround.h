#ifndef SCN_STEP_ENEMY_KABU_BRAINMOVEAROUND_H
#define SCN_STEP_ENEMY_KABU_BRAINMOVEAROUND_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

class BrainMoveAround : public BrainBase {
public:
    BrainMoveAround(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::kabu

#endif
