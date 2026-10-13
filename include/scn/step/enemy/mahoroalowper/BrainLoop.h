#ifndef SCN_STEP_ENEMY_MAHOROALOWPER_BRAINLOOP_H
#define SCN_STEP_ENEMY_MAHOROALOWPER_BRAINLOOP_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroalowper {

class BrainLoop : public BrainBase {
public:
    BrainLoop(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::mahoroalowper

#endif
