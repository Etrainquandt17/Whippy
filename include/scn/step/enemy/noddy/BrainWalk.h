#ifndef SCN_STEP_ENEMY_NODDY_BRAINWALK_H
#define SCN_STEP_ENEMY_NODDY_BRAINWALK_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace noddy {

class BrainWalk : public BrainBase {
public:
    BrainWalk(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::noddy

#endif
