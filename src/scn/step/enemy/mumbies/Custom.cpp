#include "scn/step/enemy/mumbies/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/damage/StateDeadInWater.h"
#include "scn/step/enemy/mumbies/StateEndure.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace mumbies {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mEndureFlag(false), mIsDead(false) {
    obj().nururi().changeSetting(static_cast<nururi::Mode>(1));
}

bool Custom::onVacuumResist() {
    if (!mEndureFlag && !mIsDead) {
        obj().stateChanger().setNextState<StateEndure, Enemy*>(&obj());
        mEndureFlag = true;
    }
    return true;
}

bool Custom::onInWater() {
    obj().stateChanger().setNextState<damage::StateDeadInWater, Enemy*>(&obj());
    return false;
}

bool Custom::onHitPointIsZero() {
    mIsDead = true;
    return false;
}

bool Custom::onDamaged() {
    mIsDead = true;
    return false;
}

void Custom::onCaptured() {
    mIsDead = true;
}

bool Custom::onRecover() {
    mIsDead = false;
    return false;
}

void Custom::setEndureFlag(bool endureFlag) {
    mEndureFlag = endureFlag;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::enemy::mumbies
