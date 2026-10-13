#include "scn/step/weapon/roahbullet/StateMoveUp.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/roahbullet/Custom.h"
#include "scn/step/weapon/roahbullet/Param.h"
#include "scn/step/weapon/roahbullet/StateZMove.h"

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
        hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(360.0f * rate, 0.0f, 0.0f))
    );
}

void StateMoveUp::procMove() {
    const Param& param = obj().param().roahBullet();
    f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(param._34);
    hel::math::Vector2 pos = hel::math::Vector2::ZERO;
    pos.x = hel::math::Math::LinearInterpolation(
        mStartPos.x,
        mEndPos.x,
        1.0f - (1.0f - hel::math::Math::SinDegF(90.0f * rate)) * (1.0f - hel::math::Math::SinDegF(90.0f * rate))
    );
    pos.y = hel::math::Math::LinearInterpolation(
        mStartPos.y,
        mEndPos.y,
        (1.0f - hel::math::Math::CosDegF(90.0f * rate)) * (1.0f - hel::math::Math::CosDegF(90.0f * rate))
    );
    obj().location().setPos(pos.toVector3());
}

void StateMoveUp::procFixPos() {
    hel::common::DynamicCast<Custom*, ICustom>(obj().custom())->procFixPos();
}

}}}}  // namespace scn::step::weapon::roahbullet
