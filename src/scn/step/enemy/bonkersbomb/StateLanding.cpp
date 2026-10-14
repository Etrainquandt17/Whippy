#include "scn/step/enemy/bonkersbomb/StateLanding.h"

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
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/bonkersbomb/Custom.h"
#include "scn/step/enemy/bonkersbomb/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace bonkersbomb {

StateLanding::StateLanding(Enemy* enemy) : StateBase(enemy), mFrame(0), mRot(0.0f), mRotSpeed(0.0f) {
    const ParamData::Landing& param =
        obj().size() == 0 ? obj().param().bonkersbomb().mLanding : obj().param().bonkersbomb().mLandingBig;
    mRot = obj().model().rotCtrl().getRotV();
    mRotSpeed = param.mRotSpeed;
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().move().resetVelocity();
    obj().move().setSpeedH(param.mSpeedH * obj().target().getSign());
    if (obj().size() != 0) {
        obj().model().shake().request(static_cast<chara::ShakeKind>(3));
        obj().model().setViewOffset(Vector3(0.0f, -0.3f, 0.0f));
    }
    if (obj().size() == 0) {
        obj().soundSE().start(0x5ad);
    } else {
        obj().soundSE().start(0x5ba);
    }
}

StateLanding::~StateLanding() {}

void StateLanding::procAnim() {
    const ParamData::Landing& param =
        obj().size() == 0 ? obj().param().bonkersbomb().mLanding : obj().param().bonkersbomb().mLandingBig;
    mRotSpeed -= param.mRotDecel;
    mRotSpeed = Math::Max(mRotSpeed, 0.0f);
    mRot = obj().model().rotCtrl().calcChangedRot(mRot, obj().target().isRightDir(), -mRotSpeed);
    obj().model().rotCtrl().initRotV(mRot);
    mFrame++;
    if (mFrame == param.mFrame) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).onDamaged();
        obj().deadWithEffect();
    }
}

void StateLanding::procMove() {
    const ParamData::Landing& param =
        obj().size() == 0 ? obj().param().bonkersbomb().mLanding : obj().param().bonkersbomb().mLandingBig;
    obj().move().groundDecel(param.mDecel);
}

void StateLanding::procFixPos() {}

}}}}  // namespace scn::step::enemy::bonkersbomb
