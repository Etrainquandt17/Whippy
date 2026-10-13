#include "scn/step/enemy/barracu/StateSwimStraight.h"

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

StateSwimStraight::StateSwimStraight(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().model().rotCtrl().setRotHTargetDefault(90.0f);
    obj().model().rotCtrl().initRotH(90.0f);
    obj().model().rotCtrl().setRotHIntpRate(0.07f);
}

StateSwimStraight::~StateSwimStraight() {
    obj().objColl().clearSearchHit();
}

void StateSwimStraight::procAnim() {
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

void StateSwimStraight::procMove() {
    const ParamData& param = obj().param().barracu();
    u32 level = obj().level();
    if (level > 2) {
        level = 2;
    }
    f32 speed = param.mLevel[level].mSpeed;
    if (obj().model().getCurrentScriptIndex() != 7) {
        if (obj().water().isPosInWater(hel::math::Vector2(0.5f * obj().target().getSign(), 0.0f))) {
            speed = param.mTurnSpeed;
        } else {
            speed = 0.0f;
        }
    }
    hel::math::Vector3 pos = obj().location().pos();
    pos.x += speed * obj().target().getSign();
    obj().location().setPos(pos);
    obj().objColl().clearSearchHit();
    if (obj().model().getCurrentScriptIndex() == 7) {
        obj().objColl().addSearchHit(1, param.mSearchRadius, hel::math::Vector2(param.mSearchOffset * obj().target().getSign(), 0.0f));
    }
}

void StateSwimStraight::procFixPos() {
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

void StateSwimStraight::procObjCollReact() {
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).chkCaptureHero()) {
        obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
    }
}

}
}
}
}
