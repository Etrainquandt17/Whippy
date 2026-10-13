#ifndef SCN_STEP_WEAPON_INDIVIUTIL_H
#define SCN_STEP_WEAPON_INDIVIUTIL_H

#include "scn/step/chara/ModelDesc.h"
#include "scn/step/weapon/Kind.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {

class IndiviUtil {
public:
    static chara::ModelDesc& ModelDesc(Kind kind, bool isEx);
};

}
}
}

#endif
