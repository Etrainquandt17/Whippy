#include "scn/step/boss/galactaknight/Custom.h"

#include "g3d/ColorAnimFlashOp.h"
#include "g3d/FogAccessor.h"
#include "g3d/Root.h"
#include "gobj/Anim.h"
#include "gobj/Target.h"
#include "hel/common/Color.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/CustomFlash.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Handicap.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateCallback.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/StateDamageL.h"
#include "scn/step/boss/galactaknight/StateDead.h"
#include "scn/step/boss/galactaknight/StateFirst.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/core/G3DRootSet.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

Custom::Custom(Boss& boss)
    : CustomBase(boss), mCollisionCtrl(boss), mLandCtrl(boss), mCaptureCtrl(boss), mSwordBeamCtrl(boss), mThunderSpineCtrl(boss),
      _180(false), _184(0) {}

void Custom::onInit() {
    const Param& param = obj().param().galactaknight();
    obj().hitPoint().init(param._0);
    obj().angry().setAngryHpRate(param._4);
    Utility::SetDamagePreventMikeAndCrash(obj());
    obj().location().setToCenter(hel::math::Vector3(0.0f, 0.5f, 0.0f));
    obj().handicap().setup();
    obj().target().setIsRightDir(false);
    obj().shadow().changeDiameter(1.0f);
    obj().shadow().changeMaxHeight(12.0f);
    obj().shadow().setVisibility(true);
    g3d::FogAccessor fog = obj().comp().g3dRootSet().root(static_cast<core::DrawLayerKind>(6)).fog();
    fog.setFogType(static_cast<GXFogType>(2));
    fog.setZ(50.0f, 300.0f);
    fog.setFogColor(static_cast<GXColor>(hel::common::Color(180, 150, 200, 255)));
    fog.setFogRangeAdj(true);
    obj().model().rotCtrl().setRotHTargetDefault(50.0f);
    obj().brainCtrl().set("Scn.Step.Boss.GalactaKnight.Brain.Exec");
    obj().angry().setChangeBrain("Scn.Step.Boss.GalactaKnight.Brain.ExecAngry");
    obj().stateCallback().setCanClearAttack(false);
    obj().stateChanger().setNextState<StateFirst, Boss*>(objPtr());
}

void Custom::onAppear() {}

void Custom::onStart() {}

void Custom::onDamage() {
    obj().model().shake().request(static_cast<chara::ShakeKind>(4));
}

void Custom::onDead() {
    obj().model().shake().request(static_cast<chara::ShakeKind>(5));
    obj().brainCtrl().set("Scn.Step.Boss.GalactaKnight.Brain.ExecEscape");
    obj().stateChanger().setNextState<StateDead, Boss*>(objPtr());
}

void Custom::onStateChange() {
    mCollisionCtrl.onStateChange();
}

void Custom::onProcAnim() {
    if (_180) {
        const Param& param = obj().param().galactaknight();
        if (_184 < param._2C) {
            _184++;
        }
        u8 alpha = 255.0f * (static_cast<f32>(_184) / static_cast<f32>(param._2C));
        hel::common::Color color(255, 255, 255, alpha);
        obj().flash().custom().setOperation(static_cast<g3d::ColorAnimFlashOp>(1));
        obj().flash().custom().setIsValid(true);
        obj().flash().custom().setColor(color);
    }
}

void Custom::onProcMove() {}

void Custom::onProcFixPos() {
    if (obj().angry().check()) {
        obj().stateChanger().setNextState<StateDamageL, Boss*>(objPtr());
        obj().stateChanger().changeStateIfPossible();
    }
    mCollisionCtrl.update();
}

void Custom::onProcObjCollReact() {}

void Custom::setWhiteColorAnim() {
    _180 = true;
}

CollisionCtrl& Custom::collisionCtrl() {
    return mCollisionCtrl;
}

LandCtrl& Custom::landCtrl() {
    return mLandCtrl;
}

CaptureCtrl& Custom::captureCtrl() {
    return mCaptureCtrl;
}

SwordBeamCtrl& Custom::swordBeamCtrl() {
    return mSwordBeamCtrl;
}

ThunderSpineCtrl& Custom::thunderSpineCtrl() {
    return mThunderSpineCtrl;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();
