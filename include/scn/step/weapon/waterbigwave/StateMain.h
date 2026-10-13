#ifndef SCN_STEP_WEAPON_WATERBIGWAVE_STATEMAIN_H
#define SCN_STEP_WEAPON_WATERBIGWAVE_STATEMAIN_H

#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "hel/common/MutableArray.h"
#include "hel/math/Vector2.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace waterbigwave {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    void calcJoint();

    hel::common::MutableArray<hel::math::Vector2, 13> mPositions;
    bool _74;
    bool _75;
    u32 mFrame;
    u32 _7C;
    bool _80;
};

}}}}  // namespace scn::step::weapon::waterbigwave

#endif
