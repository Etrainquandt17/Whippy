#ifndef SCN_STEP_BOSS_GOLIATH_DYNAMICSDESC_H
#define SCN_STEP_BOSS_GOLIATH_DYNAMICSDESC_H

#include "scn/step/chara/ModelDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

namespace DynamicsDesc {

const chara::ModelDesc::DynamicsDesc& Create(bool isAngry);

}

}}}}  // namespace scn::step::boss::goliath

#endif
