#ifndef SCN_STEP_CARRYITEM_BALLOONBOMB_STATEEXPLOSION_H
#define SCN_STEP_CARRYITEM_BALLOONBOMB_STATEEXPLOSION_H

#include "scn/step/carryitem/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {
namespace balloonbomb {

// TODO: the source of this state is not written. A balloonbomb::BombSize follows mFrame at 0xC; it has no
// header yet, so the class is too small.
class StateExplosion : public StateBase {
public:
    StateExplosion(CarryItem* carryItem);
    virtual ~StateExplosion();

    virtual void procAnim();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::carryitem::balloonbomb

#endif
