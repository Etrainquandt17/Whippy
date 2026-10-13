#ifndef SCN_STEP_WEAPON_GALACTAREVOLUTIONSWORD_STATEEND_H
#define SCN_STEP_WEAPON_GALACTAREVOLUTIONSWORD_STATEEND_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactarevolutionsword {

class StateEnd : public StateBase {
public:
    StateEnd(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mFrame;
};

}}}}  // namespace scn::step::weapon::galactarevolutionsword

#endif
