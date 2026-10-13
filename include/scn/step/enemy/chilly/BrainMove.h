#ifndef SCN_STEP_ENEMY_CHILLY_BRAINMOVE_H
#define SCN_STEP_ENEMY_CHILLY_BRAINMOVE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace chilly {

class BrainMove : public BrainBase {
public:
    BrainMove(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::chilly

#endif
