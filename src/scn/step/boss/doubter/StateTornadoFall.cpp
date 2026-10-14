#include "scn/step/boss/doubter/StateTornadoFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/ScriptKind.h"
#include "scn/step/boss/doubter/StateLanding.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateTornadoFall::StateTornadoFall(Boss* boss) : StateBase(boss) {
    obj().footState().setAir();
    obj().guard().setType(static_cast<GuardType>(2));
    obj().model().reqScript(13);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_3);
    setInitSpeed();
}

StateTornadoFall::~StateTornadoFall() {}

void StateTornadoFall::procAnim() {
    Utility::TurnHatedHero(obj());
}

void StateTornadoFall::procMove() {
    const Param& param = obj().param().doubter();
    if (obj().move().velocity().y > 0.0f) {
        obj().move().airDecelFall(param._90, param._94);
    } else {
        obj().move().airDecelFall(param._90, param._A0);
    }
}

void StateTornadoFall::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        Vector2 pos = obj().param().doubter()._24;
        Vector2 speed = obj().param().doubter()._2C;
        Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
        pos.x *= -1.0f;
        speed.x *= -1.0f;
        Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(7));
        obj().soundSE().loop().stop();
        obj().stateChanger().setNextState<StateLanding, Boss*, ScriptKind>(objPtr(), static_cast<ScriptKind>(5));
    }
}

void StateTornadoFall::setInitSpeed() {
    const Param& param = obj().param().doubter();
    obj().move().setVelocity(Vector3(0.0f, param._8C, 0.0f));
}

}}}}  // namespace scn::step::boss::doubter
