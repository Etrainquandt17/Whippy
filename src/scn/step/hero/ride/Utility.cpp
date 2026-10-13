#include "scn/step/hero/ride/Utility.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/hero/CarryItemRide.h"
#include "scn/step/hero/CommandManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/RideParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"

namespace scn {
namespace step {
namespace hero {
namespace ride {

bool Utility::TryToDropOffStepShoe(Hero& hero) {
    if (hero.hid().isTrigger(0x20) || !hero.carryItemUser().isItemExist()) {
        hero.carryItemRide().release();
        hero.footState().setAir();
        const RideParam& param = hero.param().ride();
        f32 rate = hero.water().isInWater() ? param._30 : 1.0f;
        hero.move().setSpeedV(param._38 * rate);
        if (hero.hid().isTrigger(0x20)) {
            hero.move().setSpeedH(param._34 * hero.target().getSign());
        }
        hero::Utility::ChangeStateWaitOrFall(hero);
        return true;
    }
    return false;
}

bool Utility::TryToEnterDoorStepShoe(Hero& hero) {
    if (gimmick::StateEnterDoor::TryToChangeState(&hero, static_cast<ScriptKind>(0x74), true)) {
        hero.carryItemRide().setContinue();
        return true;
    }
    return false;
}

bool Utility::IsJumpInput(Hero& hero, u32 frame) {
    return hero.commandManager().getTriggerPastFrame(static_cast<ButtonMask>(0x10)) <= frame;
}

}
}
}
}
