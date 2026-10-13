#ifndef SCN_STEP_ENEMY_MOPOO_BRAINMOVESTRAIGHT_H
#define SCN_STEP_ENEMY_MOPOO_BRAINMOVESTRAIGHT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mopoo {

class BrainMoveStraight : public BrainBase {
public:
    BrainMoveStraight(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}}}}  // namespace scn::step::enemy::mopoo

#endif
