#include "scn/step/boss/mahoroaroah/Custom.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
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
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
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
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

Custom::Custom(Boss& boss) : CustomBase(boss), mBodyEffectCtrl(boss), mSubAnimCtrl(boss), mWaftCtrl(boss) {}

void Custom::onInit() {
    obj().hitPoint().init(1);
    obj().objColl().bodyColl().clear();
    obj().mapColl().setValid(false);
    obj().model().reqScript(0);
    mSubAnimCtrl.setup();
}

void Custom::onAppear() {}

void Custom::onStart() {}

void Custom::onDamage() {}

void Custom::onDead() {}

void Custom::onProcAnim() {
    if (obj().model().anim().currentG3DAnimIndex() != 0x15 && obj().model().anim().currentG3DAnimIndex() != 0x17) {
        obj().model().rotCtrl().setRotHTargetDefault(0.0f);
    }
    mSubAnimCtrl.update();
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(0);
    }
}

void Custom::onProcMove() {
    mWaftCtrl.update();
}

void Custom::onProcFixPos() {}

void Custom::onProcObjCollReact() {}

void Custom::reqMotionWait() {
    obj().model().reqScript(0);
}

void Custom::reqMotionAppearFirstWarpOut(bool flag) {
    if (flag) {
        obj().model().reqScript(5);
    } else {
        obj().model().reqScript(1);
    }
    mBodyEffectCtrl.setVisible(false);
    mWaftCtrl.setToValid();
}

void Custom::reqMotionAppearFirstWarpIn() {
    obj().model().reqScript(6);
    mBodyEffectCtrl.setInvisible();
}

void Custom::reqMotionDead() {
    obj().model().reqScript(4);
}

void Custom::reqMotionStar() {
    obj().model().reqScript(7);
}

void Custom::reqMotionBoomerang(ScriptKind kind) {
    switch (kind) {
    case ScriptKind_8:
    case ScriptKind_9:
    case ScriptKind_10:
        obj().model().reqScript(kind);
        break;
    default:
        break;
    }
}

void Custom::reqMotionStorm() {
    obj().model().reqScript(0xB);
}

void Custom::reqMotionStormEnd() {
    obj().model().reqScript(0xC);
}

void Custom::reqMotionOar() {
    obj().model().reqScript(0xD);
}

void Custom::reqMotionWarpIn() {
    obj().model().reqScript(0xE);
    mBodyEffectCtrl.setInvisible();
}

void Custom::reqMotionWarpOut() {
    obj().model().reqScript(0xF);
    mBodyEffectCtrl.setVisible(true);
}

void Custom::reqMotionBullet(u32 kind) {
    obj().model().reqScript(kind + 0xF);
}

void Custom::reqMotionAnger() {
    obj().model().reqScript(0x16);
}

void Custom::reqMotionEscapeWarpIn() {
    obj().model().reqScript(0x17);
    mBodyEffectCtrl.setInvisible();
    mBodyEffectCtrl.releaseAfterImage();
}

void Custom::reqMotionEscapeWarpOut() {
    obj().model().reqScript(0x18);
    mBodyEffectCtrl.setVisible(false);
}

BodyEffectCtrl& Custom::bodyEffectCtrl() {
    return mBodyEffectCtrl;
}

WaftCtrl& Custom::waftCtrl() {
    return mWaftCtrl;
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
