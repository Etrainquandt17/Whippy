#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE
#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/buraburadee/Custom.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Model.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "mintglue/VectorInline.h"
#include "ocoll/Owner.h"
#include "revolution/mtx.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/buraburarope/Custom.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::geo::Rect;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::buraburarope::Custom>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::step::weapon::ICustom>(), RuntimeTypeInfo::NoName());
    return ti;
}

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace buraburadee {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mIsRopeRequested(false), mIsReceiver(true), _1e(true), mIsStateChange(false), _20(false) {
    obj().mapColl().setValid(false);
    obj().model().rotCtrl().initRotH(0.0f);
    f32 size = 0.8f * obj().charaParam()._2c;
    Rect rect(size, -size, -size, size);
    rect.trans(0.0f, -1.0f);
    obj().vacuumReceiver().setCustomCollideRect(rect);
}

bool Custom::onInit() {
    requestRope();
    return false;
}

Custom::~Custom() {
    releaseRopeIfExist();
}

void Custom::onProcFixPos() {
    if (_20) {
        _20 = false;
        obj().model().unsetCustomMtx();
    }
}

void Custom::ropeFixAnim() {
    if (mIsReceiver && mRope.isAlive()) {
        weapon::Weapon* rope = mRope.operator->();
        Matrix34 mtx;
        for (u32 i = 2; i <= 8; i++) {
            NodeAccessor node = rope->model().model().nodes().at(i);
            Matrix34 local = node.localMtx().rtMtx();
            mtx = local * mtx;
        }
        obj().model().setCustomMtx(mtx);
    }
}

void Custom::ropeFixMove() {
    if (mIsReceiver && mRope.isAlive()) {
        NodeAccessor node = mRope->model().model().nodes().at(9);
        Vector3 pos = node.worldMtx().getT();
        obj().location().setPos(pos);
    }
}

void Custom::deeAnimDecide() {
    if (mRope.isAlive()) {
        weapon::buraburarope::Custom& rope =
            DynamicCastToRef<weapon::buraburarope::Custom, weapon::ICustom>(mRope->custom());
        if (rope.getState() != rope.getPrevState()) {
            switch (rope.getState()) {
            case weapon::buraburarope::Custom::STATE_0: {
                u32 script = obj().kind() == 0x42 ? 0x16 : 0xF;
                obj().model().reqScript(script);
                break;
            }
            case weapon::buraburarope::Custom::STATE_1: {
                u32 script = obj().kind() == 0x42 ? 0x19 : 0x12;
                obj().model().reqScript(script);
                break;
            }
            case weapon::buraburarope::Custom::STATE_2: {
                u32 script = obj().kind() == 0x42 ? 0x17 : 0x10;
                obj().model().reqScript(script);
                break;
            }
            case weapon::buraburarope::Custom::STATE_3: {
                u32 script = obj().kind() == 0x42 ? 0x18 : 0x11;
                obj().model().reqScript(script);
                break;
            }
            }
        }
    }
}

bool Custom::onVacuumReceive() {
    _1e = false;
    obj().model().unsetCustomMtx();
    ropeSmallOn();
    releaseRopeIfExist();
    return false;
}

void Custom::onCaptured() {
    _1e = false;
    ropeSmallOn();
    releaseRopeIfExist();
    _20 = true;
}

bool Custom::onHitPointIsZero() {
    ropeSmallOn();
    onDamageProc();
    return false;
}

bool Custom::onDamaged() {
    ropeSmallOn();
    onDamageProc();
    return false;
}

void Custom::onDead() {
    releaseRopeIfExist();
    if (mRope.isAlive()) {
        weapon::Weapon* rope = mRope.operator->();
        if (_1e) {
            rope->dead();
        }
    }
}

void Custom::onDamageProc() {
    obj().model().unsetCustomMtx();
    releaseRopeIfExist();
    revertSetting();
}

void Custom::ropeSmallOn() {
    if (mRope.isAlive()) {
        weapon::Weapon* rope = mRope.operator->();
        weapon::buraburarope::Custom& custom =
            DynamicCastToRef<weapon::buraburarope::Custom, weapon::ICustom>(rope->custom());
        if (!custom.isSmall()) {
            custom.smallOn();
            rope->model().reqScript(0);
            Vector3 pos = rope->model().model().nodes().at(8).worldMtx().getT();
            obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x127), pos);
        }
    }
}

void Custom::offStateChange() {
    mIsStateChange = false;
}

bool Custom::isStateChange() {
    return mIsStateChange;
}

void Custom::releaseRopeIfExist() {
    if (mIsReceiver) {
        unsetReceiverRope();
        mIsReceiver = false;
    }
}

void Custom::revertSetting() {
    Matrix34 mtx;
    obj().model().setCustomMtx(mtx);
    obj().mapColl().setValid(true);
}

void Custom::requestRope() {
    if (!mIsRopeRequested) {
        mIsRopeRequested = true;
        Vector3 p = obj().location().pos();
        Vector2 pos(p.x, p.y);
        pos.y -= 0.1f;
        weapon::Desc desc(weapon::KIND_BURABURAROPE, 0, static_cast<ostop::Flag>(4), pos, Vector2::ZERO,
                          obj().objColl().owner());
        mRope = obj().comp().weaponManager().request(desc);
        if (mRope.isAlive()) {
            weapon::Weapon* rope = mRope.operator->();
            DynamicCastToRef<weapon::buraburarope::Custom, weapon::ICustom>(rope->custom()).setReceiver(*this);
            Matrix34 rot = Matrix34::CreateRotXYZDeg(Vector3(0.0f, 0.0f, 0.0f));
            for (u32 i = 2; i <= 8; i++) {
                rope->model().model().nodes().at(i).localMtx().setRTMtx(rot);
                rope->model().model().updateWorldMtx();
            }
            rope->target().setIsRightDir(obj().target().isRightDir());
        }
    }
}

void Custom::unsetReceiverRope() {
    if (mRope.isAlive()) {
        DynamicCastToRef<weapon::buraburarope::Custom, weapon::ICustom>(mRope->custom()).unsetReceiver(*this);
    }
}

void Custom::onRopeRequireUnsetReceiver(weapon::buraburarope::Custom& rope) {
    mIsStateChange = true;
    revertSetting();
    rope.unsetReceiver(*this);
    mIsReceiver = false;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::enemy::buraburadee
