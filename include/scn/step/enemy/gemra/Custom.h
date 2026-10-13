#ifndef SCN_STEP_ENEMY_GEMRA_CUSTOM_H
#define SCN_STEP_ENEMY_GEMRA_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace gemra {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::gemra::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace gemra {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);

    void resetPos();
    void updateDir();
    void updatePos();
    void updateFixPos();

private:
    u32 _8[12];
};

}
}
}
}

#endif
