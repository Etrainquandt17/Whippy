#ifndef SCN_STEP_ENEMY_STAREFFECT_BRAINPUFF_H
#define SCN_STEP_ENEMY_STAREFFECT_BRAINPUFF_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace stareffect {

class BrainPuff : public BrainBase {
public:
    BrainPuff(Enemy& enemy);
    virtual bool onStart();
};

}}}}  // namespace scn::step::enemy::stareffect

#endif
