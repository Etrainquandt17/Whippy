#include "scn/step/item/Utility.h"

#include "g3d/ModelAccessor.h"
#include "g3d/NodeAccessor.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/arena/Manager.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/core/SphereAccessor.h"
#include "scn/step/item/Item.h"
#include "scn/step/map/KindUtil.h"

using g3d::ModelAccessor;
using g3d::NodeAccessor;

namespace scn {
namespace step {
namespace item {

void Utility::RequestEffectEnergySphere(Component& component, const ModelAccessor& model, chara::Effect& effect) {
    NodeAccessor node = model.nodeByName("RotControlL");
    effect.requestN(
        component.sphereAccessor().isGetShipParts() ? static_cast<effect::Kind>(0x343) : static_cast<effect::Kind>(0x342),
        node);
    effect.requestN(static_cast<effect::Kind>(0x341), node);
}

void Utility::RequestEffectShipParts(Component& component, const ModelAccessor& model, chara::Effect& effect) {
    // A safety net, as far as the callers show: no boss gives out a ship part in the Arena. If one did, this keeps
    // the Arena from asking the stage's save data, which it doesn't have, whether the part is collected already.
    bool isArena = false;
    if (component.arenaManager().isArena() || map::KindUtil::IsArenaStage(component.context().mapKind)) {
        isArena = true;
    }
    bool isGet;
    if (isArena) {
        isGet = false;
    } else {
        isGet = component.sphereAccessor().isGetShipParts();
    }
    NodeAccessor node = model.nodeByName("PtclL");
    effect.requestN(isGet ? static_cast<effect::Kind>(0x345) : static_cast<effect::Kind>(0x344), node);
    effect.requestN(static_cast<effect::Kind>(0x341), node);
}

// TODO: IsOnGround(Item&) (0xAC bytes, dropped by the link) and IsInLand(Item&) (0x154 bytes) are not written.

bool Utility::IsWithLowper(Item& item) {
    bool isWithLowper = false;
    if (static_cast<int>(item.variation()) == 4 || static_cast<int>(item.variation()) == 5) {
        isWithLowper = true;
    }
    return isWithLowper;
}

}}}  // namespace scn::step::item
