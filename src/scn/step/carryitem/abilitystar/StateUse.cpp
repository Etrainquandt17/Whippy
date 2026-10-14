#include "scn/step/carryitem/abilitystar/StateUse.h"

#include "gobj/Location.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/carryitem/abilitystar/StateBound.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/SoundSE.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/map/KindUtil.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace carryitem {
namespace abilitystar {

StateUse::StateUse(CarryItem* carryItem)
    : StateBase(carryItem)
    , mIsRightDir(false)
    , mOwnerPos() {
    obj().mapColl().setValid(false);
    if (obj().getUser().operator->() != 0) {
        if (!obj().getUser()->isNoUseSE()) {
            obj().soundSE().start(0xF9);
        }
        obj().getUser()->clearNoUseSE();
        mIsRightDir = obj().getUser()->isRightDir();
        mOwnerPos = obj().getUser()->getOwnerPos();
    }
    if (map::KindUtil::IsShootingMap(obj().comp().context().mapKind)) {
        obj().model().setScale(Vector3::ALL_ONE * 0.5f);
    }
}

StateUse::~StateUse() {
    obj().mapColl().setValid(true);
}

void StateUse::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Create(0.25f, 0.01f, 0.005f));
}

void StateUse::procFixPos() {
    if (obj().getUser().operator->() == 0) {
        obj().soundSE().start(obj().getReleaseType() == RELEASE_TYPE_THROW ? 0xFE : 0xF2);
        Vector3 pos = obj().location().pos();
        obj().location().setPos(mOwnerPos);
        obj().location().updatePrevPos();
        obj().mapColl().setValid(true);
        if (obj().getReleaseType() == RELEASE_TYPE_THROW || obj().kind() == 7) {
            Vector3 offset(0.0f, 0.2f, 0.0f);
            obj().location().setPos(pos + offset);
        } else {
            Vector3 offset(mIsRightDir ? 1.0f : -1.0f, 0.2f, 0.0f);
            obj().location().setPos(mOwnerPos + offset);
        }
        obj().mapColl().procMapColl();
        obj().mapColl().reset();
        obj().worldCage().proc();
        obj().stateChanger().setNextState<StateBound, CarryItem*, bool, bool>(objPtr(), false, mIsRightDir);
    } else {
        Vector3 constraintPos = obj().getUser()->getConstraintPos();
        obj().location().setPos(constraintPos);
        mIsRightDir = obj().getUser()->isRightDir();
        obj().model().updateMtx();
        mOwnerPos = obj().getUser()->getOwnerPos();
    }
}

}}}}  // namespace scn::step::carryitem::abilitystar
