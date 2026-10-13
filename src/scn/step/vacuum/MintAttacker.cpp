#include "scn/step/vacuum/MintAttacker.h"

#include "hel/common/PointerWrapper.h"
#include "scn/step/vacuum/Attacker.h"

namespace scn {
namespace step {
namespace vacuum {

namespace {

hel::common::PointerWrapper<Attacker> t_obj;

}

namespace MintAttacker {

void Register(Attacker& obj) {
    t_obj.set(obj);
}

void Unregister(Attacker&) {
    t_obj.reset();
}

u32 VacuumCount() {
    return t_obj->vacuumCount();
}

}
}
}
}
