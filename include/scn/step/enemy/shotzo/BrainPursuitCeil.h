#ifndef SCN_STEP_ENEMY_SHOTZO_BRAINPURSUITCEIL_H
#define SCN_STEP_ENEMY_SHOTZO_BRAINPURSUITCEIL_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

class BrainPursuitCeil : public BrainBase {
public:
    BrainPursuitCeil(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::shotzo

#endif
