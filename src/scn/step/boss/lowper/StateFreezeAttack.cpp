#include "scn/step/boss/lowper/StateFreezeAttack.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateFreezeAttack::StateFreezeAttack(Boss* boss) : StateBase(boss), mDir(Vector3::BASIS_Y), mCount(0) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    Vector3 diff = heroPos - obj().location().pos();
    if (!diff.isZeroLoose(0.00001f)) {
        mDir = diff.getNormalized();
    }
    obj().model().reqScript(0x21);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    obj().guard().setType(static_cast<GuardType>(4));
}

StateFreezeAttack::~StateFreezeAttack() {
    obj().objColl().clearAttack(1);
    obj().model().model().nodes().at(3).localMtx().reset();
}

void StateFreezeAttack::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    } else if (mCount < obj().param().lowper()._74) {
        mCount++;
    }
}

void StateFreezeAttack::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    Vector3 diff = heroPos - obj().location().pos();
    if (diff.length() > 1.0f) {
        mDir = diff.getNormalized();
    }
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._74);
    f32 speed = param._78 * Math::CosDegF(90.0f * t);
    Vector3 center = custom.waftMoveCtrl().getCenter();
    center += mDir * speed;
    custom.waftMoveCtrl().setMoveIntpRate(0.5f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(center);
}

void StateFreezeAttack::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
