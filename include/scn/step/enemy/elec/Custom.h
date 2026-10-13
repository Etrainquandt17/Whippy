#ifndef SCN_STEP_ENEMY_ELEC_CUSTOM_H
#define SCN_STEP_ENEMY_ELEC_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace elec {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::elec::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace elec {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual void onProcFixPos();
};

}
}
}
}

#endif
