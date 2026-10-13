#ifndef SCN_STEP_WEAPON_OBJCOLLREACT_H
#define SCN_STEP_WEAPON_OBJCOLLREACT_H

#include "types.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

class ObjCollReact {
public:
    ObjCollReact(Weapon& weapon);

    bool procObjCollReact();

private:
    Weapon& mObj;
};

}
}
}

#endif
