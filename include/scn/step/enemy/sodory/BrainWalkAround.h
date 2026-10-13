#ifndef SCN_STEP_ENEMY_SODORY_BRAINWALKAROUND_H
#define SCN_STEP_ENEMY_SODORY_BRAINWALKAROUND_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

class BrainWalkAround : public BrainBase {
public:
    BrainWalkAround(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
    virtual bool onLanding();
};

}}}}  // namespace scn::step::enemy::sodory

#endif
