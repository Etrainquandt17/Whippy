#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/poppybrojr/Custom.h"

#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/poppybrojr/ParamData.h"
#include "scn/step/enemy/poppybrojrbomb/StateShot.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojr {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mIsThrowValid(false) {}

bool Custom::onDamaged() {
    mIsThrowValid = false;
    return false;
}

void Custom::onCaptured() {
    mIsThrowValid = false;
}

void Custom::requestBomb() {
    if (!mIsThrowValid) {
        g3d::NodeAccessor node = obj().model().model().nodes().at(1);
        hel::math::Vector2 pos = node.worldMtx().getT().getXY();
        Desc desc(static_cast<map::BinEnemyKind>(0x73), static_cast<map::BinEnemyVariation>(0x19c), obj().level(), obj().dirType(),
                  obj().size(), false, false, pos);
        mBomb = obj().comp().enemyManager().request(desc);
        if (mBomb.isAlive()) {
            if (obj().objGenerator() != 0) {
                ogen::Generator& generator = *obj().objGenerator();
                mBomb->setObjGenerator(generator);
            }
            Enemy* bomb = mBomb.operator->();
            bomb->captureReceiver().setCanCapture(false);
            bomb->mapColl().setValid(false);
            bomb->model().setVisibility(false);
            bomb->objColl().clearBodyColl();
            bomb->nururi().setCanNururi(false);
            bomb->nururi().setValid(false);
            bomb->shadow().setVisibility(false);
            bomb->vacuumReceiver().setIsValid(false);
            mIsThrowValid = true;
        } else {
            mIsThrowValid = false;
        }
    }
}

void Custom::changeBombState() {
    if (mIsThrowValid) {
        const ParamData& param = obj().param().poppybrojr();
        if (mBomb.isAlive()) {
            Enemy* bomb = mBomb.operator->();
            g3d::NodeAccessor node = obj().model().model().nodes().at(1);
            bomb->location().setPos(node.worldMtx().getT());
            bomb->move().setVelocity(hel::math::Vector3(param.mThrowSpeedX * obj().target().getSign(), param.mThrowSpeedY, 0.0f));
            bomb->mapColl().setValid(true);
            bomb->model().setVisibility(true);
            bomb->nururi().setCanNururi(true);
            bomb->nururi().setValid(true);
            bomb->shadow().setVisibility(true);
            bomb->vacuumReceiver().setIsValid(true);
            mBomb->stateChanger().setNextState<poppybrojrbomb::StateShot, Enemy*>(bomb);
            mIsThrowValid = false;
        }
    }
}

void Custom::requestBombDead() {
    if (mBomb.isAlive()) {
        mBomb->dead();
    }
}

int Custom::setWaitTime() {
    switch (obj().level()) {
    case 0:
        return 120;
    case 1:
        return 80;
    default:
        return 40;
    }
}

void Custom::setIsThrowValid(bool isThrowValid) {
    mIsThrowValid = isThrowValid;
}

bool Custom::isThrowValid() {
    return mIsThrowValid;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
