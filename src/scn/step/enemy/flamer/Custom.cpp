#include "scn/step/enemy/flamer/Custom.h"

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
#include "scn/step/enemy/flamer/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mAttackCount(0), mIsMove(true) {
    obj().nururi().changeSetting(static_cast<nururi::Mode>(1));
}

void Custom::attack() {
    mAttackCount++;
}

bool Custom::isAttackEnd() const {
    return mAttackCount >= obj().param().flamer().mAttackNum;
}

void Custom::dead() {
    obj().deadWithEffect();
}

bool Custom::isMove() const {
    return mIsMove;
}

void Custom::setIsMove(bool isMove) {
    mIsMove = isMove;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::flamer
