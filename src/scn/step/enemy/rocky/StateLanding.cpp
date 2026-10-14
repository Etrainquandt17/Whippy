#include "scn/step/enemy/rocky/StateLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/rocky/Custom.h"
#include "scn/step/enemy/rocky/ParamData.h"
#include "scn/step/enemy/rocky/StateFall.h"
#include "scn/step/enemy/rocky/StateSlope.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Direction3;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

StateLanding::StateLanding(Enemy* enemy) : StateBase(enemy), mNormalX(0.0f), mIsEffectRequested(false) {
    obj().footState().setGround();
    obj().model().reqScript(2);
    obj().move().resetSpeedV();
    obj().move().resetSpeedH();
    Vector2 normal = obj().mapColl().floorNormal();
    mNormalX = normal.x;
    obj().model().rotCtrl().setRotV(Math::Atan2DegF(-normal.x, normal.y));
    obj().soundSE().start(0x2c2);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setFallSpeedUp(false);
}

StateLanding::~StateLanding() {}

void StateLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        f32 x = Math::Abs(mNormalX);
        if (x < obj().param().rocky().mLandingSlopeNormalX) {
            obj().brainCtrl().toValid();
        } else {
            obj().stateChanger().setNextState<StateSlope, Enemy*>(objPtr());
        }
    }
}

void StateLanding::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
        return;
    }
    Vector2 normal = obj().mapColl().floorNormal();
    mNormalX = normal.x;
    obj().model().rotCtrl().setRotV(Math::Atan2DegF(-normal.x, normal.y));
    if (!mIsEffectRequested) {
        Vector3 right = obj().location().pos();
        Vector3 left = obj().location().pos();
        right.x += normal.y * obj().param().rocky().mLandingEffectOffsetX;
        right.y += -normal.x * obj().param().rocky().mLandingEffectOffsetY;
        left.x += -normal.y * obj().param().rocky().mLandingEffectOffsetX;
        left.y += normal.x * obj().param().rocky().mLandingEffectOffsetY;
        Direction3 rightDir(Vector3(-normal.y, normal.x, 0.0f), Vector3(normal.x, normal.y, 0.0f),
                            Vector3(0.0f, 0.0f, 1.0f));
        Direction3 leftDir(Vector3(normal.y, -normal.x, 0.0f), Vector3(normal.x, normal.y, 0.0f),
                           Vector3(0.0f, 0.0f, -1.0f));
        obj().effect().normal().requestPD(static_cast<effect::Kind>(0x124), right, rightDir);
        obj().effect().normal().requestPD(static_cast<effect::Kind>(0x124), left, leftDir);
        mIsEffectRequested = true;
    }
}

}}}}  // namespace scn::step::enemy::rocky
