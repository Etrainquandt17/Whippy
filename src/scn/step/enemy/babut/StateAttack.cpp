#include "scn/step/enemy/babut/StateAttack.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/babut/Custom.h"
#include "scn/step/enemy/babut/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0), mDamageWait(obj().param().babut().mAttackDamageWait) {
    obj().model().reqScript(8);
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enableResistCaptureHero();
    custom.setDamageCaptureHero(obj().param().babut().mAttackDamage, false);
    hel::math::Vector2 heroPos = Utility::GetNearestPlayerPos(obj());
    hel::math::Vector2 diff = heroPos - obj().location().pos().getXY();
    obj().target().setIsRightDir(diff.x > 0.0f);
    f32 angle;
    if (obj().target().isRightDir()) {
        angle = hel::math::Math::Atan2DegF(diff.y, diff.x);
    } else {
        angle = -hel::math::Math::Atan2DegF(diff.y, -diff.x);
    }
    hel::math::Matrix34 trans = hel::math::Matrix34::CreateTrans(hel::math::Vector3(0.0f, 0.7f, 0.0f));
    hel::math::Matrix34 transBack = hel::math::Matrix34::CreateTrans(hel::math::Vector3(0.0f, -0.7f, 1.0f));
    hel::math::Matrix34 rot = hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3(0.0f, 0.0f, 1.0f), angle);
    hel::math::Matrix34 rotY =
        hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3(0.0f, 1.0f, 0.0f), obj().target().isRightDir() ? 80.0f : -80.0f);
    obj().model().setCustomMtx(trans * rot * transBack * rotY);
    obj().soundSEState().start(0x2f2);
}

StateAttack::~StateAttack() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).disableResistCaptureHero();
    obj().model().unsetCustomMtx();
}

void StateAttack::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const ParamData& param = obj().param().babut();
    if (--mDamageWait == 0) {
        obj().model().reqScript(8);
        mDamageWait = param.mAttackDamageWait;
        custom.setDamageCaptureHero(param.mAttackDamage, false);
    }
    mFrame++;
    if (mFrame > param.mAttackFrame || custom.chkReleaseHero()) {
        if (custom.chkReleaseHero()) {
            custom.setSuccessCaptureHero();
        }
        obj().brainCtrl().toValid();
        custom.vomitCaptureHero();
        custom.setDamageCaptureHero(0, true);
    }
}

void StateAttack::procMove() {
    obj().move().resetVelocity();
    hel::math::Vector2 heroPos = Utility::GetNearestPlayerPos(obj());
    hel::math::Vector2 dir = heroPos - obj().location().pos().getXY();
    if (!dir.isZero()) {
        dir.normalize();
        hel::math::Vector2 target = heroPos - dir * 0.6f;
        hel::math::Vector2 pos = obj().location().pos().getXY();
        pos += (target - pos) * 0.2f;
        obj().location().setPos(pos.toVector3());
    }
}

}
}
}
}
