#ifndef SCN_STEP_ENEMY_VOLCANOROCK_CUSTOM_H
#define SCN_STEP_ENEMY_VOLCANOROCK_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace volcanorock {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::volcanorock::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace volcanorock {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
};

}
}
}
}

#endif
