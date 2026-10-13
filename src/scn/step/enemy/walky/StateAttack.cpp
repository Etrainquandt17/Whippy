#include "scn/step/enemy/walky/StateAttack.h"

#include "app/Random.h"
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
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/walky/ParamData.h"
#include "scn/step/enemy/walky/StateAttackEnd.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace walky {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0), mIsShot(false) {
    obj().footState().setGround();
    obj().model().reqScript(8);
    obj().move().resetSpeedH();
    obj().move().resetSpeedV();
}

StateAttack::~StateAttack() {}

void StateAttack::procAnim() {
    if (!mIsShot) {
        mFrame++;
        if (mFrame >= obj().param().walky().mAttackShotFrame) {
            shotAll();
            mIsShot = true;
        }
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateAttackEnd, Enemy*>(objPtr());
    }
}

void StateAttack::procMove() {}

void StateAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

void StateAttack::shotAll() {
    u32 table[24][3] = {
        { 0, 1, 2 }, { 0, 1, 3 }, { 0, 2, 1 }, { 0, 2, 3 }, { 0, 3, 1 }, { 0, 3, 2 }, { 1, 0, 2 }, { 1, 0, 3 },
        { 1, 2, 0 }, { 1, 2, 3 }, { 1, 3, 0 }, { 1, 3, 2 }, { 2, 0, 1 }, { 2, 0, 3 }, { 2, 1, 0 }, { 2, 1, 3 },
        { 2, 3, 0 }, { 2, 3, 1 }, { 3, 0, 1 }, { 3, 0, 2 }, { 3, 1, 0 }, { 3, 1, 2 }, { 3, 2, 0 }, { 3, 2, 1 },
    };
    int index = app::Random::Rand(24);
    shot(table[index][0] * 3);
    shot(table[index][1] * 3 + 1);
    shot(table[index][2] * 3 + 2);
}

void StateAttack::shot(u32 variation) {
    obj().soundSE().start(0x2b3);
    weapon::Desc desc;
    desc.mKind = static_cast<weapon::Kind>(0x42);
    desc.mVariation = variation;
    desc.mFlag = static_cast<ostop::Flag>(4);
    g3d::NodeAccessor node = obj().model().model().nodes().at(4);
    desc.mPos = node.worldMtx().getT().getXY();
    desc._14 = obj().location().pos().getXY() + hel::math::Vector2(0.0f, 0.0f);
    desc._1c = node.worldMtx().getZ().getXY();
    desc.mOwner = &obj().objColl().owner();
    obj().comp().weaponManager().request(desc);
}

}
}
}
}
