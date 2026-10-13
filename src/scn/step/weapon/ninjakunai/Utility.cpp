#include "scn/step/weapon/ninjakunai/Utility.h"

#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/ninjakunai/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjakunai {

void Utility::Rotate(Weapon& weapon) {
    const Param& param = weapon.param().ninjaKunai();
    f32 sign = weapon.target().getSign();
    weapon.model().rotCtrl().setRotH(param._7C);
    weapon.model().rotCtrl().setRotD(param._80);
    weapon.model().rotCtrl().setRotV(sign * param._84);
}

}}}}  // namespace scn::step::weapon::ninjakunai
