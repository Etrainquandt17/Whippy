#include "scn/step/enemy/grandlowperbullet/StateBomb.h"

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

StateBomb::StateBomb(Enemy* enemy) : StateBase(enemy), mIsLanded(false), mFallAccel(0.0f), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    mFrame = obj().param().grandlowperbullet().mBombFrame;
}

StateBomb::~StateBomb() {}

void StateBomb::procAnim() {
    if (mIsLanded) {
        if (mFrame != 0) {
            mFrame--;
        } else {
            hel::math::Vector2 pos = Utility::GetCenterPos(obj()).getXY();
            hel::math::Vector2 offset = hel::math::Vector2::ZERO;
            weapon::Desc desc(static_cast<weapon::Kind>(0x2f), 2, static_cast<ostop::Flag>(4), pos, offset,
                              obj().objColl().owner());
            obj().comp().weaponManager().request(desc);
            obj().comp().permSoundSE().start(0x3a5);
            obj().dead();
        }
    }
}

void StateBomb::procMove() {
    const ParamData& param = obj().param().grandlowperbullet();
    if (!mIsLanded) {
        mFallAccel += param.mBombFallAccelStep;
        gobj::MoveParamDecel decel = gobj::MoveParamDecel::Zero();
        gobj::MoveParamFall fall = gobj::MoveParamFall::Create(param._8, mFallAccel, param._c);
        obj().move().airDecelFall(decel, fall);
    }
}

void StateBomb::procFixPos() {
    if (!mIsLanded) {
        chara::MapCollResult result = obj().mapColl().result();
        if (result.isHit()) {
            mIsLanded = true;
            obj().soundSE().start(0x3a6);
        }
    }
}

}}}}  // namespace scn::step::enemy::grandlowperbullet
