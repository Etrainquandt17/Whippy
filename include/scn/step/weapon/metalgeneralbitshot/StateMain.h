#ifndef SCN_STEP_WEAPON_METALGENERALBITSHOT_STATEMAIN_H
#define SCN_STEP_WEAPON_METALGENERALBITSHOT_STATEMAIN_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/StateBase.h"
#include "scn/step/weapon/metalgeneralbitshot/Param.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace metalgeneralbitshot {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    const VariationParam& param();

private:
    u32 mFrame;
    hel::math::Vector3 mDir;
};

}}}}  // namespace scn::step::weapon::metalgeneralbitshot

#endif
