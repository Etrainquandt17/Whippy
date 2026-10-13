#include "scn/step/enemy/mahoroamagicball/StateSatellite.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
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
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/mahoroamagicball/Custom.h"
#include "scn/step/enemy/mahoroamagicball/ParamData.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

StateSatellite::StateSatellite(Enemy* enemy) : StateBase(enemy), mAngle(0.0f), mRadius(0.0f) {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().nururi().setValid(false);
    obj().mapColl().setValid(false);
    obj().objColl().setBodyCollStateHitOnly();
    obj().model().reqScript(7);
    mAngle = 120.0f * static_cast<f32>(obj().level());
    obj().model().updateMtx();
}

StateSatellite::~StateSatellite() {
    obj().mapColl().setValid(false);
}

void StateSatellite::procAnim() {
    mAngle += 8.0f;
    if (mAngle >= 360.0f) {
        mAngle -= 360.0f;
    }
    if (mAngle < 360.0f) {
        mAngle += 360.0f;
    }
}

void StateSatellite::procMove() {}

void StateSatellite::procConstraint() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!custom.isOwnerAlive()) {
        obj().dead();
        return;
    }
    hel::math::Vector3 pos = custom.owner()->location().pos() + hel::math::Vector3(0.0f, 2.0f, 0.0f);
    mRadius = hel::math::Math::Interpolate(mRadius, 2.0f, 0.05f);
    hel::math::Vector3 offset(0.0f, mRadius, 0.0f);
    offset.rotate(hel::math::Vector3::AXIS_Z, 0.017453292f * mAngle);
    hel::math::Vector3 newPos = pos + offset;
    obj().location().setPos(newPos);
    if (hel::math::Math::AbsF32(obj().location().pos().z) < 7.0f) {
        obj().vacuumReceiver().setIsValid(true);
        obj().objColl().setBodyCollStateHitOnly();
    } else {
        obj().vacuumReceiver().setIsValid(false);
        obj().objColl().setBodyCollStateXlu();
    }
}

void StateSatellite::procFixPos() {}

}}}}  // namespace scn::step::enemy::mahoroamagicball
