#ifndef SCN_STEP_ENEMY_STAREFFECT_BRAINBOUND_H
#define SCN_STEP_ENEMY_STAREFFECT_BRAINBOUND_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace stareffect {

class BrainBound : public BrainBase {
public:
    BrainBound(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::stareffect

#endif
