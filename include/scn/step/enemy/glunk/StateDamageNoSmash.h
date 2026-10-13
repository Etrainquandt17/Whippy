#ifndef SCN_STEP_ENEMY_GLUNK_STATEDAMAGENOSMASH_H
#define SCN_STEP_ENEMY_GLUNK_STATEDAMAGENOSMASH_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace glunk {

class StateDamageNoSmash : public StateBase {
public:
    StateDamageNoSmash(Enemy* enemy);
    virtual ~StateDamageNoSmash();
    virtual void procAnim();

private:
    u32 mFrame;
    u32 mEndFrame;
};

}}}}  // namespace scn::step::enemy::glunk

#endif
