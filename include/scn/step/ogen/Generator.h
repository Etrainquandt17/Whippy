#ifndef SCN_STEP_OGEN_GENERATOR_H
#define SCN_STEP_OGEN_GENERATOR_H

#include "hel/math/Vector2.h"

namespace scn {
namespace step {
namespace ogen {

class Generator {
public:
    void incCount();
    void decCount();
    void reqDead();
    hel::math::Vector2 pos() const;
};

}
}
}

#endif
