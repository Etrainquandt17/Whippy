#ifndef SCN_STEP_HERO_NURURI_H
#define SCN_STEP_HERO_NURURI_H

#include "hel/math/Vector2.h"

namespace scn {
namespace step {
namespace hero {

// TODO: members.
class Nururi {
public:
    void setValid(bool isValid);
    void setValid(bool isValid, u32 frame);
    void setCanNururi(bool canNururi);
    hel::math::Vector2 getNururiDir() const;
};

}
}
}

#endif
