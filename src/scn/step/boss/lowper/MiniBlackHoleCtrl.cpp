#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#include "scn/step/boss/lowper/MiniBlackHoleCtrl.h"

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/LowperWindCtrl.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

using hel::math::Vector2;
using hel::math::Vector3;

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
    Vector3 bossPos = mBoss.location().pos();
    Vector2 pos = bossPos.getXY();
    pos.y += 0.5f;
    mWindId = mBoss.comp().bossManager().lowperWindCtrl().set(pos, _2, _3, _4);
    weapon::Desc desc(static_cast<weapon::Kind>(0x81), 0, static_cast<ostop::Flag>(8), pos, Vector2::ZERO,
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
