#ifndef SCN_STEP_ENEMY_TOGEKUKI_CUSTOM_H
#define SCN_STEP_ENEMY_TOGEKUKI_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace togekuki {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::togekuki::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace togekuki {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);

private:
    u32 _8[2];
};

}
}
}
}

#endif
