#ifndef SCN_STEP_ENEMY_GOLIATHSNOWBALL_BRAINFALL_H
#define SCN_STEP_ENEMY_GOLIATHSNOWBALL_BRAINFALL_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathsnowball {

class BrainFall : public BrainBase {
public:
    BrainFall(Enemy& enemy);
    virtual bool onStart();
    virtual bool onLanding();
};

}}}}  // namespace scn::step::enemy::goliathsnowball

#endif
