#ifndef SCN_STEP_ENEMY_SODORY_BRAINFLY_H
#define SCN_STEP_ENEMY_SODORY_BRAINFLY_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

class BrainFly : public BrainBase {
public:
    BrainFly(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::sodory

#endif
