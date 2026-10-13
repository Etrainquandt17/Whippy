#include "scn/step/enemy/grandlowperbullet/StatePrepare.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
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
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/grandlowperbullet/Custom.h"
#include "scn/step/enemy/grandlowperbullet/StateHoming.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

StatePrepare::StatePrepare(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().mapColl().setValid(false);
    obj().objColl().bodyColl().setStateXlu();
    obj().vacuumReceiver().setIsValid(false);
    obj().model().setVisibility(false);
    obj().shadow().setVisibility(false);
    obj().effect().normal().releaseAndVanish();
}

StatePrepare::~StatePrepare() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).reqImageEffect();
    obj().shadow().setVisibility(true);
    obj().model().setVisibility(true);
    obj().objColl().bodyColl().setStateNormal();
    obj().vacuumReceiver().setIsValid(true);
    obj().mapColl().setValid(true);
}

void StatePrepare::procAnim() {
    if (obj().signal().isValid()) {
        u32 signal = obj().signal().get();
        obj().signal().clear();
        if (signal == 1) {
            obj().stateChanger().setNextState<StateHoming, Enemy*>(objPtr());
        }
    }
}

void StatePrepare::procMove() {}

void StatePrepare::procFixPos() {}

}
}
}
}
