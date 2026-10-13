#include "scn/step/enemy/common/StateSuperAppearPre.h"

#include "gobj/Move.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/common/StateSuperAppear.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateSuperAppearPre::StateSuperAppearPre(Enemy* enemy, int _14) : StateBase(enemy), mRequestor(enemy->comp()), _14(_14) {
    obj().move().resetVelocity();
    obj().model().setVisibility(false);
    obj().shadow().setVisibility(false);
    obj().vacuumReceiver().setIsValid(false);
    obj().objColl().setBodyCollStateXlu();
    obj().nururi().setValid(false);
}

StateSuperAppearPre::~StateSuperAppearPre() {
    obj().model().setVisibility(true);
    obj().shadow().setVisibility(true);
    obj().nururi().setValid(true);
    obj().objColl().bodyColl().setStateNormal();
    obj().vacuumReceiver().setIsValid(true);
}

void StateSuperAppearPre::procAnim() {
    mRequestor.request(static_cast<ostop::Flag>(0x11FF));
    if (mRequestor.isActive()) {
        obj().stateChanger().setNextState<StateSuperAppear, Enemy*, ::ostop::ReqHandle, int>(objPtr(), mRequestor.takeHandle(), _14);
    }
}

void StateSuperAppearPre::procMove() {}

void StateSuperAppearPre::procFixPos() {}

}}}}  // namespace scn::step::enemy::common
