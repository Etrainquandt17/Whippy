#include "scn/step/boss/roah/StateBoomerang.h"

#include "g3d/NodeAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/AttackFlash.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shake.h"
#include "snd/SERequestor.h"
#include "util/ObjList.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateBoomerang::StateBoomerang(Boss* boss, Config config)
    : StateBase(boss), mCount(0), mIsThrown(false), mIsCaught(false), mConfig(config) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    switch (mConfig._0) {
    case 0:
        obj().model().reqScript(10);
        custom.mahoroaCtrl().getCustom().reqMotionBoomerang(mahoroaroah::ScriptKind_8);
        break;
    case 1:
        obj().model().reqScript(11);
        custom.mahoroaCtrl().getCustom().reqMotionBoomerang(mahoroaroah::ScriptKind_9);
        break;
    case 2:
        obj().model().reqScript(12);
        custom.mahoroaCtrl().getCustom().reqMotionBoomerang(mahoroaroah::ScriptKind_10);
        break;
    }
}

StateBoomerang::~StateBoomerang() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).weaponCtrl().isCaught();
    obj().model().model().nodes().at(6).setVisibility(true);
    obj().model().model().nodes().at(7).setVisibility(true);
}

void StateBoomerang::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mCount++;
    if (mConfig._0 == 2 && !mIsThrown && mCount % 5 == 0) {
        obj().model().shake().request(static_cast<chara::ShakeKind>(0));
    }
    if (obj().scriptTrigger().get(0)) {
        mIsThrown = true;
        custom.weaponCtrl().request();
        switch (mConfig._0) {
        case 0:
            obj().model().model().nodes().at(6).setVisibility(false);
            break;
        case 1:
            obj().model().model().nodes().at(7).setVisibility(false);
            break;
        case 2:
            obj().model().model().nodes().at(6).setVisibility(false);
            obj().model().model().nodes().at(7).setVisibility(false);
            break;
        }
    }
    if (custom.weaponCtrl().isCaught()) {
        switch (mConfig._0) {
        case 0:
            obj().model().reqScript(14);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x4D0), 6);
            obj().model().model().nodes().at(6).setVisibility(true);
            break;
        case 1:
            obj().model().reqScript(13);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x4D0), 7);
            obj().model().model().nodes().at(7).setVisibility(true);
            break;
        case 2:
            obj().model().reqScript(13);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x4D0), 6);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x4D0), 7);
            obj().model().model().nodes().at(6).setVisibility(true);
            obj().model().model().nodes().at(7).setVisibility(true);
            break;
        }
        obj().soundSE().normal().start(0x454);
        obj().flash().attack().setEnd((GXColor){ 0xFF, 0xFF, 0xFF, 0x46 });
        mIsCaught = true;
    }
    if (mIsCaught && obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateBoomerang::procMove() {
    const Param& param = obj().param().roah();
    obj().move().decel(param.mDecel);
}

void StateBoomerang::procFixPos() {}

}}}}  // namespace scn::step::boss::roah
