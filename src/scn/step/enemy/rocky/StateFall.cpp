#include "scn/step/enemy/rocky/StateFall.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/rocky/Custom.h"
#include "scn/step/enemy/rocky/ParamData.h"
#include "scn/step/enemy/rocky/StateFall.h"
#include "scn/step/enemy/rocky/StateLanding.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(1);
    obj().model().anim().setFrameRate(1.0f);
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isFallSpeedUp()) {
        obj().move().setSpeedV(obj().param().rocky().mFallSpeedUpSpeedV);
    }
    obj().move().resetSpeedH();
    obj().model().rotCtrl().setRotVTarget(0.0f);
    obj().model().rotCtrl().setRotV(0.0f);
    obj().objColl().bodyColl().setAttackTypeOver(static_cast<ocoll::AttackType>(0x22a));
}

StateFall::~StateFall() {
    obj().objColl().bodyColl().unsetAttackTypeOver();
}

void StateFall::procMove() {
    gobj::MoveParamFall fall = obj().param().rocky().mFall;
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isFallSpeedUp()) {
        fall = obj().param().rocky().mFallSpeedUp;
    }
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), fall);
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::rocky
