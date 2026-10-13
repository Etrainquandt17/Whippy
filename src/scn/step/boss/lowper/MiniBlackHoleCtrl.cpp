#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#include "scn/step/boss/lowper/MiniBlackHoleCtrl.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/LowperWindCtrl.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/DataBuff.h"
#include "scn/step/boss/lowper/EnemyCtrl.h"
#include "scn/step/boss/lowper/GearCtrl.h"
#include "scn/step/boss/lowper/ItemCtrl.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/boss/lowper/WaftMoveCtrl.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

MiniBlackHoleCtrl::MiniBlackHoleCtrl(Boss& boss) : mBoss(boss), mFrame(0), mWindId(-1), mWeapon() {}

MiniBlackHoleCtrl::~MiniBlackHoleCtrl() {
    clear();
}

void MiniBlackHoleCtrl::update() {
    if (mFrame != 0) {
        mFrame--;
        if (mFrame == 0 || mWeapon.isNull()) {
            clear();
        }
    }
}

void MiniBlackHoleCtrl::set(u32 frame, f32 _2, f32 _3, f32 _4) {
    mFrame = frame;
    hel::math::Vector3 bossPos = mBoss.location().pos();
    hel::math::Vector2 pos = bossPos.getXY();
    pos.y += 0.5f;
    mWindId = mBoss.comp().bossManager().lowperWindCtrl().set(pos, _2, _3, _4);
    weapon::Desc desc(static_cast<weapon::Kind>(0x81), 0, static_cast<ostop::Flag>(8), pos, hel::math::Vector2::ZERO,
                      mBoss.objColl().owner());
    mWeapon = mBoss.comp().weaponManager().request(desc);
}

void MiniBlackHoleCtrl::clear() {
    mFrame = 0;
    mBoss.comp().bossManager().lowperWindCtrl().clear(mWindId);
    if (mWeapon.isAlive()) {
        mWeapon->dead();
    }
}

bool MiniBlackHoleCtrl::canSetBlackHole(f32 x) const {
    x += mBoss.basePos().x;
    return mBoss.comp().bossManager().lowperWindCtrl().canSet(x);
}

}}}}  // namespace scn::step::boss::lowper
