#include "scn/step/boss/gigantedge/StateGuard.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/VectorInline.h"
#include "ocoll/Hit.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/CollUtil.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/gigantedge/Custom.h"
#include "scn/step/boss/gigantedge/Param.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace gigantedge {

namespace {

// TODO: an inline accessor of chara::BodyColl, whose members are not declared yet.
inline const ::ocoll::Hit& t_Hit(const chara::BodyColl& bodyColl) {
    return *reinterpret_cast<const ::ocoll::Hit*>(reinterpret_cast<const u8*>(&bodyColl) + 8);
}

}

StateGuard::StateGuard(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(14);
    obj().brainCtrl().toValid();
    obj().guard().setType(GUARD_TYPE_6);
    obj().flash().guard().setIsValid(true);
}

StateGuard::~StateGuard() {
    const Param& param = obj().param().gigantedge();
    common::CollUtil::SetBodyCollDefault(obj(), 0, param.mBodyCollRadius, param.mBodyCollOffset);
}

void StateGuard::procAnim() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setBodyCollGuard();
    Utility::TurnHatedHero(obj());
}

void StateGuard::procMove() {
    const Param& param = obj().param().gigantedge();
    obj().move().groundDecel(param._38);
}

void StateGuard::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

void StateGuard::procObjCollReact() {
    if (t_Hit(obj().objColl().bodyColl()).isCollide()) {
        obj().soundSE().normal().start(0x299);
        obj().effect().normal().requestP(static_cast<effect::Kind>(0xDD), obj().location().pos());
    }
}

}}}}  // namespace scn::step::boss::gigantedge
