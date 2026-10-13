#ifndef SCN_STEP_ENEMY_BLIPPER_STATEFATTYBUFFERAPPEARFALL_H
#define SCN_STEP_ENEMY_BLIPPER_STATEFATTYBUFFERAPPEARFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace blipper {

class StateFattyBufferAppearFall : public StateBase {
public:
    StateFattyBufferAppearFall(Enemy* enemy);
    virtual ~StateFattyBufferAppearFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
};

}}}}  // namespace scn::step::enemy::blipper

#endif
