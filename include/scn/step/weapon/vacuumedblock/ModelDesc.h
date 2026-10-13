#ifndef SCN_STEP_WEAPON_VACUUMEDBLOCK_MODELDESC_H
#define SCN_STEP_WEAPON_VACUUMEDBLOCK_MODELDESC_H

#include "scn/step/chara/ModelDesc.h"

namespace scn {
namespace step {
namespace weapon {
namespace vacuumedblock {

namespace ModelDesc {

chara::ModelDesc& CreateStar();
chara::ModelDesc& CreateHeavy1x1();
chara::ModelDesc& CreateHeavy2x2();
chara::ModelDesc& CreateHeavy3x3();
chara::ModelDesc& CreateHeavy4x4();
chara::ModelDesc& CreateHeavyA1x2x1();
chara::ModelDesc& CreateHeavyB1x2x1();
chara::ModelDesc& CreateHeavy1x2x3();
chara::ModelDesc& CreateHeavy1x3();
chara::ModelDesc& CreateHeavy3x1();
chara::ModelDesc& CreateHeavy2x4x4x2();
chara::ModelDesc& CreateHeavy3x2x1();

}

}}}}  // namespace scn::step::weapon::vacuumedblock

#endif
