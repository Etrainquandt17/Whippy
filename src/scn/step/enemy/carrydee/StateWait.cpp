#include "scn/step/enemy/carrydee/StateWait.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
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
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/carrydee/Custom.h"
#include "scn/step/enemy/carrydee/ParamData.h"
#include "scn/step/enemy/carrydee/StateCarry.h"
#include "scn/step/enemy/carrydee/StateFall.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace carrydee {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(7);
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    const ParamData& param = obj().param().carrydee();
    if (Utility::IsHeroInRange(obj(), param.mCarryRangeH, -param.mCarryRangeH, param.mCarryRangeV, -param.mCarryRangeV) &&
        obj().variation() != 0x13a) {
        f32 playerX = Utility::GetNearestPlayerPos(obj()).x;
        f32 x = obj().location().pos().x;
        obj().target().setIsRightDir(playerX <= x);
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).onCarryStart();
        obj().stateChanger().setNextState<StateCarry, Enemy*>(objPtr());
    }
}

void StateWait::procMove() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).fixPosKey();
}

void StateWait::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::carrydee
