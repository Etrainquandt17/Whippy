#define MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE

#include "scn/step/hero/common/StateShipRepairDemoAfter.h"
#include "gobj/Move.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/gimmick/Manager.h"
#include "scn/step/gimmick/shipevent/Manager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Nururi.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/WearBack.h"
#include "scn/step/hero/gimmick/StateEnterMahoroa.h"
#include "scn/step/info/InfoGameStatus.h"
#include "scn/step/info/Manager.h"
#include "util/StateChanger.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace common {

StateShipRepairDemoAfter::StateShipRepairDemoAfter(Hero* hero) : StateBase(hero) {
    obj().stateChecker().setDemo(true);
    obj().model().script().start(0x4D);
    obj().comp().infoManager().gameStatus().startAnimOutS();
    obj().objColl().setXlu();
    obj().mapColl().setValid(false);
    obj().nururi().setValid(false);
    mPos = obj().location().pos();
    mCounter.reset(60);
    obj().comp().gimmickManager().shipeventManager().setIsClearDemo(true);
    obj().wearBack().setBack();
}

StateShipRepairDemoAfter::~StateShipRepairDemoAfter() {
    obj().stateChecker().setDemo(false);
    obj().move().resetSpeedV();
    obj().nururi().setValid(true);
    obj().wearBack().unsetBack();
}

void StateShipRepairDemoAfter::procAnim() {
    mCounter.advanceIfNotEnd();
    if (obj().model().isAllEnd()) {
        obj().model().script().start(0);
    }
    if (mCounter.isEnd()) {
        obj().stateChanger().setNextState<gimmick::StateEnterMahoroa, Hero*>(objPtr());
    }
}

void StateShipRepairDemoAfter::procMove() {
    if (!mCounter.isEnd()) {
        Vector3 pos = obj().location().pos();
        pos.z = mPos.z - 0.1f * (59 - mCounter.frame());
        obj().location().setPos(pos);
    }
}

void StateShipRepairDemoAfter::procFixPos() {
    if (mCounter.isEnd()) {
        obj().move().resetSpeedV();
    }
}

}}}}  // namespace scn::step::hero::common
