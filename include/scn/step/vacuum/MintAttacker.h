#ifndef SCN_STEP_VACUUM_MINTATTACKER_H
#define SCN_STEP_VACUUM_MINTATTACKER_H

#include "types.h"

namespace scn {
namespace step {
namespace vacuum {

class Attacker;

namespace MintAttacker {

void Register(Attacker& obj);
void Unregister(Attacker& obj);
u32 VacuumCount();

}
}
}
}

#endif
