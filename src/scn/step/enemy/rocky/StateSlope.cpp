#include "scn/step/enemy/rocky/StateSlope.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/rocky/Custom.h"
#include "scn/step/enemy/rocky/ParamData.h"
#include "scn/step/enemy/rocky/StateFall.h"
#include "scn/step/enemy/rocky/StateStay.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

StateSlope::StateSlope(Enemy* enemy) : StateBase(enemy), mNormalX(0.0f) {
    obj().footState().setGround();
    obj().model().reqScript(11);
    obj().move().resetSpeedV();
    obj().move().resetSpeedH();
    hel::math::Vector2 normal = obj().mapColl().floorNormal();
    mNormalX = normal.x;
    obj().model().rotCtrl().setRotVTarget(hel::math::Math::Atan2DegF(-normal.x, normal.y));
    obj().model().rotCtrl().setRotV(hel::math::Math::Atan2DegF(-normal.x, normal.y));
}

StateSlope::~StateSlope() {}

void StateSlope::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(11);
    }
}

void StateSlope::procMove() {
    obj().move().setSpeedH(mNormalX * obj().param().rocky().mSlopeSpeed);
    obj().move().groundDecel(obj().param().rocky().mSlopeDecel);
}

void StateSlope::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setFallSpeedUp(true);
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
        return;
    }
    hel::math::Vector2 normal = obj().mapColl().floorNormal();
    f32 x = hel::math::Math::Abs(normal.x);
    if (x < obj().param().rocky().mSlopeStayNormalX) {
        obj().model().rotCtrl().setRotV(0.0f);
        obj().stateChanger().setNextState<StateStay, Enemy*>(objPtr());
    } else {
        mNormalX = normal.x;
        obj().model().rotCtrl().setRotVTarget(hel::math::Math::Atan2DegF(-normal.x, normal.y));
    }
}

}}}}  // namespace scn::step::enemy::rocky
