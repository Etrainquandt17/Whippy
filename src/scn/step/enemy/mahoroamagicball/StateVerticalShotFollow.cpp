#include "scn/step/enemy/mahoroamagicball/StateVerticalShotFollow.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/mahoroamagicball/Custom.h"
#include "scn/step/enemy/mahoroamagicball/StateVerticalShotShot.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

namespace {

const f32 T_VVEL_TABLE[6] = { 0.08f, -0.08f, 0.14f, -0.14f, 0.18f, -0.18f };

}

StateVerticalShotFollow::StateVerticalShotFollow(Enemy* enemy) : StateBase(enemy), mFrame(0), mOffset(), mVelocity() {
    if (!DynamicCastToRef<Custom, ICustom>(obj().custom()).isOwnerAlive()) {
        obj().dead();
        return;
    }
    obj().footState().setAir();
    obj().nururi().setValid(false);
    obj().mapColl().setValid(false);
    obj().vacuumReceiver().setIsValid(false);
    obj().model().reqScript(8);
    obj().objColl().bodyColl().setStateXlu();
    u32 index = obj().level();
    if (index > 5) {
        index = 5;
    }
    mVelocity.x = T_VVEL_TABLE[index];
}

StateVerticalShotFollow::~StateVerticalShotFollow() {
    obj().mapColl().setValid(true);
}

void StateVerticalShotFollow::procAnim() {
    if (mFrame < 80) {
        mFrame++;
        if (mFrame == 80) {
            obj().objColl().bodyColl().setStateNormal();
            obj().vacuumReceiver().setIsValid(true);
        }
    }
    if (obj().signal().isValid()) {
        u32 signal = obj().signal().get();
        obj().signal().clear();
        if (signal == 1) {
            obj().stateChanger().setNextState<StateVerticalShotShot, Enemy*>(objPtr());
        }
    }
}

void StateVerticalShotFollow::procMove() {}

void StateVerticalShotFollow::procConstraint() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isOwnerAlive()) {
        f32 rate = static_cast<f32>(mFrame) / 80.0f;
        Vector3 center = custom.owner()->location().pos();
        mOffset += mVelocity * (1.0f - rate);
        Vector3 pos = mOffset;
        Vector3 axis = Vector3::BASIS_Y;
        axis.rotate(Vector3::AXIS_X, 0.34906584f);
        f32 angle = 1080.0f * Math::SinDegF(90.0f * rate);
        pos.rotate(axis, 0.017453292f * angle);
        pos.z *= 2.5f;
        pos += center;
        obj().location().setPos(pos);
    }
}

void StateVerticalShotFollow::procFixPos() {}

}}}}  // namespace scn::step::enemy::mahoroamagicball
