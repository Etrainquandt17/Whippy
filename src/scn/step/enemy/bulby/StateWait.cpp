#include "scn/step/enemy/bulby/StateWait.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/bulby/Custom.h"
#include "scn/step/enemy/bulby/ParamData.h"
#include "scn/step/enemy/bulby/StateAttack.h"
#include "scn/step/enemy/bulby/StateJump.h"
#include "scn/step/enemy/common/StateFall.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace bulby {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isBuried()) {
        obj().model().reqScript(7);
    }
}

StateWait::~StateWait() {
    setHitFlag(true);
}

void StateWait::procAnim() {
    const ParamData& param = obj().param().bulby();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    setHitFlag(true);
    if (mFrame > param.mWaitFrame && Utility::IsHeroInRange(obj(), param.mRangeH, -param.mRangeH, -param.mRangeV, param.mRangeV)) {
        if (custom.isBuried() || obj().variation() == 0x64) {
            obj().stateChanger().setNextState<StateJump, Enemy*>(objPtr());
        } else {
            obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
        }
    } else if (custom.isBuried()) {
        if (mFrame > param.mWaitFrame
            && Utility::IsHeroInRange(obj(), param.mRangeH, -param.mRangeH, -param.mRangeVBuried, param.mRangeVBuried)) {
            obj().objColl().clearBodyColl();
            f32 scale = Utility::GetModelScaleBySizeType(obj());
            obj().objColl().addBodyColl(0, param.mBodyRadiusBuried * scale);
            if (obj().model().getCurrentScriptIndex() != 8) {
                obj().model().reqScript(8);
                smoke();
            }
        } else {
            obj().objColl().clearBodyColl();
            setHitFlag(false);
            if (obj().model().getCurrentScriptIndex() != 7) {
                obj().model().reqScript(7);
                smoke();
            }
        }
    } else {
        obj().model().reqScript(0);
    }
    if (mFrame <= param.mWaitFrame) {
        mFrame++;
    }
    Utility::TurnHero(obj());
}

void StateWait::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

void StateWait::smoke() {
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x124), 0);
}

void StateWait::setHitFlag(bool flag) {
    obj().captureReceiver().setCanCapture(flag);
    u32 level = flag ? 0 : 2;
    obj().vacuumReceiver().setResistLevel(level);
    obj().shadow().setVisibility(flag);
}

}}}}  // namespace scn::step::enemy::bulby
