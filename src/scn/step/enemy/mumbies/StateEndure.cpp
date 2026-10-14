#include "scn/step/enemy/mumbies/StateEndure.h"

#include "gobj/FootState.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/mumbies/Custom.h"
#include "scn/step/hero/Manager.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace mumbies {

StateEndure::StateEndure(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(10);
    obj().captureReceiver().setCanCapture(true);
    obj().brainCtrl().toValid();
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setEndureFlag(true);
}

StateEndure::~StateEndure() {}

void StateEndure::procMove() {}

void StateEndure::procFixPos() {
    if (Utility::IsPlayerExist(obj())) {
        Vector3 playerPos = obj().comp().heroManager().getMainPlayerPos();
        bool isRight = playerPos.x > obj().location().pos().x;
        if (isRight != obj().target().isRightDir()) {
            obj().target().setIsRightDir(isRight);
        }
    }
}

}}}}  // namespace scn::step::enemy::mumbies
