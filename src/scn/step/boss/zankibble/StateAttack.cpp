#include "scn/step/boss/zankibble/StateAttack.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/zankibble/Custom.h"
#include "scn/step/boss/zankibble/NodeKind.h"
#include "scn/step/boss/zankibble/Param.h"
#include "scn/step/boss/zankibble/StateCatch.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

StateAttack::StateAttack(Boss* boss, Config config) : StateBase(boss), mConfig(config), mIsScaling(false), mCount(0) {
    obj().footState().setGround();
    obj().model().reqScript(mConfig._0);
    Utility::ControlHateOnAction(obj());
}

StateAttack::~StateAttack() {
    g3d::NodeAccessor node = obj().model().model().nodes().at(NODE_KIND_CUTTER);
    node.localMtx().setScale(hel::math::Vector3(1.0f, 1.0f, 1.0f));
}

void StateAttack::procAnim() {
    const Param& param = obj().param().zankibble();
    if (obj().scriptTrigger().get(0)) {
        switch (mConfig._0) {
        case 12:
            reqCutterStraight();
            break;
        case 14:
        case 15:
            reqCutterCircle();
            break;
        case 16:
            reqCutterBackCircle();
            break;
        }
    }
    if (obj().scriptTrigger().get(1)) {
        mIsScaling = true;
    }
    if (mConfig._C && mIsScaling) {
        if (mCount < param.mCutterScaleTime) {
            mCount++;
        }
        f32 rate = static_cast<f32>(mCount) / static_cast<f32>(param.mCutterScaleTime);
        f32 scale = hel::math::Math::LinearInterpolation(param.mCutterScaleStart, param.mCutterScaleEnd, rate);
        g3d::NodeAccessor node = obj().model().model().nodes().at(NODE_KIND_CUTTER);
        g3d::NodeLocalMtxAccessor mtx = node.localMtx();
        mtx.setScale(hel::math::Vector3(scale, scale, scale));
    }
    if (obj().model().isAllEnd()) {
        switch (mConfig._0) {
        case 12:
            obj().stateChanger().setNextState<StateCatch, Boss*>(objPtr());
            break;
        case 14:
        case 15:
            obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
            break;
        case 16:
            obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
            break;
        }
    }
}

void StateAttack::procMove() {
    const Param& param = obj().param().zankibble();
    obj().move().groundDecel(param._24);
}

void StateAttack::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

void StateAttack::reqCutterStraight() {
    const Param& param = obj().param().zankibble();
    hel::math::Vector2 pos = obj().location().pos().getXY();
    pos += hel::math::Vector2(param.mCutterStraightOffset.x * obj().target().getSign(), param.mCutterStraightOffset.y);
    hel::math::Vector3 velocity(mConfig._4.x * obj().target().getSign(), mConfig._4.y, 0.0f);
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().request(EnemyCtrl::CUTTER_KIND_STRAIGHT, pos, velocity, false);
}

void StateAttack::reqCutterCircle() {
    const Param& param = obj().param().zankibble();
    hel::math::Vector2 pos = obj().location().pos().getXY();
    pos += hel::math::Vector2(param.mCutterCircleOffset.x * obj().target().getSign(), param.mCutterCircleOffset.y);
    hel::math::Vector3 velocity(mConfig._4.x * obj().target().getSign(), mConfig._4.y, 0.0f);
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().request(EnemyCtrl::CUTTER_KIND_CIRCLE, pos, velocity, mConfig._C);
}

void StateAttack::reqCutterBackCircle() {
    const Param& param = obj().param().zankibble();
    hel::math::Vector2 pos = obj().location().pos().getXY();
    pos += hel::math::Vector2(param.mCutterBackCircleOffset.x * obj().target().getSign(), param.mCutterBackCircleOffset.y);
    hel::math::Vector3 velocity(mConfig._4.x * obj().target().getSign(), mConfig._4.y, 0.0f);
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().request(EnemyCtrl::CUTTER_KIND_BACK_CIRCLE, pos, velocity, false);
}

}}}}  // namespace scn::step::boss::zankibble
