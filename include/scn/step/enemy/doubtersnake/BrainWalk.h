#ifndef SCN_STEP_ENEMY_DOUBTERSNAKE_BRAINWALK_H
#define SCN_STEP_ENEMY_DOUBTERSNAKE_BRAINWALK_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace doubtersnake {

class BrainWalk : public BrainBase {
public:
    BrainWalk(Enemy& enemy);
    virtual bool onStart();
    virtual bool onLanding();
    virtual void update();
};

}}}}  // namespace scn::step::enemy::doubtersnake

#endif
