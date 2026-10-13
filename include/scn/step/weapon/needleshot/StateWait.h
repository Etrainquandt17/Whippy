#ifndef SCN_STEP_WEAPON_NEEDLESHOT_STATEWAIT_H
#define SCN_STEP_WEAPON_NEEDLESHOT_STATEWAIT_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {

namespace hero {
class Hero;
}

namespace weapon {
namespace needleshot {

class StateWait : public StateBase {
public:
    StateWait(Weapon* weapon);
    virtual ~StateWait();
    virtual void procConstraint();

private:
    util::ObjRefHandle<hero::Hero> mHero;
    f32 mOffsetY;
};

}}}}  // namespace scn::step::weapon::needleshot

#endif
