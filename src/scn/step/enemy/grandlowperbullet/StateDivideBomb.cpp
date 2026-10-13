#include "scn/step/enemy/grandlowperbullet/StateDivideBomb.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/grandlowperbullet/ParamData.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

StateDivideBomb::StateDivideBomb(Enemy* enemy)
    : StateBase(enemy), mIsLanded(false), mFallAccel(0.0f), mFrame(0), mShakeFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    const ParamData& param = obj().param().grandlowperbullet();
    mFrame = param.mDivideFrame;
    mShakeFrame = param.mDivideShakeFrame;
}

StateDivideBomb::~StateDivideBomb() {}

void StateDivideBomb::procAnim() {
    if (mIsLanded) {
        if (mFrame != 0) {
            mFrame--;
            if (mShakeFrame != 0) {
                mShakeFrame--;
            } else {
                mShakeFrame = 4;
                obj().model().shake().request(static_cast<chara::ShakeKind>(2));
            }
        } else {
            obj().comp().permSoundSE().start(0x55b);
            reqBullet(1.0f);
            reqBullet(-1.0f);
            obj().dead();
        }
    }
}

void StateDivideBomb::procMove() {
    const ParamData& param = obj().param().grandlowperbullet();
    if (!mIsLanded) {
        mFallAccel += param.mBombFallAccelStep;
        gobj::MoveParamDecel decel = gobj::MoveParamDecel::Zero();
        gobj::MoveParamFall fall = gobj::MoveParamFall::Create(param._8, mFallAccel, param._c);
        obj().move().airDecelFall(decel, fall);
    }
}

void StateDivideBomb::procFixPos() {
    if (!mIsLanded) {
        chara::MapCollResult result = obj().mapColl().result();
        if (result.isHit()) {
            mIsLanded = true;
            obj().soundSE().start(0x3a6);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x2b4), 0);
        }
    }
}

void StateDivideBomb::reqBullet(f32 sign) {
    const ParamData& param = obj().param().grandlowperbullet();
    hel::math::Vector3 pos = obj().location().pos();
    pos.y += 1.0f;
    hel::math::Vector3 velocity(sign * param.mDivideSpeed, 0.0f, 0.0f);
    weapon::Desc desc(static_cast<weapon::Kind>(0x8c), 0, static_cast<ostop::Flag>(8), pos.getXY(), velocity.getXY(),
                      obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

}}}}  // namespace scn::step::enemy::grandlowperbullet
