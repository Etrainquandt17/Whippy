#include "scn/step/enemy/shotzo/BrainFix.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/shotzo/Custom.h"
#include "scn/step/enemy/shotzo/StateWait.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

BrainFix::BrainFix(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFix::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setAimAngle(Utility::GetRotByDirType(obj()));
    return true;
}

}}}}  // namespace scn::step::enemy::shotzo
