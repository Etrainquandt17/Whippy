#include "scn/step/enemy/sodory/StateWalkAround.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/sodory/Custom.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

StateWalkAround::StateWalkAround(Enemy* enemy)
    : StateBase(enemy), mFrame(0), mIsTurning(false), mIsRightDir(obj().target().isRightDir()) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    if (obj().model().anim().currentG3DAnimIndex() != 3) {
        obj().model().reqScript(3);
    }
    obj().model().setFrameRate(custom.getAnimRate());
    custom.setBasePosX();
    custom.setDirectionAll();
}

StateWalkAround::~StateWalkAround() {}

void StateWalkAround::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mFrame < custom.getFrame()) {
        mFrame++;
        if (mFrame >= custom.getFrame()) {
            obj().brainCtrl().toValid();
        }
    }
}

void StateWalkAround::procMove() {
    f32 speed = DynamicCastToRef<Custom, ICustom>(obj().custom()).getSpeed();
    if (!mIsTurning) {
        obj().move().groundAccel(obj().target().isRightDir(), gobj::MoveParamAccel::Create(speed, speed * 0.5f, speed * 0.5f));
    }
}

void StateWalkAround::procFixPos() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!mIsTurning) {
        Vector2 nururiDir = obj().nururi().getNururiDir();
        if (Math::Abs(nururiDir.x) >= 0.1f) {
            obj().move().resetSpeedH();
            mIsRightDir = nururiDir.x > 0.0f;
            mIsTurning = true;
        } else if (obj().mapColl().result().isHitWallFront()) {
            obj().move().resetSpeedH();
            mIsRightDir = !obj().target().isRightDir();
            mIsTurning = true;
            f32 sign = mIsRightDir ? 1.0f : -1.0f;
            custom.setBasePosX(obj().location().pos().x + 2.5f * sign);
        } else if (obj().cliffChecker().isCliff()) {
            obj().move().resetSpeedH();
            mIsRightDir = !obj().target().isRightDir();
            mIsTurning = true;
        } else {
            f32 diff = obj().location().pos().x - custom.getBasePosX();
            bool isOver = false;
            if (obj().target().isRightDir()) {
                if (diff > 2.0f) {
                    isOver = true;
                }
            } else {
                if (diff < -2.0f) {
                    isOver = true;
                }
            }
            if (isOver) {
                obj().move().resetSpeedH();
                mIsRightDir = !obj().target().isRightDir();
                mIsTurning = true;
            }
        }
    } else {
        if (obj().model().anim().frame() < custom.getAnimRate()) {
            obj().target().setIsRightDir(mIsRightDir);
            obj().move().setSpeedH(custom.getSpeed() * obj().target().getSign());
            mIsTurning = false;
        }
    }
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
    custom.setDirectionAll();
}

}}}}  // namespace scn::step::enemy::sodory
