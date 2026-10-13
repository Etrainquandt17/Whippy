#ifndef SCN_STEP_ENEMY_ROLLBALL_MODELDESC_H
#define SCN_STEP_ENEMY_ROLLBALL_MODELDESC_H

#include "scn/step/chara/ModelDesc.h"

namespace scn {
namespace step {
namespace enemy {
namespace rollball {
namespace ModelDesc {

chara::ModelDesc& Create();
chara::ModelDesc& CreateIron();
chara::ModelDesc& CreateIce();
chara::ModelDesc& CreateLava();

}}}}}  // namespace scn::step::enemy::rollball::ModelDesc

#endif
