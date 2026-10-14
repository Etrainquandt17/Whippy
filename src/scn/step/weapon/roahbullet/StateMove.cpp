#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/weapon/roahbullet/StateMove.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/roahbullet/Custom.h"
#include "scn/step/weapon/roahbullet/Param.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCast;
using hel::math::Matrix34;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

StateMove::StateMove(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    Vector3 target = Vector3::ZERO;
    u32 num = obj().comp().bossManager().getBossCount();
    for (u32 i = 0; i < num; i++) {
        ObjRefHandle<boss::Boss> boss = obj().comp().bossManager().getBossByIndex(i);
        if (boss.isAlive() && boss->kind() == 0xE) {
            target = boss::Utility::GetHatedHeroPos(*boss.operator->());
        }
    }
    mDir = target - obj().location().pos();
    mDir.normalize();
    switch (obj().variation()) {
    case 0:
        obj().soundSE().start(0x45D);
        break;
    case 1:
        obj().soundSE().start(0x45C);
        break;
    }
}

void StateMove::procAnim() {
    const Param& param = obj().param().roahBullet();
    mFrame++;
    if (mFrame == param._30) {
        obj().dead();
    } else {
        f32 rate = static_cast<f32>(mFrame % param._2C) / static_cast<f32>(param._2C);
        obj().model().model().nodes().at(0).localMtx().setRTMtx(
            Matrix34::CreateRotXYZDeg(Vector3(360.0f * -rate, 0.0f, 0.0f))
        );
    }
}

void StateMove::procMove() {
    const Param& param = obj().param().roahBullet();
    switch (obj().variation()) {
    case 0:
        obj().move().accel(mDir, param._20);
        break;
    case 1:
        obj().move().accel(Vector3::BASIS_X * -1.0f, param._20);
        break;
    }
}

void StateMove::procFixPos() {
    DynamicCast<Custom*, ICustom>(obj().custom())->procFixPos();
    if (weapon::Utility::CheckShootingCulling(obj())) {
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::roahbullet
