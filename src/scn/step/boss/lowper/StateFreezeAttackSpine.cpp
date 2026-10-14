#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#include "scn/step/boss/lowper/StateFreezeAttackSpine.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

namespace {

const f32 T_SPINE_ANGLE_TABLE[] = { 65.0f, 115.0f, 245.0f, 295.0f };

}

StateFreezeAttackSpine::StateFreezeAttackSpine(Boss* boss, u32 frame) : StateBase(boss), mFrame(frame), mCount(0), mWeapons() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().model().reqScript(0x1F);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    obj().guard().setType(static_cast<GuardType>(4));
    reqIceSpine();
}

StateFreezeAttackSpine::~StateFreezeAttackSpine() {
    obj().objColl().clearAttack(1);
}

void StateFreezeAttackSpine::procAnim() {
    if (mCount < mFrame) {
        mCount++;
        if (mCount == mFrame) {
            obj().objColl().clearAttack(1);
            obj().model().reqScript(0x23);
        }
    } else {
        if (obj().scriptTrigger().get(2)) {
            shotIceSpine();
        }
        if (obj().model().isAllEnd()) {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        }
    }
}

void StateFreezeAttackSpine::procMove() {}

void StateFreezeAttackSpine::procFixPos() {}

void StateFreezeAttackSpine::reqIceSpine() {
    Vector3 pos = obj().location().pos();
    pos.y += 0.5f;
    f32 speed = 0.03f;
    weapon::Desc desc(static_cast<weapon::Kind>(0x83), 0, static_cast<ostop::Flag>(8), pos.getXY(), Vector2::ZERO,
                      obj().objColl().owner());
    for (int i = 0; i < 4; i++) {
        Vector2 dir(0.0f, 1.0f);
        dir.rotate(0.017453292f * T_SPINE_ANGLE_TABLE[i]);
        desc._1c = dir * speed;
        mWeapons[i] = obj().comp().weaponManager().request(desc);
    }
    obj().soundSE().normal().start(0x561);
}

void StateFreezeAttackSpine::shotIceSpine() {
    f32 speed = obj().param().lowper()._7C;
    for (int i = 0; i < 4; i++) {
        if (mWeapons[i].isAlive()) {
            Vector2 dir(0.0f, 1.0f);
            dir.rotate(0.017453292f * T_SPINE_ANGLE_TABLE[i]);
            dir *= speed;
            mWeapons[i]->move().setVelocity(dir.toVector3());
        }
    }
    obj().soundSE().normal().start(0x562);
}

}}}}  // namespace scn::step::boss::lowper
