#include "scn/step/enemy/barracu/StatePursuit.h"

#include "gobj/FootState.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Water.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/barracu/Custom.h"
#include "scn/step/enemy/barracu/ParamData.h"
#include "scn/step/enemy/barracu/StateAttack.h"

namespace scn {
namespace step {
namespace enemy {
namespace barracu {

namespace {

// TODO: the names are guesses.
enum Script {
    SCRIPT_TURN_RIGHT = 8,
    SCRIPT_TURN_LEFT = 9,
};

}

StatePursuit::StatePursuit(Enemy* enemy) : StateBase(enemy), mTurnFrame(0), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().model().rotCtrl().setRotHTargetDefault(90.0f);
    obj().model().rotCtrl().initRotH(90.0f);
    obj().model().rotCtrl().setRotHIntpRate(0.07f);
}

StatePursuit::~StatePursuit() {
    obj().objColl().clearSearchHit();
}

void StatePursuit::procAnim() {
    const ParamData& param = obj().param().barracu();
    if (obj().model().getCurrentScriptIndex() != 7 && obj().model().isAllEnd()) {
        obj().model().reqScript(7);
    }
    mFrame++;
    if (mFrame % param.mEffectFrame == 0) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x133), 0);
        if (mFrame == param.mEffectFrame) {
            mFrame = 0;
        }
    }
}

void StatePursuit::procMove() {
    const ParamData& param = obj().param().barracu();
    u32 level = hel::math::Math::LimitMinMax<u32>(obj().level(), 0, 2);
    hel::math::Vector3 pos = obj().location().pos();
    if (obj().model().getCurrentScriptIndex() == 7) {
        if (!obj().water().isPosInWater(hel::math::Vector2(0.0f, 0.5f))) {
            pos.y -= 0.02f;
            obj().location().setPos(pos);
        }
        if (Utility::IsPlayerExist(obj())) {
            if ((obj().target().isRightDir() && !Utility::IsNearestPlayerRight(obj())) ||
                (!obj().target().isRightDir() && Utility::IsNearestPlayerRight(obj()))) {
                mTurnFrame++;
                if (mTurnFrame >= 60) {
                    Utility::Turn(obj());
                    obj().model().reqScript(obj().target().isRightDir() ? SCRIPT_TURN_RIGHT : SCRIPT_TURN_LEFT);
                    mTurnFrame = 0;
                    obj().effect().normal().requestN(static_cast<effect::Kind>(0x133), 0);
                    mFrame = 0;
                }
            } else {
                mTurnFrame = 0;
            }
            f32 rate = 1.0f - mTurnFrame / 80.0f;
            pos.x += rate * (param.mLevel[level].mSpeed * obj().target().getSign());
            pos.y += 0.02f * hel::math::Math::LimitMinMax<f32>(Utility::GetNearestPlayerPos(obj()).y - pos.y, -1.0f, 1.0f);
        } else {
            pos.x += param.mLevel[level].mSpeed * obj().target().getSign();
        }
    } else if (obj().water().isPosInWater(hel::math::Vector2(0.5f * obj().target().getSign(), 0.0f))) {
        pos.x += param.mTurnSpeed * obj().target().getSign();
    }
    hel::math::Vector2 diff = pos.getXY() - obj().location().pos().getXY();
    if (!obj().water().isPosInWater(diff + hel::math::Vector2(0.0f, 0.5f))) {
        pos.y -= 0.02f;
    }
    obj().location().setPos(pos);
    obj().objColl().clearSearchHit();
    if (obj().model().getCurrentScriptIndex() == 7) {
        obj().objColl().addSearchHit(1, param.mSearchRadius, hel::math::Vector2(param.mSearchOffset * obj().target().getSign(), 0.0f));
    }
}

void StatePursuit::procFixPos() {
    if (obj().model().getCurrentScriptIndex() == 7) {
        if (obj().mapColl().result()._2 || Utility::ChkNururiByDir(obj(), 0.1f) ||
            !obj().water().isPosInWater(hel::math::Vector2(0.5f * obj().target().getSign(), 0.0f))) {
            Utility::Turn(obj());
            obj().objColl().clearSearchHit();
            obj().model().reqScript(obj().target().isRightDir() ? SCRIPT_TURN_RIGHT : SCRIPT_TURN_LEFT);
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x133), 0);
            mFrame = 0;
        }
    }
}

void StatePursuit::procObjCollReact() {
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).chkCaptureHero()) {
        obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
    }
}

}
}
}
}
