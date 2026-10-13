#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/weapon/metalgeneralbitshot/StateMain.h"

#include "gobj/Move.h"
#include "ocoll/Hit.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace metalgeneralbitshot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0), mDir() {
    const VariationParam& variationParam = param();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1DD));
    obj().objColl().addAttack(0, variationParam._0);
    obj().objColl().addHit(0, variationParam._4);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x455), 0);
    obj().move().resetVelocity();
    hel::math::Vector3 target = hel::math::Vector3::ZERO;
    u32 num = obj().comp().bossManager().getBossCount();
    for (u32 i = 0; i < num; i++) {
        util::ObjRefHandle<boss::Boss> boss = obj().comp().bossManager().getBossByIndex(i);
        if (boss.isAlive() && boss->kind() == 0xB) {
            target = boss::Utility::GetHatedHeroPos(*boss.operator->());
        }
    }
    mDir = target - obj().location().pos();
    mDir.normalize();
    obj().soundSE().start(0x3F5);
}

void StateMain::procAnim() {
    const VariationParam& variationParam = param();
    mFrame++;
    if (mFrame >= variationParam._8) {
        obj().dead();
    }
}

void StateMain::procMove() {
    const VariationParam& variationParam = param();
    switch (obj().variation()) {
    case 0:
        obj().move().accel(mDir, variationParam._C);
        break;
    case 1:
        obj().move().accel(hel::math::Vector3::BASIS_Y * -1.0f, variationParam._C);
        break;
    }
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().deadWithEffect();
    }
}

void StateMain::procObjCollReact() {
    if (obj().objColl().hit().isCollide()) {
        obj().deadWithEffect();
    }
}

const VariationParam& StateMain::param() {
    const Param& param = obj().param().metalGeneralBitShot();
    const VariationParam* result = 0;
    switch (obj().variation()) {
    case 0:
        result = &param._0;
        break;
    case 1:
        result = &param._18;
        break;
    }
    return *result;
}

}}}}  // namespace scn::step::weapon::metalgeneralbitshot
