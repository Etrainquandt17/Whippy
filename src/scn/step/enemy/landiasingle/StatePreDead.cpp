#include "scn/step/enemy/landiasingle/StatePreDead.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/Color.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/SingleCtrl.h"
#include "scn/step/boss/landia/SingleWeaponCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Flash.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/landiasingle/Custom.h"
#include "scn/step/enemy/landiasingle/ParamData.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

StatePreDead::StatePreDead(Enemy* enemy) : StateBase(enemy), mFlashFrame(0), mFrame(0) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x13);
    obj().move().resetVelocity();
    f32 x = obj().location().pos().x;
    if (obj().comp().mainCamera().getCenter().x < x) {
        obj().target().setIsRightDir(false);
    } else {
        obj().target().setIsRightDir(true);
    }
    obj().soundSE().start(0x47c);
    custom.headAngleCtrl().toInvalid();
}

StatePreDead::~StatePreDead() {}

void StatePreDead::procAnim() {
    if (obj().signal().isValid() && obj().signal().get() == 0x19) {
        obj().signal().clear();
        mFlashFrame = 40;
    }
    if (mFlashFrame != 0) {
        f32 rate = static_cast<f32>(mFlashFrame) / 40.0f;
        if (rate > 1.0f) {
            rate = 1.0f;
        }
        u8 value = static_cast<u8>(255.0f * rate);
        obj().flash().setEnf1F(hel::common::Color(value, value, value, 0xff), static_cast<g3d::ColorAnimFlashOp>(2));
        mFlashFrame--;
    }
    mFrame++;
    if (mFrame % 5 == 0) {
        if (mFrame > 50) {
            obj().model().shake().request(static_cast<chara::ShakeKind>(2));
        } else {
            obj().model().shake().request(static_cast<chara::ShakeKind>(1));
        }
    }
}

// TODO: the two word copies inside Vector3::squareDistance (its own and the one of operator-) sit in swapped stack
// slots: the original has the difference at 0x3c and the copy of the centre at 0x24.
void StatePreDead::procMove() {
    const ParamData& param = obj().param().landiasingle();
    f32 distance = hel::math::Math::SqrtF(
        obj().location().pos().squareDistance(obj().comp().mainCamera().getCenter().toVector3()));
    if (distance > param._190) {
        obj().location().setPos(obj().comp().mainCamera().getCenter().toVector3() * param._18c
                                + obj().location().pos() * (1.0f - param._18c));
    }
}

void StatePreDead::procFixPos() {}

}
}
}
}
