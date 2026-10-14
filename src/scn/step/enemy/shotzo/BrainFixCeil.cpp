#include "scn/step/enemy/shotzo/BrainFixCeil.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/shotzo/Custom.h"
#include "scn/step/enemy/shotzo/StateWait.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

BrainFixCeil::BrainFixCeil(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFixCeil::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    f32 angle = 0.0f;
    if (obj().dirType() != static_cast<map::BinEnemyDirType>(0) && obj().dirType() != static_cast<map::BinEnemyDirType>(1)) {
        f32 rot = Utility::GetRotByDirType(obj());
        angle = Math::Atan2DegF(Math::SinDegF(rot), -Math::CosDegF(rot));
    }
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setAimAngle(angle);
    return true;
}

}}}}  // namespace scn::step::enemy::shotzo
