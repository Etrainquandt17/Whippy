#ifndef SCN_STEP_BOSS_BONKERS_MODELDESC_H
#define SCN_STEP_BOSS_BONKERS_MODELDESC_H

#include "scn/step/chara/ModelDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {
namespace ModelDesc {

chara::ModelDesc& CreateNormal(u32 level, bool isExtra);
chara::ModelDesc& CreateSuper(u32 level, bool isExtra);

}}}}}  // namespace scn::step::boss::bonkers::ModelDesc

#endif
