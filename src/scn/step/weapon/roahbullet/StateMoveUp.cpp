#include "scn/step/weapon/roahbullet/StateMoveUp.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "pow.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/roahbullet/Custom.h"
#include "scn/step/weapon/roahbullet/Param.h"
#include "scn/step/weapon/roahbullet/StateZMove.h"

using hel::common::DynamicCast;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

StateMoveUp::StateMoveUp(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    const Param& param = obj().param().roahBullet();
    mStartPos = obj().location().pos().getXY();
    mEndPos = static_cast<const Component&>(obj().comp()).mainCamera().getCenter() + param._38;
}

void StateMoveUp::procAnim() {
    const Param& param = obj().param().roahBullet();
    if (mFrame < param._34) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateZMove, Weapon*>(&obj());
        return;
    }
    f32 rate = static_cast<f32>(mFrame % param._40) / static_cast<f32>(param._40);
    obj().model().model().nodes().at(0).localMtx().setRTMtx(
        Matrix34::CreateRotXYZDeg(Vector3(360.0f * rate, 0.0f, 0.0f))
    );
}

void StateMoveUp::procMove() {
    const Param& param = obj().param().roahBullet();
    f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(param._34);
    Vector2 pos = Vector2::ZERO;
    pos.x = Math::LinearInterpolation(mStartPos.x, mEndPos.x, 1.0f - POW2(1.0f - Math::SinDegF(90.0f * rate)));
    pos.y = Math::LinearInterpolation(
        mStartPos.y,
        mEndPos.y,
        (1.0f - Math::CosDegF(90.0f * rate)) * (1.0f - Math::CosDegF(90.0f * rate))
    );
    obj().location().setPos(pos.toVector3());
}

void StateMoveUp::procFixPos() {
    DynamicCast<Custom*, ICustom>(obj().custom())->procFixPos();
}

}}}}  // namespace scn::step::weapon::roahbullet
