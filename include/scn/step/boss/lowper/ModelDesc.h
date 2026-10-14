#ifndef SCN_STEP_BOSS_LOWPER_MODELDESC_H
#define SCN_STEP_BOSS_LOWPER_MODELDESC_H

#include "scn/step/chara/ModelDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra);

}

}}}}  // namespace scn::step::boss::lowper

#endif
