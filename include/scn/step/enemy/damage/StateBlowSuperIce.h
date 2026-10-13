#ifndef SCN_STEP_ENEMY_DAMAGE_STATEBLOWSUPERICE_H
#define SCN_STEP_ENEMY_DAMAGE_STATEBLOWSUPERICE_H

#include "scn/step/enemy/StateBase.h"
#include "scn/step/ocoll/Element.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace damage {

class StateBlowSuperIce : public StateBase {
public:
    StateBlowSuperIce(Enemy* enemy);
    virtual ~StateBlowSuperIce();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
    u32 mReflectCount;
    u32 _10;
    u32 mReflectMax;
    ocoll::Element mElement;
};

}}}}  // namespace scn::step::enemy::damage

#endif
